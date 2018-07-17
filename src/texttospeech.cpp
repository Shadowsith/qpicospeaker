#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <regex>
#include "texttospeech.h"

    /*
        supported languages:
        en-US
        en-GB
        de-DE
        es-ES
        fr-FR
        it-IT
    */

TextToSpeech::TextToSpeech(std::string lang, std::string speed,
                           std::string pitch, std::string output, std::string input) {
    checkLanguage(lang);
    if(speed != "") {
        m_speed = speed;
    }
    if(pitch != "") {
        m_pitch = pitch;
    }
    if(output != "") {
        m_out = output;
    }
    if(input != "") {
        m_in = input;
    }
}

TextToSpeech::~TextToSpeech() {}

void TextToSpeech::checkLanguage(std::string& lang) {
    std::transform(lang.begin(), lang.end(), lang.begin(), ::tolower); 
    if(lang == "english-uk") {
        m_lang += "en-GB";
    } 
    else if(lang == "german") {
        m_lang += "de-DE"; 
    }
    else if (lang == "spain") {
        m_lang += "es-ES";
    }
    else if (lang == "french") {
        m_lang += "fr-FR";
    }
    else if (lang == "italian") {
        m_lang += "it-IT";
    }
    else {
        m_lang += "en-US"; 
    }
}

void TextToSpeech::setSpeedAndPitch() {
    std::string cmd =
        m_sox+" "+m_out+" "+"/tmp/new.wav"+" "+"tempo"+" "+
        m_speed+" "+"pitch"+" "+m_pitch;
    std::system(cmd.c_str());
}

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
    std::string cmd = m_rm+" "+m_out;
    std::system(cmd.c_str());
}

void TextToSpeech::createAudio(std::string text) {
    std::string out = "-w=" + m_out; 
    text = "\"" + text + "\"";
    std::string cmd = 
        m_pico+" "+m_lang+" "+out+" "+text;
    std::system(cmd.c_str());
}

void TextToSpeech::createAudio() {
    std::string out = "-w=" + m_out; 
    m_text = "\"" + m_text + "\"";
    std::string cmd = m_pico+" "+m_lang+" "+out+" "+m_text; 
    std::system(cmd.c_str());
}


void TextToSpeech::start() {
    m_text = m_in;
    createAudio(m_text);
    setSpeedAndPitch();
    clearTmp();
}

