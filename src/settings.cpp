#include "settings.h"
#include "ui_settings.h"
#include <QPushButton>

Settings::Settings(QWidget *parent) : QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, [=] {
        close();
    });
    connect(ui->btnSave, &QPushButton::clicked, [=] {
    });
}

Settings::~Settings() {
    delete ui;
}

Settings* Settings::instance = 0;

Settings* Settings::open() {
    if(!instance) {
        instance = new Settings();
        return instance;
    } else {
        return instance;
    }
}

bool Settings::isAlloc() {
    if(instance) {
        return true;
    } else {
        return false;
    }
}

void Settings::writeXml() {
    // TODO XML Writing
}

