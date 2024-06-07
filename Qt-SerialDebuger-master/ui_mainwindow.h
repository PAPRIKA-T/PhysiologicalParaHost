/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QPlainTextEdit *txtRec;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QCheckBox *chkRec;
    QWidget *widget_1;
    QVBoxLayout *verticalLayout;
    QLabel *lblSerialPort;
    myComboBox *cmbSerialPort;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *lblBaudRate;
    QComboBox *cmbBaudRate;
    QLabel *lblStop;
    QComboBox *cmbStop;
    QLabel *lblData;
    QComboBox *cmbData;
    QLabel *lblCheck;
    QComboBox *cmbCheck;
    QLabel *lblSwitch;
    QPushButton *btnSwitch;
    QSpacerItem *verticalSpacer;
    QPushButton *btnClearRec;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnClearSend;
    QCheckBox *chkSend;
    QSpacerItem *verticalSpacer_3;
    QPlainTextEdit *txtSend;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QPushButton *btnSend;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtSendMs;
    QLabel *lblMs;
    QCheckBox *chkTimSend;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 520);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        txtRec = new QPlainTextEdit(centralwidget);
        txtRec->setObjectName(QString::fromUtf8("txtRec"));
        txtRec->setReadOnly(true);

        gridLayout_4->addWidget(txtRec, 0, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(170, 0));
        widget->setMaximumSize(QSize(240, 16777215));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        chkRec = new QCheckBox(widget);
        chkRec->setObjectName(QString::fromUtf8("chkRec"));

        gridLayout_3->addWidget(chkRec, 2, 0, 1, 1);

        widget_1 = new QWidget(widget);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        verticalLayout = new QVBoxLayout(widget_1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblSerialPort = new QLabel(widget_1);
        lblSerialPort->setObjectName(QString::fromUtf8("lblSerialPort"));

        verticalLayout->addWidget(lblSerialPort);

        cmbSerialPort = new myComboBox(widget_1);
        cmbSerialPort->setObjectName(QString::fromUtf8("cmbSerialPort"));

        verticalLayout->addWidget(cmbSerialPort);

        widget_2 = new QWidget(widget_1);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblBaudRate = new QLabel(widget_2);
        lblBaudRate->setObjectName(QString::fromUtf8("lblBaudRate"));

        gridLayout->addWidget(lblBaudRate, 0, 0, 1, 1);

        cmbBaudRate = new QComboBox(widget_2);
        cmbBaudRate->addItem(QString());
        cmbBaudRate->addItem(QString());
        cmbBaudRate->addItem(QString());
        cmbBaudRate->setObjectName(QString::fromUtf8("cmbBaudRate"));

        gridLayout->addWidget(cmbBaudRate, 0, 1, 1, 1);

        lblStop = new QLabel(widget_2);
        lblStop->setObjectName(QString::fromUtf8("lblStop"));

        gridLayout->addWidget(lblStop, 1, 0, 1, 1);

        cmbStop = new QComboBox(widget_2);
        cmbStop->addItem(QString());
        cmbStop->addItem(QString());
        cmbStop->addItem(QString());
        cmbStop->setObjectName(QString::fromUtf8("cmbStop"));

        gridLayout->addWidget(cmbStop, 1, 1, 1, 1);

        lblData = new QLabel(widget_2);
        lblData->setObjectName(QString::fromUtf8("lblData"));

        gridLayout->addWidget(lblData, 2, 0, 1, 1);

        cmbData = new QComboBox(widget_2);
        cmbData->addItem(QString());
        cmbData->addItem(QString());
        cmbData->addItem(QString());
        cmbData->addItem(QString());
        cmbData->setObjectName(QString::fromUtf8("cmbData"));

        gridLayout->addWidget(cmbData, 2, 1, 1, 1);

        lblCheck = new QLabel(widget_2);
        lblCheck->setObjectName(QString::fromUtf8("lblCheck"));

        gridLayout->addWidget(lblCheck, 3, 0, 1, 1);

        cmbCheck = new QComboBox(widget_2);
        cmbCheck->addItem(QString());
        cmbCheck->addItem(QString());
        cmbCheck->addItem(QString());
        cmbCheck->setObjectName(QString::fromUtf8("cmbCheck"));

        gridLayout->addWidget(cmbCheck, 3, 1, 1, 1);

        lblSwitch = new QLabel(widget_2);
        lblSwitch->setObjectName(QString::fromUtf8("lblSwitch"));

        gridLayout->addWidget(lblSwitch, 4, 0, 1, 1);

        btnSwitch = new QPushButton(widget_2);
        btnSwitch->setObjectName(QString::fromUtf8("btnSwitch"));

        gridLayout->addWidget(btnSwitch, 4, 1, 1, 1);


        verticalLayout->addWidget(widget_2);


        gridLayout_3->addWidget(widget_1, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 84, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        btnClearRec = new QPushButton(widget);
        btnClearRec->setObjectName(QString::fromUtf8("btnClearRec"));
        btnClearRec->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(btnClearRec, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 12, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer_2, 3, 0, 1, 1);

        btnClearSend = new QPushButton(widget);
        btnClearSend->setObjectName(QString::fromUtf8("btnClearSend"));
        btnClearSend->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(btnClearSend, 4, 1, 1, 1);

        chkSend = new QCheckBox(widget);
        chkSend->setObjectName(QString::fromUtf8("chkSend"));

        gridLayout_3->addWidget(chkSend, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 8, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer_3, 5, 0, 1, 1);


        gridLayout_4->addWidget(widget, 0, 1, 1, 1);

        txtSend = new QPlainTextEdit(centralwidget);
        txtSend->setObjectName(QString::fromUtf8("txtSend"));
        txtSend->setMinimumSize(QSize(0, 80));
        txtSend->setMaximumSize(QSize(16777215, 100));

        gridLayout_4->addWidget(txtSend, 1, 0, 1, 1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMaximumSize(QSize(240, 16777215));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, -1, -1, -1);
        btnSend = new QPushButton(widget_3);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setMinimumSize(QSize(0, 60));
        btnSend->setMaximumSize(QSize(125, 16777215));

        gridLayout_2->addWidget(btnSend, 0, 0, 3, 1);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMaximumSize(QSize(70, 16777215));
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        txtSendMs = new QLineEdit(widget_4);
        txtSendMs->setObjectName(QString::fromUtf8("txtSendMs"));
        txtSendMs->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(txtSendMs);

        lblMs = new QLabel(widget_4);
        lblMs->setObjectName(QString::fromUtf8("lblMs"));
        lblMs->setMaximumSize(QSize(20, 16777215));
        QFont font;
        font.setPointSize(12);
        lblMs->setFont(font);

        horizontalLayout->addWidget(lblMs);


        gridLayout_2->addWidget(widget_4, 0, 1, 1, 1);

        chkTimSend = new QCheckBox(widget_3);
        chkTimSend->setObjectName(QString::fromUtf8("chkTimSend"));
        chkTimSend->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(chkTimSend, 1, 1, 1, 1);


        gridLayout_4->addWidget(widget_3, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        cmbBaudRate->setCurrentIndex(2);
        cmbData->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        chkRec->setText(QCoreApplication::translate("MainWindow", "16\350\277\233\345\210\266\346\216\245\346\224\266", nullptr));
        lblSerialPort->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\200\211\346\213\251", nullptr));
        lblBaudRate->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        cmbBaudRate->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        cmbBaudRate->setItemText(1, QCoreApplication::translate("MainWindow", "38400", nullptr));
        cmbBaudRate->setItemText(2, QCoreApplication::translate("MainWindow", "115200", nullptr));

        lblStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        cmbStop->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        cmbStop->setItemText(1, QCoreApplication::translate("MainWindow", "1.5", nullptr));
        cmbStop->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));

        lblData->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        cmbData->setItemText(0, QCoreApplication::translate("MainWindow", "5", nullptr));
        cmbData->setItemText(1, QCoreApplication::translate("MainWindow", "6", nullptr));
        cmbData->setItemText(2, QCoreApplication::translate("MainWindow", "7", nullptr));
        cmbData->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        lblCheck->setText(QCoreApplication::translate("MainWindow", "\345\245\207\345\201\266\346\240\241\351\252\214", nullptr));
        cmbCheck->setItemText(0, QCoreApplication::translate("MainWindow", "\346\227\240", nullptr));
        cmbCheck->setItemText(1, QCoreApplication::translate("MainWindow", "\345\245\207\346\240\241\351\252\214", nullptr));
        cmbCheck->setItemText(2, QCoreApplication::translate("MainWindow", "\345\201\266\346\240\241\351\252\214", nullptr));

        lblSwitch->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\223\215\344\275\234", nullptr));
        btnSwitch->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnClearRec->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\216\245\346\224\266", nullptr));
        btnClearSend->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\345\217\221\351\200\201", nullptr));
        chkSend->setText(QCoreApplication::translate("MainWindow", "16\350\277\233\345\210\266\345\217\221\351\200\201", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        txtSendMs->setText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        lblMs->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        chkTimSend->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
