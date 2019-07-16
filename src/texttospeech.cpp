/*
Project:     QPicoSpeaker
Description: A Qt frontend for SVOX - pico2wave, Google TTS and eSpeak
Author:      Philip Mayer (Shadowsith) <philip.mayer@shadowsith.de>
Copyright:   2018 Philip Mayer
License:     GPLv3+

QPicoSpeaker is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QPicoSpeaker is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QPicoSpeaker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <regex>
#include <vector>
#include <algorithm>
#include "texttospeech.h"

// constructor & destructor -----------------------------------------------------------------------
TextToSpeech::TextToSpeech(const Language lang,
    std::string& speed, std::string& pitch, std::string& output,
    std::string& text, Engine eng) {
    _eng = eng;
    checkLanguage(lang);
    if(speed != "")     _speed = speed;
    if(pitch != "")     _pitch = pitch;
    if(output != "")    _out = output;
    if(text != "")      _text = text;
}

TextToSpeech::~TextToSpeech() {}

// privat methods --------------------------------------------------------------------------------- 
void TextToSpeech::checkLanguage(const Language& lang) {
    switch(_eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: {
            switch(lang) {
                case Language::DE:    _lang = "&tl=de"; break;
                case Language::EN_US: _lang = "&tl=en"; break;
                case Language::EN_UK: _lang = "&tl=en"; break;
                case Language::ES:    _lang = "&tl=es"; break;
                case Language::FR:    _lang = "&tl=fr"; break;
                case Language::IT:    _lang = "&tl=it"; break;
            }
        } break;
        case Engine::PICO2WAVE: {
            switch(lang) {
                case Language::DE:    _lang += "de-DE"; break;
                case Language::EN_US: _lang += "en-US"; break;
                case Language::EN_UK: _lang += "en-GB"; break;
                case Language::ES: _lang += "es-ES"; break;
                case Language::FR: _lang += "fr-FR"; break;
                case Language::IT: _lang += "it-IT"; break;
                // default: _lang += "en-US"; break;
            }
        } break;
    }
}


void TextToSpeech::recordFiles() {
    for (size_t i = 0; i < m_gMsgParts.size(); i++) {
        std::string tmp = "/tmp/gTmp" + std::to_string(i) + ".wav";
        std::string message = "\"" + m_google + m_gMsgParts[i] + _lang + "\"";
        _cmd = "mplayer "+message+" -vc null -vo null -ao pcm:fast:waveheader:file="+tmp;
        std::system(_cmd.c_str());
    }
}


void TextToSpeech::saveParts() {
    std::vector<std::string> words = split(_text," ");
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
    if(request.length() < 200) {
        m_gMsgParts.push_back(request);
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
    switch(_eng) {
        case Engine::ESPEAK: break;
        case Engine::PICO2WAVE: 
            _cmd = m_rm+" "+m_tmp;
            break;
        case Engine::GOOGLE:
            _cmd = m_rm+" /tmp/gTmp*.wav "+m_tmp;
            break;
    }
    std::system(_cmd.c_str());
}

void TextToSpeech::createAudio() {
    switch(_eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: { 
            saveParts();
            recordFiles();
            _cmd = m_sox+" "+"/tmp/gTmp*.wav"+" "+m_tmp;
            std::system(_cmd.c_str());
        } break;
        case Engine::PICO2WAVE: {
            std::string tmp = "-w=" + m_tmp;
            _text = "\"" + _text + "\"";
            _cmd = m_pico+" "+_lang+" "+tmp+" "+_text;
            std::system(_cmd.c_str());
        } break;
    }
}

void TextToSpeech::setSpeedAndPitch() {
    _cmd = m_sox+" "+m_tmp+" "+_out+" "+"tempo"+" "+_speed+" "+"pitch"+" "+_pitch;
    std::system(_cmd.c_str());
}

void TextToSpeech::start() {
    createAudio();
    setSpeedAndPitch();
    clearTmp();
}

// operators-----------------------------------------------------------------------------------------


