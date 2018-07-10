#ifndef QPICOSPEAKER_H
#define QPICOSPEAKER_H

#include "aboutinfo.h"
#include <QMainWindow>
#include <QDir>
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
    AboutInfo* m_info;
    QMediaPlayer *player = new QMediaPlayer;
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
