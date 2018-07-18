#ifndef QPICOSPEAKER_H
#define QPICOSPEAKER_H

#include "aboutinfo.h"
#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include <QTranslator>
#include <QtMultimedia/QMediaPlayer>


namespace Ui {
class QPicoSpeaker;
}

class QPicoSpeaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit QPicoSpeaker(QWidget *parent = 0);
    ~QPicoSpeaker();

private:
    Ui::QPicoSpeaker *ui;
    AboutInfo* info;
    QMediaPlayer *player = new QMediaPlayer;
    QTranslator tl;
    void conWin();
    void conMenu();
    void conTranl();
    //@Override
    void closeEvent(QCloseEvent *cev);
    void play();
    void stop();
    void resize(bool checked);
    QString m_text = "";
    void openFile();
    void openInfo();
    void saveText();
    void saveAudio();
};

#endif // QPICOSPEAKER_H
