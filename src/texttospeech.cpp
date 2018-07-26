#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <regex>
#include <vector>
#include "texttospeech.h"

// constructor & destructor -----------------------------------------------------------------------
TextToSpeech::TextToSpeech(const int& lang,
    std::string& speed, std::string& pitch, std::string& output,
    std::string& text, Engine eng) {
    m_eng = eng;
    checkLanguage(lang);
    if(speed != "")     m_speed = speed;
    if(pitch != "")     m_pitch = pitch;
    if(output != "")    m_out = output;
    if(text != "")      m_text = text;
}

TextToSpeech::~TextToSpeech() {}

// privat methods --------------------------------------------------------------------------------- 
void TextToSpeech::checkLanguage(const int& lang) {
    switch(m_eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: {
            switch(lang) {
                case 0: m_lang = "&tl=en"; break;
                case 1: m_lang = "&tl=en"; break;
                case 2: m_lang = "&tl=de"; break;
                case 3: m_lang = "&tl=es"; break;
                case 4: m_lang = "&tl=fr"; break;
                case 5: m_lang = "&tl=it"; break;
                default: m_lang = "&tl=en"; break;
            }
            std::cout << m_lang << std::endl;
        } break;
        case Engine::PICO2WAVE: {
            switch(lang) {
                case 0: m_lang += "en-US"; break;
                case 1: m_lang += "en-GB"; break;
                case 2: m_lang += "de-DE"; break;
                case 3: m_lang += "es-ES"; break;
                case 4: m_lang += "fr-FR"; break;
                case 5: m_lang += "it-IT"; break;
                default: m_lang += "en-US"; break;
            }
        } break;
    }
}


void TextToSpeech::recordFiles() {
    for (size_t i = 0; i < m_gMsgParts.size(); i++) {
        std::string tmp = "/tmp/gTmp" + std::to_string(i) + ".wav";
        std::string message = "\"" + m_google + m_gMsgParts[i] + m_lang + "\"";
        std::cout << message << std::endl;
        m_cmd = "mplayer "+message+" -vc null -vo null -ao pcm:fast:waveheader:file="+tmp;
        std::system(m_cmd.c_str());
    }
}


void TextToSpeech::saveParts() {
    std::vector<std::string> words = split(m_text," ");  
    std::string request = "";
    for(auto& word : words) {
        if(request.length()+word.length()+1 <= m_gRequestLength) {
            request += word + " ";
        } else {
            m_gMsgParts.push_back(request);
            request = word + " ";
            m_gTmpFiles++;
        }
    }
    m_gMsgParts.push_back(request);

}

std::vector<std::string> TextToSpeech::split(std::string &str, const std::string delimiter) {
    std::vector<std::string> parts;
    std::size_t pos = 0;
    std::string token;
    while((pos = str.find(delimiter)) != std::string::npos){
        token = str.substr(0,pos);
        parts.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    parts.push_back(str);
    return parts;
} 

// public methods ----------------------------------------------------------------------------------
bool TextToSpeech::checkProgram(const std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(),"r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    if(result == "" || (result.find("which: no") != std::string::npos)) {
        return false;
    } else {
        return true;
    }
}

void TextToSpeech::clearTmp() {
    switch(m_eng) {
        case Engine::ESPEAK: break;
        case Engine::PICO2WAVE: 
            m_cmd = m_rm+" "+m_tmp;
            break;
        case Engine::GOOGLE:
            m_cmd = m_rm+" /tmp/gTmp*.wav "+m_tmp;
            break;
    }
    std::system(m_cmd.c_str());
}

void TextToSpeech::createAudio() {
    switch(m_eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: { 
            std::cout << "GoogleAudio" << std::endl;
            saveParts();
            recordFiles();
            m_cmd = m_sox+" "+"/tmp/gTmp*.wav"+" "+m_tmp;
            std::system(m_cmd.c_str());
        } break;
        case Engine::PICO2WAVE: {
            std::string tmp = "-w=" + m_tmp;
            m_text = "\"" + m_text + "\"";
            m_cmd = m_pico+" "+m_lang+" "+tmp+" "+m_text;
            std::system(m_cmd.c_str());
        } break;
    }
}

void TextToSpeech::setSpeedAndPitch() {
    m_cmd = m_sox+" "+m_tmp+" "+m_out+" "+"tempo"+" "+m_speed+" "+"pitch"+" "+m_pitch;
    std::system(m_cmd.c_str());
}

void TextToSpeech::start() {
    createAudio();
    setSpeedAndPitch();
    clearTmp();
}

// operators-----------------------------------------------------------------------------------------


