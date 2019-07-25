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

#include "texttospeech.h"
#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include <QDir>
#include <memory>
#include "lib/tinyxml/tinyxml2.h"

using namespace tinyxml2;

class ConfigXml {
    private:
        XMLDocument xml;
        XMLNode* node;
        const QString m_configPath = "/.config/qpicospeaker/config.xml";
        QString m_audioPath;
        std::string m_path;

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
        void createXml();
        void createXmlEngines(XMLDocument &doc, XMLNode* root);
        void createXmlSlider(XMLDocument &doc, XMLNode* root,
                             std::vector<XMLElement*> &xmlVec);

        void createXmlLang(XMLDocument &doc, XMLNode* root,
                           std::vector<XMLElement*> &xmlVec);
        void disableUiLang(QComboBox* cbl, std::string lang);

    public:
        ConfigXml();
        ~ConfigXml();
        QString getAudioPath();
        bool isEspeak();
        bool isGoogle();
        bool isPico();
        std::string getDefEngine();
        int getDefTextLang();
        int getVolume();
        int getSpeed();
        int getPitch();
        std::vector<QCheckBox*> getUiLang(std::shared_ptr<Ui::Settings> ui);
        std::vector<XMLElement*> getXmlLang();

        void setAudioPath();
        void setDefEngine(Engine eng);
        void setVolume(int volume);
        void setSpeed(int speed);
        void setPitch(int pitch);

        void read(std::shared_ptr<Ui::QPicoSpeaker> ui);
        void read(std::shared_ptr<Ui::Settings> ui);
        void write(std::shared_ptr<Ui::Settings> ui);

};

#endif // SETTINGXML_H
