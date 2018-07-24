#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H
#include <string>
#include <vector>

// not implemented now, needed for later versions
enum Engine {
    ESPEAK,
    GOOGLE, // internet connection needed
    PICO2WAVE,
};

class TextToSpeech {
      private:
        std::string m_cmd = "";
        Engine m_eng; 
        std::string m_lang = "-l=";
        std::string m_out = "/tmp/picoTmp.wav";
        const std::string m_pico = "pico2wave";
        const std::string m_mplayer = "mplayer";
        const std::string m_google = 
            "http://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=";
        const std::string m_rm = "rm";
        const std::string m_sox = "sox";
        std::string m_in = "";
        const std::string m_new = "/tmp/new.wav";
        std::string m_text = "";
        std::string m_speed = "1.0";
        std::string m_pitch = "0";
        const size_t m_gRequestLength = 200;
        int m_gTmpFiles = 1; 
        std::vector<std::string> m_gMsgParts;

        void checkLanguage(const int& lang);
        void recordFiles();
        void saveParts();
        std::vector<std::string> split(std::string &str, const std::string delimter);

    public:
        TextToSpeech();
        TextToSpeech(const int& lang, std::string& speed, std::string& pitch,
                std::string output, std::string& text, Engine eng);
        ~TextToSpeech();
        bool checkProgram(const std::string cmd); 
        void clearTmp();
        void createAudio();
        void setSpeedAndPitch();
        void start();
};

#endif //TEXTTOSPEECH_H
