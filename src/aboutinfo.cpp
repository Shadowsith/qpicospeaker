#include "aboutinfo.h"
#include "ui_aboutinfo.h"

AboutInfo::AboutInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutInfo)
{
    ui->setupUi(this);
}

AboutInfo::~AboutInfo()
{
    delete ui;
}

AboutInfo* AboutInfo::instance = 0;

AboutInfo* AboutInfo::open() {
    if(!instance) {
        instance = new AboutInfo();
        return instance;
    } else {
        return instance;
    }
}
