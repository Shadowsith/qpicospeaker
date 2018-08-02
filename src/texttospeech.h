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

#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H
#include <string>
#include <vector>

enum Engine {
    ESPEAK,
    GOOGLE, // internet connection needed
    PICO2WAVE,
};

enum Language {
    DE,
    EN_US,
    EN_UK,
    ES,
    FR,
    IT,
};

class TextToSpeech {
      private:
        std::string m_cmd = "";
        Engine m_eng; 
        std::string m_lang = "-l=";
        const std::string m_tmp = "/tmp/picoTmp.wav";
        const std::string m_pico = "pico2wave";
        const std::string m_mplayer = "mplayer";
        const std::string m_google = 
            "http://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=";
        const std::string m_rm = "rm";
        const std::string m_sox = "sox";
        std::string m_out = "/tmp/picospeak.wav";
        std::string m_text = "";
        std::string m_speed = "1.0";
        std::string m_pitch = "0";
        const size_t m_gRequestLength = 200;
        int m_gTmpFiles = 1; 
        std::vector<std::string> m_gMsgParts;

        void checkLanguage(const Language& lang);
        void recordFiles();
        void saveParts();
        std::vector<std::string> split(std::string &str, const std::string delimter);

    public:
        TextToSpeech(const Language lang, std::string& speed, std::string& pitch,
                std::string& output, std::string& text, Engine eng);
        ~TextToSpeech();
        bool checkProgram(const std::string cmd); 
        void clearTmp();
        void createAudio();
        void setSpeedAndPitch();
        void start();
};

#endif //TEXTTOSPEECH_H
