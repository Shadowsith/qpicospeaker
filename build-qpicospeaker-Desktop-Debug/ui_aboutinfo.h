/********************************************************************************
** Form generated from reading UI file 'aboutinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTINFO_H
#define UI_ABOUTINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutInfo
{
public:
    QLabel *lblVer;
    QLabel *lblQt;
    QLabel *lblDev;
    QLabel *lblCtc;
    QLabel *lblLic;
    QLabel *lblVerVal;
    QLabel *lblQtVal;
    QLabel *lblDevVal;
    QLabel *lblCtcVal;
    QLabel *lblLicVal;

    void setupUi(QWidget *AboutInfo)
    {
        if (AboutInfo->objectName().isEmpty())
            AboutInfo->setObjectName(QStringLiteral("AboutInfo"));
        AboutInfo->resize(209, 198);
        lblVer = new QLabel(AboutInfo);
        lblVer->setObjectName(QStringLiteral("lblVer"));
        lblVer->setGeometry(QRect(20, 10, 58, 18));
        lblQt = new QLabel(AboutInfo);
        lblQt->setObjectName(QStringLiteral("lblQt"));
        lblQt->setGeometry(QRect(20, 50, 71, 18));
        lblDev = new QLabel(AboutInfo);
        lblDev->setObjectName(QStringLiteral("lblDev"));
        lblDev->setGeometry(QRect(20, 90, 71, 18));
        lblCtc = new QLabel(AboutInfo);
        lblCtc->setObjectName(QStringLiteral("lblCtc"));
        lblCtc->setGeometry(QRect(20, 130, 71, 18));
        lblLic = new QLabel(AboutInfo);
        lblLic->setObjectName(QStringLiteral("lblLic"));
        lblLic->setGeometry(QRect(20, 170, 71, 18));
        lblVerVal = new QLabel(AboutInfo);
        lblVerVal->setObjectName(QStringLiteral("lblVerVal"));
        lblVerVal->setGeometry(QRect(110, 10, 58, 18));
        lblQtVal = new QLabel(AboutInfo);
        lblQtVal->setObjectName(QStringLiteral("lblQtVal"));
        lblQtVal->setGeometry(QRect(110, 50, 58, 18));
        lblDevVal = new QLabel(AboutInfo);
        lblDevVal->setObjectName(QStringLiteral("lblDevVal"));
        lblDevVal->setGeometry(QRect(110, 90, 101, 18));
        lblCtcVal = new QLabel(AboutInfo);
        lblCtcVal->setObjectName(QStringLiteral("lblCtcVal"));
        lblCtcVal->setGeometry(QRect(110, 120, 81, 31));
        lblCtcVal->setAcceptDrops(false);
        lblCtcVal->setWordWrap(true);
        lblLicVal = new QLabel(AboutInfo);
        lblLicVal->setObjectName(QStringLiteral("lblLicVal"));
        lblLicVal->setGeometry(QRect(110, 170, 71, 18));

        retranslateUi(AboutInfo);

        QMetaObject::connectSlotsByName(AboutInfo);
    } // setupUi

    void retranslateUi(QWidget *AboutInfo)
    {
        AboutInfo->setWindowTitle(QApplication::translate("AboutInfo", "Form", nullptr));
        lblVer->setText(QApplication::translate("AboutInfo", "Verson:", nullptr));
        lblQt->setText(QApplication::translate("AboutInfo", "Qt Version:", nullptr));
        lblDev->setText(QApplication::translate("AboutInfo", "Developer:", nullptr));
        lblCtc->setText(QApplication::translate("AboutInfo", "Contact:", nullptr));
        lblLic->setText(QApplication::translate("AboutInfo", "Licence:", nullptr));
        lblVerVal->setText(QApplication::translate("AboutInfo", "0.9", nullptr));
        lblQtVal->setText(QApplication::translate("AboutInfo", "5.11.0", nullptr));
        lblDevVal->setText(QApplication::translate("AboutInfo", "Philip Mayer", nullptr));
        lblCtcVal->setText(QApplication::translate("AboutInfo", "philip.mayer @shadowsith.de", nullptr));
        lblLicVal->setText(QApplication::translate("AboutInfo", "MIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutInfo: public Ui_AboutInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTINFO_H
