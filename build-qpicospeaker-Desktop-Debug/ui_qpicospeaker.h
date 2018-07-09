/********************************************************************************
** Form generated from reading UI file 'qpicospeaker.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPICOSPEAKER_H
#define UI_QPICOSPEAKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QPicoSpeaker
{
public:
    QAction *actionAbout;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_As;
    QAction *actionClose;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionInsert;
    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionQPicoSpeaker;
    QAction *actionLanguage;
    QWidget *centralWidget;
    QComboBox *cmbLang;
    QTextEdit *tePlay;
    QLabel *lblLang;
    QPushButton *btnClose;
    QLabel *lblInputDesc;
    QPushButton *btnStop;
    QPushButton *btnPlay;
    QScrollArea *saSliders;
    QWidget *scrollAreaWidgetContents;
    QLabel *lblPitchVal;
    QLabel *lblSpeed;
    QLabel *lblSpeedVal;
    QLabel *lblPitch;
    QSlider *hsSpeed;
    QSlider *hsPitch;
    QLabel *lblVolume;
    QLabel *lblVolumeVal;
    QSlider *hsVolume;
    QCheckBox *cbSettings;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuSettings;

    void setupUi(QMainWindow *QPicoSpeaker)
    {
        if (QPicoSpeaker->objectName().isEmpty())
            QPicoSpeaker->setObjectName(QStringLiteral("QPicoSpeaker"));
        QPicoSpeaker->resize(454, 508);
        QPicoSpeaker->setStyleSheet(QLatin1String("QMenu {\n"
"	border-style: solid;\n"
"	border-width: 5px;\n"
"}"));
        actionAbout = new QAction(QPicoSpeaker);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon(QIcon::fromTheme(QStringLiteral("help-about")));
        actionAbout->setIcon(icon);
        actionNew = new QAction(QPicoSpeaker);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setCheckable(false);
        QIcon icon1;
        QString iconThemeName = QStringLiteral("document-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionNew->setIcon(icon1);
        actionOpen = new QAction(QPicoSpeaker);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        iconThemeName = QStringLiteral("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionOpen->setIcon(icon2);
        actionSave_As = new QAction(QPicoSpeaker);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        QIcon icon3;
        iconThemeName = QStringLiteral("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_As->setIcon(icon3);
        actionClose = new QAction(QPicoSpeaker);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        QIcon icon4;
        iconThemeName = QStringLiteral("window-close");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionClose->setIcon(icon4);
        actionCut = new QAction(QPicoSpeaker);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon5;
        iconThemeName = QStringLiteral("edit-cut");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCut->setIcon(icon5);
        actionCopy = new QAction(QPicoSpeaker);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon6;
        iconThemeName = QStringLiteral("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCopy->setIcon(icon6);
        actionInsert = new QAction(QPicoSpeaker);
        actionInsert->setObjectName(QStringLiteral("actionInsert"));
        QIcon icon7;
        iconThemeName = QStringLiteral("edit-paste");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionInsert->setIcon(icon7);
        actionPlay = new QAction(QPicoSpeaker);
        actionPlay->setObjectName(QStringLiteral("actionPlay"));
        QIcon icon8(QIcon::fromTheme(QStringLiteral("media-playback-start")));
        actionPlay->setIcon(icon8);
        actionPause = new QAction(QPicoSpeaker);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        QIcon icon9(QIcon::fromTheme(QStringLiteral("media-playback-pause")));
        actionPause->setIcon(icon9);
        actionStop = new QAction(QPicoSpeaker);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon10(QIcon::fromTheme(QStringLiteral("media-playback-stop")));
        actionStop->setIcon(icon10);
        actionQPicoSpeaker = new QAction(QPicoSpeaker);
        actionQPicoSpeaker->setObjectName(QStringLiteral("actionQPicoSpeaker"));
        QIcon icon11(QIcon::fromTheme(QStringLiteral("audio-volume-high")));
        actionQPicoSpeaker->setIcon(icon11);
        actionLanguage = new QAction(QPicoSpeaker);
        actionLanguage->setObjectName(QStringLiteral("actionLanguage"));
        QIcon icon12(QIcon::fromTheme(QStringLiteral("languages")));
        actionLanguage->setIcon(icon12);
        centralWidget = new QWidget(QPicoSpeaker);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        cmbLang = new QComboBox(centralWidget);
        cmbLang->addItem(QString());
        cmbLang->addItem(QString());
        cmbLang->addItem(QString());
        cmbLang->addItem(QString());
        cmbLang->addItem(QString());
        cmbLang->addItem(QString());
        cmbLang->setObjectName(QStringLiteral("cmbLang"));
        cmbLang->setGeometry(QRect(130, 230, 111, 30));
        cmbLang->setMinimumSize(QSize(100, 0));
        cmbLang->setLayoutDirection(Qt::LeftToRight);
        cmbLang->setStyleSheet(QLatin1String("#cmbLang {\n"
"	padding-left: 5px;\n"
"}"));
        cmbLang->setMaxVisibleItems(10);
        tePlay = new QTextEdit(centralWidget);
        tePlay->setObjectName(QStringLiteral("tePlay"));
        tePlay->setGeometry(QRect(20, 30, 411, 190));
        lblLang = new QLabel(centralWidget);
        lblLang->setObjectName(QStringLiteral("lblLang"));
        lblLang->setGeometry(QRect(30, 230, 81, 20));
        btnClose = new QPushButton(centralWidget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(350, 440, 80, 26));
        btnClose->setCursor(QCursor(Qt::PointingHandCursor));
        lblInputDesc = new QLabel(centralWidget);
        lblInputDesc->setObjectName(QStringLiteral("lblInputDesc"));
        lblInputDesc->setGeometry(QRect(20, 10, 321, 20));
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans"));
        font.setPointSize(11);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblInputDesc->setFont(font);
        lblInputDesc->setTextFormat(Qt::AutoText);
        btnStop = new QPushButton(centralWidget);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setGeometry(QRect(110, 440, 80, 26));
        btnStop->setCursor(QCursor(Qt::PointingHandCursor));
        btnPlay = new QPushButton(centralWidget);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));
        btnPlay->setGeometry(QRect(20, 440, 80, 26));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnPlay->sizePolicy().hasHeightForWidth());
        btnPlay->setSizePolicy(sizePolicy);
        btnPlay->setCursor(QCursor(Qt::PointingHandCursor));
        saSliders = new QScrollArea(centralWidget);
        saSliders->setObjectName(QStringLiteral("saSliders"));
        saSliders->setGeometry(QRect(20, 300, 411, 131));
        saSliders->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 129));
        lblPitchVal = new QLabel(scrollAreaWidgetContents);
        lblPitchVal->setObjectName(QStringLiteral("lblPitchVal"));
        lblPitchVal->setGeometry(QRect(310, 90, 40, 20));
        lblSpeed = new QLabel(scrollAreaWidgetContents);
        lblSpeed->setObjectName(QStringLiteral("lblSpeed"));
        lblSpeed->setGeometry(QRect(10, 10, 58, 18));
        lblSpeedVal = new QLabel(scrollAreaWidgetContents);
        lblSpeedVal->setObjectName(QStringLiteral("lblSpeedVal"));
        lblSpeedVal->setGeometry(QRect(310, 10, 40, 20));
        lblSpeedVal->setStyleSheet(QStringLiteral(""));
        lblPitch = new QLabel(scrollAreaWidgetContents);
        lblPitch->setObjectName(QStringLiteral("lblPitch"));
        lblPitch->setGeometry(QRect(10, 90, 58, 18));
        hsSpeed = new QSlider(scrollAreaWidgetContents);
        hsSpeed->setObjectName(QStringLiteral("hsSpeed"));
        hsSpeed->setGeometry(QRect(110, 10, 181, 31));
        hsSpeed->setMinimum(0);
        hsSpeed->setMaximum(20);
        hsSpeed->setSingleStep(1);
        hsSpeed->setValue(10);
        hsSpeed->setOrientation(Qt::Horizontal);
        hsPitch = new QSlider(scrollAreaWidgetContents);
        hsPitch->setObjectName(QStringLiteral("hsPitch"));
        hsPitch->setGeometry(QRect(110, 90, 181, 31));
        hsPitch->setMinimum(-1000);
        hsPitch->setMaximum(1000);
        hsPitch->setSingleStep(100);
        hsPitch->setPageStep(100);
        hsPitch->setValue(0);
        hsPitch->setSliderPosition(0);
        hsPitch->setOrientation(Qt::Horizontal);
        lblVolume = new QLabel(scrollAreaWidgetContents);
        lblVolume->setObjectName(QStringLiteral("lblVolume"));
        lblVolume->setGeometry(QRect(10, 50, 58, 18));
        lblVolumeVal = new QLabel(scrollAreaWidgetContents);
        lblVolumeVal->setObjectName(QStringLiteral("lblVolumeVal"));
        lblVolumeVal->setGeometry(QRect(310, 50, 40, 20));
        hsVolume = new QSlider(scrollAreaWidgetContents);
        hsVolume->setObjectName(QStringLiteral("hsVolume"));
        hsVolume->setGeometry(QRect(110, 50, 181, 31));
        hsVolume->setMinimum(0);
        hsVolume->setMaximum(100);
        hsVolume->setSingleStep(1);
        hsVolume->setValue(50);
        hsVolume->setSliderPosition(50);
        hsVolume->setOrientation(Qt::Horizontal);
        saSliders->setWidget(scrollAreaWidgetContents);
        cbSettings = new QCheckBox(centralWidget);
        cbSettings->setObjectName(QStringLiteral("cbSettings"));
        cbSettings->setGeometry(QRect(30, 270, 141, 24));
        QPicoSpeaker->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QPicoSpeaker);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 454, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        QPicoSpeaker->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionClose);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionInsert);
        menuEdit->addSeparator();
        menuEdit->addAction(actionPlay);
        menuEdit->addAction(actionPause);
        menuEdit->addAction(actionStop);
        menuHelp->addAction(actionAbout);
        menuSettings->addSeparator();
        menuSettings->addAction(actionQPicoSpeaker);
        menuSettings->addAction(actionLanguage);

        retranslateUi(QPicoSpeaker);

        QMetaObject::connectSlotsByName(QPicoSpeaker);
    } // setupUi

    void retranslateUi(QMainWindow *QPicoSpeaker)
    {
        QPicoSpeaker->setWindowTitle(QApplication::translate("QPicoSpeaker", "qpicospeaker", nullptr));
        actionAbout->setText(QApplication::translate("QPicoSpeaker", "&About", nullptr));
        actionNew->setText(QApplication::translate("QPicoSpeaker", "&New", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("QPicoSpeaker", "&Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_As->setText(QApplication::translate("QPicoSpeaker", "&Save As", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_As->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("QPicoSpeaker", "&Close", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClose->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionCut->setText(QApplication::translate("QPicoSpeaker", "&Cut", nullptr));
        actionCopy->setText(QApplication::translate("QPicoSpeaker", "C&opy", nullptr));
        actionInsert->setText(QApplication::translate("QPicoSpeaker", "&Paste", nullptr));
        actionPlay->setText(QApplication::translate("QPicoSpeaker", "P&lay", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPlay->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionPause->setText(QApplication::translate("QPicoSpeaker", "Pause", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPause->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionStop->setText(QApplication::translate("QPicoSpeaker", "&Stop", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStop->setShortcut(QApplication::translate("QPicoSpeaker", "Ctrl+H", nullptr));
#endif // QT_NO_SHORTCUT
        actionQPicoSpeaker->setText(QApplication::translate("QPicoSpeaker", "QPicoSpeaker", nullptr));
        actionLanguage->setText(QApplication::translate("QPicoSpeaker", "Language", nullptr));
        cmbLang->setItemText(0, QApplication::translate("QPicoSpeaker", "English-US", nullptr));
        cmbLang->setItemText(1, QApplication::translate("QPicoSpeaker", "English-UK", nullptr));
        cmbLang->setItemText(2, QApplication::translate("QPicoSpeaker", "German", nullptr));
        cmbLang->setItemText(3, QApplication::translate("QPicoSpeaker", "Spain", nullptr));
        cmbLang->setItemText(4, QApplication::translate("QPicoSpeaker", "French", nullptr));
        cmbLang->setItemText(5, QApplication::translate("QPicoSpeaker", "Italian", nullptr));

        cmbLang->setCurrentText(QApplication::translate("QPicoSpeaker", "English-US", nullptr));
        tePlay->setHtml(QApplication::translate("QPicoSpeaker", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        lblLang->setText(QApplication::translate("QPicoSpeaker", "Language:", nullptr));
        btnClose->setText(QApplication::translate("QPicoSpeaker", "Close", nullptr));
        lblInputDesc->setText(QApplication::translate("QPicoSpeaker", "Enter text for playback:", nullptr));
        btnStop->setText(QApplication::translate("QPicoSpeaker", "\342\226\240 Stop", nullptr));
        btnPlay->setText(QApplication::translate("QPicoSpeaker", "\342\226\266 Play", nullptr));
        lblPitchVal->setText(QApplication::translate("QPicoSpeaker", "0", nullptr));
        lblSpeed->setText(QApplication::translate("QPicoSpeaker", "Speed:", nullptr));
        lblSpeedVal->setText(QApplication::translate("QPicoSpeaker", "1.0", nullptr));
        lblPitch->setText(QApplication::translate("QPicoSpeaker", "Pitch:", nullptr));
        lblVolume->setText(QApplication::translate("QPicoSpeaker", "Volume:", nullptr));
        lblVolumeVal->setText(QApplication::translate("QPicoSpeaker", "50", nullptr));
        cbSettings->setText(QApplication::translate("QPicoSpeaker", "Advanced Settings:", nullptr));
        menuFile->setTitle(QApplication::translate("QPicoSpeaker", "Fi&le", nullptr));
        menuEdit->setTitle(QApplication::translate("QPicoSpeaker", "Edit", nullptr));
        menuHelp->setTitle(QApplication::translate("QPicoSpeaker", "Help", nullptr));
        menuSettings->setTitle(QApplication::translate("QPicoSpeaker", "Setti&ngs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QPicoSpeaker: public Ui_QPicoSpeaker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPICOSPEAKER_H
