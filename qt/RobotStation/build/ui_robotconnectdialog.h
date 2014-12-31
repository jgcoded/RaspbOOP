/********************************************************************************
** Form generated from reading UI file 'robotconnectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTCONNECTDIALOG_H
#define UI_ROBOTCONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotConnectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *ip_tab;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ip_button;
    QWidget *multicast_tab;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QListView *listView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *multicast_button;

    void setupUi(QDialog *RobotConnectDialog)
    {
        if (RobotConnectDialog->objectName().isEmpty())
            RobotConnectDialog->setObjectName(QStringLiteral("RobotConnectDialog"));
        RobotConnectDialog->resize(473, 256);
        verticalLayout = new QVBoxLayout(RobotConnectDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(RobotConnectDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        ip_tab = new QWidget();
        ip_tab->setObjectName(QStringLiteral("ip_tab"));
        verticalLayout_2 = new QVBoxLayout(ip_tab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(ip_tab);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(ip_tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaxLength(15);
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(ip_tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(ip_tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ip_button = new QPushButton(ip_tab);
        ip_button->setObjectName(QStringLiteral("ip_button"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ip_button->sizePolicy().hasHeightForWidth());
        ip_button->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(ip_button);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(ip_tab, QString());
        multicast_tab = new QWidget();
        multicast_tab->setObjectName(QStringLiteral("multicast_tab"));
        verticalLayout_3 = new QVBoxLayout(multicast_tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(multicast_tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        listView = new QListView(multicast_tab);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_3->addWidget(listView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        multicast_button = new QPushButton(multicast_tab);
        multicast_button->setObjectName(QStringLiteral("multicast_button"));

        horizontalLayout_2->addWidget(multicast_button);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(multicast_tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(RobotConnectDialog);
        QObject::connect(ip_button, SIGNAL(clicked()), RobotConnectDialog, SLOT(ip_connect()));
        QObject::connect(multicast_button, SIGNAL(clicked()), RobotConnectDialog, SLOT(multicast_connect()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RobotConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *RobotConnectDialog)
    {
        RobotConnectDialog->setWindowTitle(QApplication::translate("RobotConnectDialog", "Robot Connect Dialog", 0));
        label->setText(QApplication::translate("RobotConnectDialog", "IP Address:", 0));
        lineEdit->setInputMask(QApplication::translate("RobotConnectDialog", "000.000.000.000", 0));
        lineEdit->setText(QApplication::translate("RobotConnectDialog", "127.0.0.1", 0));
        lineEdit->setPlaceholderText(QApplication::translate("RobotConnectDialog", "127.0.0.1", 0));
        label_2->setText(QApplication::translate("RobotConnectDialog", "Port:", 0));
        lineEdit_2->setInputMask(QApplication::translate("RobotConnectDialog", "00000", 0));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("RobotConnectDialog", "1357", 0));
        ip_button->setText(QApplication::translate("RobotConnectDialog", "Connect", 0));
        tabWidget->setTabText(tabWidget->indexOf(ip_tab), QApplication::translate("RobotConnectDialog", "IP", 0));
        label_3->setText(QApplication::translate("RobotConnectDialog", "Select a client to connect to:", 0));
        multicast_button->setText(QApplication::translate("RobotConnectDialog", "Connect", 0));
        tabWidget->setTabText(tabWidget->indexOf(multicast_tab), QApplication::translate("RobotConnectDialog", "Multicast", 0));
    } // retranslateUi

};

namespace Ui {
    class RobotConnectDialog: public Ui_RobotConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTCONNECTDIALOG_H
