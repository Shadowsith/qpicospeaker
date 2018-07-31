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
#include "texttospeech.h"
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
    std::string config_dir = QDir::homePath().toStdString()+"/.config/qpicospeaker/";
    struct stat buffer;
    if(stat (config_dir.c_str(), &buffer) != 0) {
        mkdir(config_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(stat (path.c_str(), &buffer) != 0) {
            createXML();
        }
    } else {
         if(stat (path.c_str(), &buffer) != 0) {
            createXML();
        }
    }
    xml.LoadFile(path.c_str());
    node = xml.FirstChildElement("QPicoSpeaker");
}

ConfigXml::~ConfigXml() {}

QString ConfigXml::getAudioPath() {
    XMLElement* path = node->FirstChildElement("Path");
    const char* out = path->GetText();
    m_audioPath = QString(out);
    return m_audioPath;
}

bool ConfigXml::isEspeak() {
    XMLElement* engine = node->FirstChildElement("Engine");
    XMLElement* espeak = engine->FirstChildElement("Espeak");
    espeak->QueryBoolText(&m_espeak);
    return m_espeak;
}

bool ConfigXml::isGoogle() {
    XMLElement* engine = node->FirstChildElement("Engine");
    XMLElement* google = engine->FirstChildElement("Google");
    google->QueryBoolText(&m_google);
    return m_google;
}

bool ConfigXml::isPico() {
    XMLElement* engine = node->FirstChildElement("Engine");
    XMLElement* pico = engine->FirstChildElement("Pico");
    pico->QueryBoolText(&m_pico);
    return m_pico;
}

std::string ConfigXml::getDefEngine() {
    return std::string(node->FirstChildElement("DefEngine")->GetText());
}

int ConfigXml::getSpeed() {
    XMLElement* slider = node->FirstChildElement("Slider");
    XMLElement* speed = slider->FirstChildElement("Speed");
    speed->QueryIntText(&m_speed);
    return m_speed;
}

int ConfigXml::getVolume() {
    XMLElement* slider = node->FirstChildElement("Slider");
    XMLElement* volume = slider->FirstChildElement("Volume");
    volume->QueryIntText(&m_volume);
    return m_volume;
}

int ConfigXml::getPitch() {
    XMLElement* slider = node->FirstChildElement("Slider");
    XMLElement* pitch = slider->FirstChildElement("Pitch");
    pitch->QueryIntText(&m_pitch);
    return m_pitch;
}

void ConfigXml::createXML() {
    std::string path = QString(QDir::homePath()+m_configPath).toStdString();
    std::vector<XMLElement*> xmlVec;
    XMLDocument doc;
    XMLDeclaration *header = doc.NewDeclaration();
    header->SetValue("xml version=\"1.0\" encoding=\"\"");
    doc.InsertFirstChild(header);
    XMLNode* root = doc.NewElement("QPicoSpeaker");
    doc.InsertEndChild(root);
    XMLElement *rPath = doc.NewElement("Path");
    rPath->SetText("/tmp/picospeak.wav");
    root->InsertEndChild(rPath);
    XMLElement *rDefEngine = doc.NewElement("DefEngine");
    rDefEngine->SetText("Pico");
    root->InsertEndChild(rDefEngine);
    XMLElement *rEngine = doc.NewElement("Engine");
    XMLElement *rEspeak = doc.NewElement("Espeak");
    rEspeak->SetText(false);
    XMLElement *rGoogle = doc.NewElement("Google");
    rGoogle->SetText(true);
    XMLElement *rPico = doc.NewElement("Pico");
    rPico->SetText(true);
    rEngine->InsertEndChild(rEspeak);
    rEngine->InsertEndChild(rGoogle);
    rEngine->InsertEndChild(rPico);
    root->InsertEndChild(rEngine);
    XMLElement *rSlider = doc.NewElement("Slider");
    xmlVec.push_back(doc.NewElement("Speed"));
    xmlVec.at(xmlVec.size()-1)->SetText(10);
    xmlVec.push_back(doc.NewElement("Volume"));
    xmlVec.at(xmlVec.size()-1)->SetText(100);
    xmlVec.push_back(doc.NewElement("Pitch"));
    xmlVec.at(xmlVec.size()-1)->SetText(0);
    for(auto& itm : xmlVec) {
        rSlider->InsertEndChild(itm);
    } xmlVec.clear();
    root->InsertEndChild(rSlider);
    XMLElement *rLang = doc.NewElement("Lang");
    xmlVec.push_back(doc.NewElement("de"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    xmlVec.push_back(doc.NewElement("en"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    xmlVec.push_back(doc.NewElement("en"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    xmlVec.push_back(doc.NewElement("es"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    xmlVec.push_back(doc.NewElement("fr"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    xmlVec.push_back(doc.NewElement("it"));
    xmlVec.at(xmlVec.size()-1)->SetText(true);
    for(auto& itm : xmlVec) {
        rLang->InsertEndChild(itm);
    } xmlVec.clear();
    root->InsertEndChild(rLang);
    XMLError xml_err = doc.SaveFile(path.c_str());
    std::cout << xml_err << std::endl;
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
    if(getDefEngine() == "Espeak") {
        ui->cmbEng->setCurrentIndex(static_cast<int>(Engine::ESPEAK));
    } else if(getDefEngine() == "Google") {
        ui->cmbEng->setCurrentIndex(static_cast<int>(Engine::GOOGLE));
    } else {
        ui->cmbEng->setCurrentIndex(static_cast<int>(Engine::PICO2WAVE));
    }
}
