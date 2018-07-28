#include "configxml.h"
#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>

using namespace tinyxml2;

// TODO outsource config file
// TODO check if file exists

ConfigXml::ConfigXml()
{
    xml.LoadFile(m_configPath.toStdString().c_str());
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
