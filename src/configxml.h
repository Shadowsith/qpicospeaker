#ifndef SETTINGXML_H
#define SETTINGXML_H

#include "ui_settings.h"
#include "ui_qpicospeaker.h"

class ConfigXml {
    private:
        QString m_configPath = "./qpicospeaker_conf.xml";
        QString m_audioPath;

        //enabled (visible) engines
        bool m_espeak;
        bool m_google;
        bool m_pico;

        // qslider
        int m_volume;
        int m_speed;
        int m_pitch;

        // enabled languages
        bool m_DE;
        bool m_EN;
        bool m_ES;
        bool m_FR;
        bool m_IT;

    public:
        ConfigXml(Ui::QPicoSpeaker *ui);
        ConfigXml(Ui::Settings *ui);
        QString getAudioPath();
        int getVolume();
        int getSpeed();
        int getPitch();

        void setAudioPath();
        void setVolume();
        void setSpeed();
        void setPitch();

        void read();
        void write();
};

#endif // SETTINGXML_H
