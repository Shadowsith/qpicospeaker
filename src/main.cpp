#include "qpicospeaker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPicoSpeaker w;
    const int heigth = w.height();
    const int width = w.width();
    w.setFixedSize(width, heigth);
    w.show();

    return a.exec();
}
