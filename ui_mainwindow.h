/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QTableWidget *tableNeed;
    QLineEdit *lineProcesses;
    QLabel *labelProcesses;
    QLineEdit *lineResources;
    QTableWidget *tableAllocation;
    QLabel *labelResources;
    QPushButton *btnCreateTables;
    QTextEdit *textOutput;
    QTableWidget *tableMax;
    QPushButton *btnCheckSafe;
    QPushButton *Reset;
    QPushButton *btnAutoFill;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 351, 470));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        tableNeed = new QTableWidget(gridLayoutWidget);
        tableNeed->setObjectName(QString::fromUtf8("tableNeed"));

        gridLayout->addWidget(tableNeed, 13, 0, 1, 1);

        lineProcesses = new QLineEdit(gridLayoutWidget);
        lineProcesses->setObjectName(QString::fromUtf8("lineProcesses"));

        gridLayout->addWidget(lineProcesses, 3, 0, 1, 1);

        labelProcesses = new QLabel(gridLayoutWidget);
        labelProcesses->setObjectName(QString::fromUtf8("labelProcesses"));

        gridLayout->addWidget(labelProcesses, 2, 0, 1, 1);

        lineResources = new QLineEdit(gridLayoutWidget);
        lineResources->setObjectName(QString::fromUtf8("lineResources"));

        gridLayout->addWidget(lineResources, 4, 0, 1, 1);

        tableAllocation = new QTableWidget(gridLayoutWidget);
        tableAllocation->setObjectName(QString::fromUtf8("tableAllocation"));

        gridLayout->addWidget(tableAllocation, 11, 0, 1, 1);

        labelResources = new QLabel(gridLayoutWidget);
        labelResources->setObjectName(QString::fromUtf8("labelResources"));

        gridLayout->addWidget(labelResources, 1, 0, 1, 1);

        btnCreateTables = new QPushButton(gridLayoutWidget);
        btnCreateTables->setObjectName(QString::fromUtf8("btnCreateTables"));

        gridLayout->addWidget(btnCreateTables, 6, 0, 1, 1);

        textOutput = new QTextEdit(gridLayoutWidget);
        textOutput->setObjectName(QString::fromUtf8("textOutput"));

        gridLayout->addWidget(textOutput, 10, 0, 1, 1);

        tableMax = new QTableWidget(gridLayoutWidget);
        tableMax->setObjectName(QString::fromUtf8("tableMax"));

        gridLayout->addWidget(tableMax, 12, 0, 1, 1);

        btnCheckSafe = new QPushButton(gridLayoutWidget);
        btnCheckSafe->setObjectName(QString::fromUtf8("btnCheckSafe"));

        gridLayout->addWidget(btnCheckSafe, 8, 0, 1, 1);

        Reset = new QPushButton(gridLayoutWidget);
        Reset->setObjectName(QString::fromUtf8("Reset"));

        gridLayout->addWidget(Reset, 9, 0, 1, 1);

        btnAutoFill = new QPushButton(gridLayoutWidget);
        btnAutoFill->setObjectName(QString::fromUtf8("btnAutoFill"));

        gridLayout->addWidget(btnAutoFill, 7, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lineProcesses->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter number of resources ", nullptr));
        labelProcesses->setText(QCoreApplication::translate("MainWindow", "Processes:", nullptr));
        lineResources->setText(QString());
        lineResources->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter number of processes ", nullptr));
        labelResources->setText(QCoreApplication::translate("MainWindow", "Resources:", nullptr));
        btnCreateTables->setText(QCoreApplication::translate("MainWindow", "Create Tables", nullptr));
        textOutput->setAccessibleIdentifier(QString());
        btnCheckSafe->setText(QCoreApplication::translate("MainWindow", "Check Safe Sequence", nullptr));
        Reset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        btnAutoFill->setText(QCoreApplication::translate("MainWindow", "btnAutoFill", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
