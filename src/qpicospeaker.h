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

#ifndef QPICOSPEAKER_H
#define QPICOSPEAKER_H

#include "aboutinfo.h"
#include "settings.h"
#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include <QTranslator>
#include <QThread>
#include <QtMultimedia/QMediaPlayer>


namespace Ui {
class QPicoSpeaker;
}

class QPicoSpeaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit QPicoSpeaker(QWidget *parent = nullptr);
    ~QPicoSpeaker();

private:
    std::shared_ptr<Ui::QPicoSpeaker> ui;
    std::shared_ptr<AboutInfo> info;
    std::shared_ptr<Settings> settings;
    std::unique_ptr<QMediaPlayer> player =
            std::unique_ptr<QMediaPlayer>(new QMediaPlayer);
    QTranslator tl;
    std::unique_ptr<QThread> worker;
    void setSpecialCharsToUiItms();
    void conWin();
    void conMenu();
    void conTranl();
    void clearTmp();
    //@Override
    void closeEvent(QCloseEvent* e);
    //@Override
    void changeEvent(QEvent* e);
    //@Override
    void resizeEvent(QResizeEvent* e);
    int play();
    void stop();
    void resize();
    QString m_text = "";
    QString m_audio = "/tmp/picospeak.wav";
    void openFile();
    void openInfo();
    void openSettings();
    void saveText();
    void saveAudio();

};

#endif // QPICOSPEAKER_H
