#ifndef ABOUTINFO_H
#define ABOUTINFO_H

#include <QWidget>

namespace Ui {
class AboutInfo;
}

class AboutInfo : public QWidget
{
    Q_OBJECT

public:
    static AboutInfo* open();
    static bool isAlloc();

private:
    explicit AboutInfo(QWidget *parent = 0);
    Ui::AboutInfo *ui;
    ~AboutInfo();
    static AboutInfo* instance;

};

#endif // ABOUTINFO_H
