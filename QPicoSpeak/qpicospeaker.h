#ifndef QPICOSPEAKER_H
#define QPICOSPEAKER_H

#include <QMainWindow>
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
    QMediaPlayer *player = new QMediaPlayer;
    void play();
    void stop();
    void resize(bool checked);
    QString m_text = "";
};

#endif // QPICOSPEAKER_H
