#ifndef TTS_H
#define TTS_H
#include <string>
#include <unistd.h>

// not implemented now, needed for later versions
enum Engine {
    GOOGLE, // internet connection needed
    ESPEAK,
    PICO2WAVE,
};

class TextToSpeech {
      private:
        std::string m_lang = "-l=";
        std::string m_out = "/tmp/picoTmp.wav";
        std::string m_pico = "pico2wave";
        std::string m_rm = "rm";
        std::string m_sox = "sox";
        std::string m_in = "";
        std::string m_new = "/tmp/new.wav";
        std::string m_text = "";
        std::string m_speed = "1.0";
        std::string m_pitch = "0";
        void checkLanguage(const int& lang);

    public:
        TextToSpeech(const int& lang, std::string& speed, std::string& pitch,
                std::string output, std::string& input);
        ~TextToSpeech();
        void setSpeedAndPitch();
        bool checkProgram(const std::string cmd); 
        void clearTmp();
        void createAudio();
        void createAudio(std::string text);
        void loadText(std::string filePath); 
        void start();
};

#endif //TTS_H
