#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>
#include <thread>
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
                           std::string pitch, std::string output, std::string input, Source from) {
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
    m_source = from;
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
    m_pid = fork();
    if (m_pid > 0) {
        waitpid(m_pid, &m_status, 0);
    } else if (m_pid == 0){
        execl(m_soxExec.c_str(), m_soxExec.c_str(),  m_out.c_str(),
                "/tmp/new.wav", "tempo", m_speed.c_str(),
                "pitch", m_pitch.c_str(), NULL);
    } else {
        std::cout << "fork() failed" << std::endl;
    }
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
    m_pid = fork();
    if (m_pid > 0) {
        waitpid(m_pid, &m_status, 0);
    } else if (m_pid == 0){
        execl(m_rmExec.c_str(), m_rmExec.c_str(), m_out.c_str(), NULL); 
    } else {
        std::cout << "fork() failed" << std::endl;
    }
}

void TextToSpeech::createAudio(std::string text) {
    //pico2wave -l=en-US -w=/tmp/test.wav "$1"
    m_pid = fork();
    if (m_pid > 0) {
        waitpid(m_pid, &m_status, 0);
    } else if (m_pid == 0) {
        std::string out = "-w=" + m_out; 
        text = "\"" + text + "\"";
        execl(m_picoExec.c_str(), m_picoExec.c_str(), m_lang.c_str(), 
            out.c_str(), text.c_str(), NULL);
    } else {
        std::cout << "fork() failed" << std::endl;
    }
}

void TextToSpeech::createAudio() {
    //pico2wave -l=en-US -w=/tmp/test.wav "$1"
    m_pid = fork();
    std::string out = "-w=" + m_out; 
    if (m_pid > 0) {
        waitpid(m_pid, &m_status, 0);
    } else if (m_pid == 0){
        m_text = "\"" + m_text + "\"";
        execl(m_picoExec.c_str(), m_picoExec.c_str(), m_lang.c_str(), 
            out.c_str(), m_text.c_str(), NULL);
    } else {
        std::cout << "fork() failed" << std::endl;
    }
}


void TextToSpeech::loadText(std::string filePath) {
    std::ifstream file(filePath); 
    for(std::string line; std::getline(file,line); ) {
        m_text += line; 
    }
}

void TextToSpeech::work() {
    switch(m_source) {
    case Source::FROM_TEXT: {
        m_text = m_in;
    } break;
    case Source::FROM_FILE: {
        loadText(m_in);
    } break;
    default: break;
    }
    createAudio(m_text);
    setSpeedAndPitch();
    //play(m_new);
    clearTmp();
}

void TextToSpeech::process() {
    std::thread th(&TextToSpeech::work, this);
    th.join();
}

