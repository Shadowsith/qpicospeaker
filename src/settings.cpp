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
#include "ui_settings.h"
#include <QPushButton>

Settings::Settings(QWidget *parent) : QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, [=] {
        close();
    });
    connect(ui->btnSave, &QPushButton::clicked, [=] {
    });
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

void Settings::writeXml() {
    // TODO XML Writing
}

