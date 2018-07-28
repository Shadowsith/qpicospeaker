#ifndef SETTINGXML_H
#define SETTINGXML_H

#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class ConfigXml {
    private:
        XMLDocument xml;
        XMLNode* node;
        QString m_configPath = "/home/philip/Projekte/qt/picospeak/src/qpicospeaker_conf.xml";
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
        ConfigXml();
        ~ConfigXml();
        QString getAudioPath();
        bool isEspeak();
        bool isGoogle();
        bool isPico();
        int getVolume();
        int getSpeed();
        int getPitch();

        void setAudioPath();
        void setEspeak();
        void setGoogle();
        void setPico();
        void setVolume();
        void setSpeed();
        void setPitch();

        void read(Ui::QPicoSpeaker *ui);
        void write(Ui::Settings *ui);
};

#endif // SETTINGXML_H
