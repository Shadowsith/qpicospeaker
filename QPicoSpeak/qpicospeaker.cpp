#include "qpicospeaker.h"
#include "ui_qpicospeaker.h"
#include <qslider.h>
#include <thread>
#include <qthread.h>
#include <texttospeech.h>
#include <qprocess.h>
#include <QUrl>
#include <QTextEdit>
#include <QCheckBox>
#include <QScrollArea>
#include <QComboBox>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>

QPicoSpeaker::QPicoSpeaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPicoSpeaker)
{
    /* buttons */
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, [=] {
        close();
    });
    connect(ui->btnPlay, &QPushButton::clicked, [=] {
        play();
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
            ui->btnPlay->setText("⯈ Play");
        }
        else if(player->state() == QMediaPlayer::PausedState) {
            ui->btnPlay->setText("⯈ Resume");
        } else {
            ui->btnPlay->setText("⏸ Pause");
        }
    });
    /* Menu bar */
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
    /* init */
    ui->cbSettings->setChecked(false);
    resize(false);
}

QPicoSpeaker::~QPicoSpeaker()
{
    delete ui;
}

void QPicoSpeaker::play() {
    if(player->state() == QMediaPlayer::StoppedState) {
        m_text = ui->tePlay->toPlainText();
        QString lang = ui->cmbLang->currentText();
        QString speed = ui->lblSpeedVal->text();
        QString pitch = ui->lblPitchVal->text();
        TextToSpeech t(lang.toStdString(), speed.toStdString(),
                       pitch.toStdString(), "", m_text.toStdString(), FROM_TEXT);
        //TextToSpeech t(lang.toStdString(), speed.toStdString());
        t.process();
        player->setMedia(QUrl::fromLocalFile("/tmp/new.wav"));
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
        ui->cbSettings->setGeometry(ui->cbSettings->x(), ui->cbSettings->y()+growth,
                                    ui->cbSettings->width(), ui->cbSettings->height());
        ui->saSliders->hide();
    }
}

void QPicoSpeaker::stop() {
    player->stop();
}

