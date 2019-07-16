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

#include "qpicospeaker.h"
#include "ui_qpicospeaker.h"
#include "ui_aboutinfo.h"
#include "aboutinfo.h"
#include "configxml.h"
#include <iostream>
#include <QApplication>
#include <QSlider>
#include <thread>
#include <src/texttospeech.h>
#include <QUrl>
#include <QEvent>
#include <QTextEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QComboBox>
#include <QFileDialog>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QStandardItemModel>
#include <QtMultimedia/QMediaPlayer>

QPicoSpeaker::QPicoSpeaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPicoSpeaker)
{
    ui->setupUi(this);

    conWin();
    conMenu();
    conTranl();
    setSpecialCharsToUiItms();

    /* init */
    ui->cbSettings->setChecked(false);
    resize(false);

    // hide Espeak QComboBox item without deleting it and change index structure
    try{
        ConfigXml xml;
        xml.read(ui);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

}

QPicoSpeaker::~QPicoSpeaker()
{
    delete ui;
    delete player;
}

void QPicoSpeaker::conWin() {
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, [=] {
        clearTmp();
        QApplication::instance()->exit();
    });
    connect(ui->btnPlay, &QPushButton::clicked, [=] {
        std::thread thp(&QPicoSpeaker::play, this); thp.join();
    });
    connect(ui->btnStop, &QPushButton::clicked, [=] {
        stop();
    });
    connect(ui->cbSettings, &QCheckBox::stateChanged, [=] {
        resize(ui->cbSettings->isChecked());
    });
    /* slider */
    connect(ui->hsSpeed, &QSlider::valueChanged, [=] {
        QString val = QString::number(ui->hsSpeed->value());
        if(val.length() == 1) {
            val = "0." + val;
        } else {
            val = val[0] + "." + val[1];
        }
        ui->lblSpeedVal->setText(val);
    });
    connect(ui->hsVolume, &QSlider::valueChanged, [=] {
       QString val = QString::number(ui->hsVolume->value());
       ui->lblVolumeVal->setText(val);
    });
    connect(ui->hsPitch, &QSlider::valueChanged, [=] {
        QString val = QString::number(ui->hsPitch->value());
        ui->lblPitchVal->setText(val);
    });

    /* Media player */
    connect(player, &QMediaPlayer::stateChanged, [=] {
        if(player->state() == QMediaPlayer::StoppedState) {
            ui->btnPlay->setText(tr("&Play"));
        }
        else if(player->state() == QMediaPlayer::PausedState) {
            ui->btnPlay->setText(tr("&Resume"));
        } else {
            ui->btnPlay->setText(tr("&Pause"));
        }
    });
}

void QPicoSpeaker::conMenu() {
    connect(ui->actionNew, &QAction::triggered, [=] {
        ui->tePlay->setText("");
    });
    connect(ui->actionOpen, &QAction::triggered, [=] {
        openFile();
    });
    connect(ui->actionSaveText, &QAction::triggered, [=] {
        saveText();
    });
    connect(ui->actionSaveAudio, &QAction::triggered, [=] {
        saveAudio();
    });
    connect(ui->actionClose, &QAction::triggered, [=] {
        close();
    });
    connect(ui->actionPlay, &QAction::triggered, [=] {
       play();
    });
    connect(ui->actionPause, &QAction::triggered, [=] {
        player->pause();
    });
    connect(ui->actionStop, &QAction::triggered, [=] {
       player->stop();

    });
    connect(ui->actionSettings, &QAction::triggered, [=] {
       openSettings();
    });
    connect(ui->actionAbout, &QAction::triggered, [=] {
        openInfo();
    });
    connect(ui->actionHelp, &QAction::triggered, [=] {
       // TODO Open Help
    });
    connect(ui->actionDev, &QAction::triggered, [=] {
        QDesktopServices::openUrl(QUrl("https://github.com/Shadowsith/qpicospeaker"));
    });
}

void QPicoSpeaker::conTranl() {
    //TODO make install path for translation files
    QApplication::instance()->installTranslator(&tl);
    connect(ui->actionEnglish, &QAction::triggered, [=] {
        tl.load("qpicospeaker_en", QDir::homePath()+QString("/Projekte/qt/picospeak/lang"));
        ui->retranslateUi(this);
    });
    connect(ui->actionGerman, &QAction::triggered, [=] {
        tl.load("qpicospeaker_de", QDir::homePath()+QString("/Projekte/qt/picospeak/lang"));
        ui->retranslateUi(this);
    });
    connect(ui->actionSpanish, &QAction::triggered, [=] {
        tl.load("qpicospeaker_es", QDir::homePath()+QString("/Projekte/qt/picospeak/lang"));
        ui->retranslateUi(this);
    });
}

void QPicoSpeaker::setSpecialCharsToUiItms() {
    ui->lblEng->setText(ui->lblEng->text() + ":");
    ui->lblLang->setText(ui->lblLang->text() + ":");
}

void QPicoSpeaker::clearTmp() {
    QFile f(m_audio);
    f.remove();
}

void QPicoSpeaker::changeEvent(QEvent *ev) {
    if(ev->type() == QEvent::LanguageChange) {
        setSpecialCharsToUiItms();
        if(info->isAlloc()) {
            info->ui->retranslateUi(info);
        }
    }
}

void QPicoSpeaker::closeEvent(QCloseEvent *cev) {
    cev->accept();
    clearTmp();
    QApplication::instance()->exit();
}

void QPicoSpeaker::play() {
    if(player->state() == QMediaPlayer::StoppedState) {
        const int lang = ui->cmbLang->currentIndex();
        const int eng = ui->cmbEng->currentIndex();
        std::string text  = ui->tePlay->toPlainText().toStdString();
        std::string speed = ui->lblSpeedVal->text().toStdString();
        std::string pitch = ui->lblPitchVal->text().toStdString();
        std::string output = m_audio.toStdString();
        switch(eng) {
            case 0: {
                TextToSpeech t(static_cast<Language>(lang), speed, pitch, output, text, Engine::ESPEAK);
            } break;
            case 1: {
                TextToSpeech t(static_cast<Language>(lang), speed, pitch, output, text, Engine::GOOGLE);
                t.start();
            } break;
            default: {
                TextToSpeech t(static_cast<Language>(lang), speed, pitch, output, text, Engine::PICO2WAVE);
                t.start();
            } break;
        }
        player->setMedia(QUrl::fromLocalFile(m_audio));
        player->setVolume(ui->hsVolume->value());
        player->play();
    } else if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void QPicoSpeaker::resize(bool checked) {
    int teNewH = 190;
    if(checked) {
        int shrink = ui->tePlay->height()-teNewH;
        ui->tePlay->setGeometry(ui->tePlay->x(), ui->tePlay->y(),ui->tePlay->width(),teNewH);
        ui->lblLang->setGeometry(ui->lblLang->x(), ui->lblLang->y()-shrink,
                                 ui->lblLang->width(), ui->lblLang->height());
        ui->cmbLang->setGeometry(ui->cmbLang->x(), ui->cmbLang->y()-shrink,
                                 ui->cmbLang->width(), ui->cmbLang->height());
        ui->lblEng->setGeometry(ui->lblEng->x(), ui->lblEng->y()-shrink,
                                ui->lblEng->width(), ui->lblEng->height());
        ui->cmbEng->setGeometry(ui->cmbEng->x(), ui->cmbEng->y()-shrink,
                                 ui->cmbEng->width(), ui->cmbEng->height());
        ui->cbSettings->setGeometry(ui->cbSettings->x(), ui->cbSettings->y()-shrink,
                                    ui->cbSettings->width(), ui->cbSettings->height());
        ui->saSliders->show();
    } else {
        teNewH = 300;
        int growth = teNewH-ui->tePlay->height();
        ui->tePlay->setGeometry(ui->tePlay->x(), ui->tePlay->y(),ui->tePlay->width(),teNewH);
        ui->lblLang->setGeometry(ui->lblLang->x(), ui->lblLang->y()+growth,
                                 ui->lblLang->width(), ui->lblLang->height());
        ui->cmbLang->setGeometry(ui->cmbLang->x(), ui->cmbLang->y()+growth,
                                 ui->cmbLang->width(), ui->cmbLang->height());
                ui->lblEng->setGeometry(ui->lblEng->x(), ui->lblEng->y()+growth,
                                 ui->lblEng->width(), ui->lblEng->height());
        ui->cmbEng->setGeometry(ui->cmbEng->x(), ui->cmbEng->y()+growth,
                                 ui->cmbEng->width(), ui->cmbEng->height());
                ui->cbSettings->setGeometry(ui->cbSettings->x(), ui->cbSettings->y()+growth,
                                    ui->cbSettings->width(), ui->cbSettings->height());
        ui->saSliders->hide();
    }
}

void QPicoSpeaker::stop() {
    player->stop();
}

void QPicoSpeaker::openFile() {
    QString read = "";
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Text"), QDir::homePath(),
                            tr("Text files") + "( *.txt *.text)");
    QFileInfo finfo(filePath);
    if(finfo.exists() && finfo.isFile()) {
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly)) {
            //Some translation here?
            QMessageBox::information(nullptr ,"error", file.errorString());
        }
        QTextStream in(&file);
        while(!in.atEnd()) {
            read += in.readLine() + "\n";
        }
        file.close();
        if(filePath != "") {
            ui->tePlay->setText(read);
        }
    }
}

void QPicoSpeaker::openInfo() {
    info = AboutInfo::open();
    if (info != nullptr) {
        const int fHeight = info->height();
        const int fWidth = info->width();
        info->setFixedSize(fWidth, fHeight);
        info->show();
    }
}

void QPicoSpeaker::openSettings() {
    settings = Settings::open();
    if (settings != nullptr) {
        const int fHeight = settings->height();
        const int fWidth = settings->width();
        settings->setFixedSize(fWidth, fHeight);
        settings->show();
    }
}

void QPicoSpeaker::saveText() {
    QString filePath = QFileDialog::getSaveFileName(
                this, tr("Save File"), QDir::homePath(),
                tr("Text files") + " (*.txt *.text)");
    QFileInfo finfo(filePath);
    if(finfo.exists() && finfo.isFile()) {
        QFile file(filePath);
        if(file.open(QIODevice::ReadWrite)) {
            file.resize(0);
            QTextStream stream(&file);
            stream << ui->tePlay->toPlainText() << endl;
        }
        file.close();
    } else {
        QFile file(filePath);
        if(file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << ui->tePlay->toPlainText() << endl;
        }
        file.close();
    }
}

void QPicoSpeaker::saveAudio() {
    QString filePath = QFileDialog::getSaveFileName(
                this, tr("Save File"), QDir::homePath(),
                tr("Wave audio files") + " (*.wav)");

    QFileInfo finfo(filePath);
    if(finfo.exists() && finfo.isFile()) {
        QFile file(m_audio);
        file.copy(filePath);
        file.close();
    } else {
        QFile file(m_audio);
        file.copy(filePath);
        file.close();
    }
}

