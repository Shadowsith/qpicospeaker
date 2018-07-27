#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    static Settings* open();
    static bool isAlloc();
    Ui::Settings *ui;

private:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    static Settings* instance;

};

#endif // SETTINGS_H
