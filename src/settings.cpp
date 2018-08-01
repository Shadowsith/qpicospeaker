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

#include "settings.h"
#include "configxml.h"
#include "ui_settings.h"
#include <QPushButton>
#include <QCheckBox>
#include <QLayout>
#include <iostream>

Settings::Settings(QWidget *parent) : QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    connect(ui->btnClose, &QPushButton::clicked, [=] {
        close();
    });
    connect(ui->btnSave, &QPushButton::clicked, [=] {
        ConfigXml xml;
        xml.write(ui);
    });
    connect(ui->cbLang, &QCheckBox::stateChanged, [=] {
        resize(ui->cbLang->isChecked());
    });
    ConfigXml xml;
    xml.read(ui);
    resize(false);
}

Settings::~Settings() {
    delete ui;
}

Settings* Settings::instance = 0;

Settings* Settings::open() {
    if(!instance) {
        instance = new Settings();
        return instance;
    } else {
        return instance;
    }
}

bool Settings::isAlloc() {
    if(instance) {
        return true;
    } else {
        return false;
    }
}

void Settings::resize(bool check) {
    if(check) {
        ui->scrollArea->show();
        int growth = ui->scrollArea->y()+ui->scrollArea->height()-ui->cbLang->y()-10;
        QRect close = ui->btnClose->geometry();
        close.setTop(close.top()+growth);
        close.setBottom(close.bottom()+growth);
        ui->btnClose->setGeometry(close);
        QRect save = ui->btnSave->geometry();
        save.setY(save.y()+growth);
        save.setBottom(save.bottom()+growth);
        ui->btnSave->setGeometry(save);
        QRect window = this->geometry();
        window.setHeight(window.height()+growth);
        this->setFixedSize(window.size());
    } else {
        ui->scrollArea->hide();
        int shrink = ui->scrollArea->y()+ui->scrollArea->height()-ui->cbLang->y()-10;
        QRect close = ui->btnClose->geometry();
        close.setTop(close.top()-shrink);
        close.setBottom(close.bottom()-shrink);
        ui->btnClose->setGeometry(close);
        QRect save = ui->btnSave->geometry();
        std::cout << save.top() << " " << shrink << std::endl;
        save.setY(save.y()-shrink);
        save.setBottom(save.bottom()-shrink);
        ui->btnSave->setGeometry(save);
        QRect window = this->geometry();
        window.setHeight(window.height()-shrink);
        this->setFixedSize(window.size());
    }
}

