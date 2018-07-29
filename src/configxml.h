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

#ifndef SETTINGXML_H
#define SETTINGXML_H

#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include <QDir>
#include "lib/tinyxml/tinyxml2.h"

using namespace tinyxml2;

class ConfigXml {
    private:
        XMLDocument xml;
        XMLNode* node;
        QString m_configPath = "/.config/qpicospeaker/config.xml";
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

        void createXML();
        void read(Ui::QPicoSpeaker *ui);
        void write(Ui::Settings *ui);
};

#endif // SETTINGXML_H
