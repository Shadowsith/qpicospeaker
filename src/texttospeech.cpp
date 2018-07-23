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
    std::string& speed, std::string& pitch, std::string output, std::string& text) {
    checkLanguage(lang);
    if(speed != "")     m_speed = speed;
    if(pitch != "")     m_pitch = pitch;
    if(output != "")    m_out = output;
    if(text != "")     m_text = text;
    m_eng = Engine::PICO2WAVE;
}

TextToSpeech::TextToSpeech(const int& lang,
    std::string& speed, std::string& pitch, std::string output, 
    std::string& input, Engine eng) {
    checkLanguage(lang);
    if(speed != "")     m_speed = speed;
    if(pitch != "")     m_pitch = pitch;
    if(output != "")    m_out = output;
    if(input != "")     m_in = input;
    m_eng = eng; 
}

TextToSpeech::~TextToSpeech() {}

// privat methods --------------------------------------------------------------------------------- 
void TextToSpeech::checkLanguage(const int& lang) {
    switch(lang) {
        case 0: m_lang += "en-US"; break;
        case 1: m_lang += "en-GB"; break;
        case 2: m_lang += "de-DE"; break;
        case 3: m_lang += "es-ES"; break;
        case 4: m_lang += "fr-FR"; break;
        case 5: m_lang += "it-IT"; break;
        default: m_lang += "en-US"; break;
    }
}


void TextToSpeech::recordFiles() {
    for (size_t i = 0; i < m_gMsgParts.size(); i++) {
        std::string out = "/tmp/gTmp" + std::to_string(i) + ".wav";
        std::string message = "\"" + m_google + m_gMsgParts[i] + "de" + "\"";
        m_cmd = "mplayer "+message+" -vc null -vo null -ao pcm:fast:waveheader:file="+out;
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
            m_cmd = m_rm+" "+m_out;
            break;
        case Engine::GOOGLE:
            m_cmd = m_rm+" /tmp/gTmp*.wav";
            break;
    }
    std::system(m_cmd.c_str());
}

void TextToSpeech::createAudio() {
    switch(m_eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: { 
            saveParts();
            recordFiles();
            m_cmd = m_sox+" "+"/tmp/gTmp*.wav"+" "+"new.wav";
            std::system(m_cmd.c_str());
        } break;
        case Engine::PICO2WAVE: {
            std::string out = "-w=" + m_out; 
            m_text = "\"" + m_text + "\"";
            m_cmd = m_pico+" "+m_lang+" "+out+" "+m_text; 
            std::system(m_cmd.c_str());
        } break;
    }
}

void TextToSpeech::setSpeedAndPitch() {
    m_cmd = m_sox+" "+m_out+" "+"/tmp/new.wav"+" "+"tempo"+" "+m_speed+" "+"pitch"+" "+m_pitch;
    std::system(m_cmd.c_str());
}

void TextToSpeech::start() {
    createAudio();
    setSpeedAndPitch();
    clearTmp();
}

