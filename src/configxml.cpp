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

#include "configxml.h"
#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include "lib/tinyxml/tinyxml2.h"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>


using namespace tinyxml2;

// TODO outsource config file
// TODO check if file exists

ConfigXml::ConfigXml() {
    //TODO add file exisits and create XML if not exists
    std::string path = QString(QDir::homePath()+m_configPath).toStdString();
    struct stat buffer;
    if(stat (path.c_str(), &buffer) == 0) {
        createXML();
    }
    xml.LoadFile(path.c_str());
    node = xml.FirstChildElement("QPicoSpeaker");
}

ConfigXml::~ConfigXml() {}

QString ConfigXml::getAudioPath() {
    XMLElement* path = node->FirstChildElement("path");
    const char* out = path->GetText();
    m_audioPath = QString(out);
    return m_audioPath;
}

bool ConfigXml::isEspeak() {
    XMLElement* engine = node->FirstChildElement("engine");
    XMLElement* espeak = engine->FirstChildElement("espeak");
    espeak->QueryBoolText(&m_espeak);
    return m_espeak;
}

bool ConfigXml::isGoogle() {
    XMLElement* engine = node->FirstChildElement("engine");
    XMLElement* google = engine->FirstChildElement("google");
    google->QueryBoolText(&m_google);
    return m_google;
}

bool ConfigXml::isPico() {
    XMLElement* engine = node->FirstChildElement("engine");
    XMLElement* pico = engine->FirstChildElement("pico");
    pico->QueryBoolText(&m_pico);
    return m_pico;
}

int ConfigXml::getSpeed() {
    XMLElement* slider = node->FirstChildElement("slider");
    XMLElement* speed = slider->FirstChildElement("speed");
    speed->QueryIntText(&m_speed);
    return m_speed;
}

int ConfigXml::getVolume() {
    XMLElement* slider = node->FirstChildElement("slider");
    XMLElement* volume = slider->FirstChildElement("volume");
    volume->QueryIntText(&m_volume);
    return m_volume;
}

int ConfigXml::getPitch() {
    XMLElement* slider = node->FirstChildElement("slider");
    XMLElement* pitch = slider->FirstChildElement("pitch");
    pitch->QueryIntText(&m_pitch);
    return m_pitch;
}

void ConfigXml::createXML() {
    std::string path = QString(QDir::homePath()+m_configPath).toStdString();
    std::vector<XMLElement*> elem;
    XMLDocument doc;
    XMLDeclaration *header = doc.NewDeclaration();
    header->SetValue("xml version=\"1.0\" encoding=\"\"");
    doc.InsertFirstChild(header);
    XMLNode* root = doc.NewElement("QPicoSpeaker");
    doc.InsertEndChild(root);
    XMLElement *rPath = doc.NewElement("path");
    rPath->SetText("/tmp/picospeak.wav");
    root->InsertEndChild(rPath);
    XMLElement *rDefEngine = doc.NewElement("defEngine");
    rDefEngine->SetText("Pico");
    root->InsertEndChild(rDefEngine);
    XMLElement *rEngine = doc.NewElement("engine");
    XMLElement *rEspeak = doc.NewElement("espeak");
    rEspeak->SetText("false");
    XMLElement *rGoogle = doc.NewElement("google");
    rGoogle->SetText("true");
    XMLElement *rPico = doc.NewElement("pico");
    rPico->SetText("true");
    rEngine->InsertEndChild(rEspeak);
    rEngine->InsertEndChild(rGoogle);
    rEngine->InsertEndChild(rPico);
    root->InsertEndChild(rEngine);
    XMLElement *rSlider = doc.NewElement("slider");
    elem.push_back(doc.NewElement("speed"));
    elem.at(elem.size()-1)->SetText(10);
    elem.push_back(doc.NewElement("volume"));
    elem.at(elem.size()-1)->SetText(100);
    elem.push_back(doc.NewElement("pitch"));
    elem.at(elem.size()-1)->SetText(0);
    for(auto& itm : elem) {
        rSlider->InsertEndChild(itm);
    }
    elem.clear();

}

void ConfigXml::read(Ui::QPicoSpeaker *ui) {
    ui->hsSpeed->setValue(getSpeed());
    ui->hsVolume->setValue(getVolume());
    ui->hsPitch->setValue(getPitch());
    if(!isEspeak())
        ui->cmbEng->setItemData(0, QSize(-1,-1), Qt::SizeHintRole);
    if(!isGoogle())
        ui->cmbEng->setItemData(1, QSize(-1,-1), Qt::SizeHintRole);
    if(!isPico())
        ui->cmbEng->setItemData(2, QSize(-1,-1), Qt::SizeHintRole);
}
