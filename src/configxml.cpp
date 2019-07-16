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
#include <QComboBox>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

using namespace tinyxml2;

// TODO outsource config file
// TODO check if file exists

ConfigXml::ConfigXml() {
    m_path = QString(QDir::homePath()+m_configPath).toStdString();
    std::string config_dir =
            QDir::homePath().toStdString()+"/.config/qpicospeaker/";
    if( !QDir(config_dir.c_str()).exists() ) {
        QDir().mkdir(config_dir.c_str());
    }
    if( !QFileInfo::exists(m_path.c_str())) {
        createXml();
    }

    xml.LoadFile(m_path.c_str());
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

int ConfigXml::getDefTextLang() {
    return (node->FirstChildElement("DefTextLang")->IntText());
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

void ConfigXml::setDefEngine(Engine eng) {
    XMLElement* defEngine = node->FirstChildElement("DefEngine");
    switch (eng) {
        case Engine::ESPEAK: break;
        case Engine::GOOGLE: {
            defEngine->SetText("Google");
        } break;
        case Engine::PICO2WAVE: {
            defEngine->SetText("Pico");
        } break;
    }
    xml.SaveFile(m_path.c_str());
}

void ConfigXml::setPitch(int val) {
    XMLElement* pitch = node->FirstChildElement("Slider")->FirstChildElement("Pitch");
    pitch->SetText(val);
    xml.SaveFile(m_path.c_str());

}

void ConfigXml::setSpeed(int val) {
    XMLElement* speed = node->FirstChildElement("Slider")->FirstChildElement("Speed");
    speed->SetText(val);
    xml.SaveFile(m_path.c_str());
}

void ConfigXml::setVolume(int val) {
    XMLElement* volume = node->FirstChildElement("Slider")->FirstChildElement("Volume");
    volume->SetText(val);
    xml.SaveFile(m_path.c_str());
}

std::vector<QCheckBox*> ConfigXml::getUiLang(Ui::Settings *ui) {
    std::vector<QCheckBox*> uiVec;
    uiVec.push_back(ui->cbDE);
    uiVec.push_back(ui->cbEN);
    uiVec.push_back(ui->cbES);
    uiVec.push_back(ui->cbFR);
    uiVec.push_back(ui->cbIT);
    return uiVec;
}

std::vector<XMLElement*> ConfigXml::getXmlLang() {
    std::vector<XMLElement*> xlVec;
    xlVec.push_back(node->FirstChildElement("Lang")->FirstChildElement("de"));
    xlVec.push_back(node->FirstChildElement("Lang")->FirstChildElement("en"));
    xlVec.push_back(node->FirstChildElement("Lang")->FirstChildElement("es"));
    xlVec.push_back(node->FirstChildElement("Lang")->FirstChildElement("fr"));
    xlVec.push_back(node->FirstChildElement("Lang")->FirstChildElement("it"));
    return xlVec;
}



void ConfigXml::createXml() {
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
    XMLElement *rDefTextLang = doc.NewElement("DefTextLang");
    rDefTextLang->SetText(Language::EN_US);
    root->InsertEndChild(rDefTextLang);
    createXmlEngines(doc, root);
    createXmlSlider(doc, root, xmlVec);
    createXmlLang(doc, root, xmlVec);
    XMLError xml_err = doc.SaveFile(m_path.c_str());
    std::cout << xml_err << std::endl;
}

void ConfigXml::createXmlEngines(XMLDocument &doc, XMLNode* root) {
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
}

void ConfigXml::createXmlSlider(XMLDocument &doc, XMLNode* root, std::vector<XMLElement*> &xmlVec) {
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
}

void ConfigXml::createXmlLang(XMLDocument &doc, XMLNode* root, std::vector<XMLElement*> &xmlVec) {
    XMLElement *rLang = doc.NewElement("Lang");
    xmlVec.push_back(doc.NewElement("de"));
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
}


void ConfigXml::disableUiLang(QComboBox* cbl, std::string lang) {
    if(lang == "de")  cbl->setItemData(Language::DE, QSize(-1,-1), Qt::SizeHintRole);
    if(lang == "en") {
        cbl->setItemData(Language::EN_US, QSize(-1,-1), Qt::SizeHintRole);
        cbl->setItemData(Language::EN_UK, QSize(-1,-1), Qt::SizeHintRole);
    }
    if(lang == "es")  cbl->setItemData(Language::ES, QSize(-1,-1), Qt::SizeHintRole);
    if(lang == "fr")  cbl->setItemData(Language::FR, QSize(-1,-1), Qt::SizeHintRole);
    if(lang == "it")  cbl->setItemData(Language::IT, QSize(-1,-1), Qt::SizeHintRole);

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
    ui->cmbLang->setCurrentIndex(getDefTextLang());

    QComboBox* cbl = ui->cmbLang;
    std::vector<XMLElement*> xlVec = getXmlLang();
    if(static_cast<size_t>(cbl->count()) == xlVec.size()+1) {
        for(auto& lang : xlVec) {
            if(!lang->BoolText()) {
               disableUiLang(cbl, std::string(lang->Name()));
            }
        }
    } xlVec.clear();
}

void ConfigXml::read(Ui::Settings *ui) {
    ui->sbDefVol->setValue(getVolume());
    ui->sbDefPitch->setValue(getPitch());
    ui->sbDefSpeed->setValue(getSpeed());

    if(getDefEngine() == "Espeak") {
        ui->cmbDefEng->setCurrentIndex(static_cast<int>(Engine::ESPEAK));
    } else if(getDefEngine() == "Google") {
        ui->cmbDefEng->setCurrentIndex(static_cast<int>(Engine::GOOGLE));
    } else {
        ui->cmbDefEng->setCurrentIndex(static_cast<int>(Engine::PICO2WAVE));
    }

    std::vector<QCheckBox*> uiVec = getUiLang(ui);
    std::vector<XMLElement*> xlVec = getXmlLang();

    if(uiVec.size() == xlVec.size()) {
        for(size_t i = 0; i < uiVec.size(); i++) {
            uiVec[i]->setChecked(xlVec[i]->BoolText());
        }
    } xlVec.clear();
}

void ConfigXml::write(Ui::Settings *ui) {
    setDefEngine(static_cast<Engine>(ui->cmbDefEng->currentIndex()));
    setPitch(ui->sbDefPitch->value());
    setSpeed(ui->sbDefSpeed->value());
    setVolume(ui->sbDefVol->value());

    std::vector<QCheckBox*> uiVec = getUiLang(ui);
    std::vector<XMLElement*> xlVec = getXmlLang();

    if(uiVec.size() == xlVec.size()) {
        for(size_t i = 0; i < uiVec.size(); i++) {
            xlVec[i]->SetText(uiVec[i]->isChecked());
        }
    } xlVec.clear();
    xml.SaveFile(m_path.c_str());
 }
