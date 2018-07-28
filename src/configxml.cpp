#include "configxml.h"
#include "ui_settings.h"
#include "ui_qpicospeaker.h"
#include <iostream>
#include <QFile>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

ConfigXml::ConfigXml(Ui::QPicoSpeaker *ui)
{
    QFile file("/home/philip/Projekte/qt/picospeak/src/qpicospeaker_conf.xml");
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader xml;
        xml.setDevice(&file);
        xml.readNext();
        std::cout << xml.name().toString().toStdString() << std::endl;
        xml.readNext();
        QXmlStreamAttributes attr = xml.attributes();
    }

}
