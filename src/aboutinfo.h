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


#ifndef ABOUTINFO_H
#define ABOUTINFO_H

#include <QWidget>
#include <memory>

namespace Ui {
class AboutInfo;
}

class AboutInfo : public QWidget
{
    Q_OBJECT

public:
    static std::shared_ptr<AboutInfo> open();
    static bool isAlloc();
    std::unique_ptr<Ui::AboutInfo> ui;
    ~AboutInfo();

private:
    explicit AboutInfo(QWidget *parent = nullptr);
    static std::shared_ptr<AboutInfo> instance;

};

#endif // ABOUTINFO_H
