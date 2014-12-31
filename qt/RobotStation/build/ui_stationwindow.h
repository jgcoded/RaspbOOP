/********************************************************************************
** Form generated from reading UI file 'stationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONWINDOW_H
#define UI_STATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StationWindow)
    {
        if (StationWindow->objectName().isEmpty())
            StationWindow->setObjectName(QStringLiteral("StationWindow"));
        StationWindow->resize(523, 397);
        centralWidget = new QWidget(StationWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 501, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        frame = new QFrame(verticalLayoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        verticalLayout->setStretch(2, 1);
        StationWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StationWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 523, 25));
        StationWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StationWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        StationWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StationWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        StationWindow->setStatusBar(statusBar);

        retranslateUi(StationWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), StationWindow, SLOT(connect()));

        QMetaObject::connectSlotsByName(StationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StationWindow)
    {
        StationWindow->setWindowTitle(QApplication::translate("StationWindow", "Robot Station", 0));
        pushButton->setText(QApplication::translate("StationWindow", "Connect to robot", 0));
        label->setText(QApplication::translate("StationWindow", "Connected to:", 0));
        label_2->setText(QApplication::translate("StationWindow", "0.0.0.0", 0));
    } // retranslateUi

};

namespace Ui {
    class StationWindow: public Ui_StationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONWINDOW_H
