/********************************************************************************
** Form generated from reading UI file 'GUIWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIWINDOW_H
#define UI_GUIWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUIWindow)
    {
        if (GUIWindow->objectName().isEmpty())
            GUIWindow->setObjectName(QStringLiteral("GUIWindow"));
        GUIWindow->resize(243, 111);
        actionExit = new QAction(GUIWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(GUIWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/brick.jpg")));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        GUIWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 243, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        GUIWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(GUIWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GUIWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(GUIWindow);

        QMetaObject::connectSlotsByName(GUIWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GUIWindow)
    {
        GUIWindow->setWindowTitle(QApplication::translate("GUIWindow", "Hello, World!", 0));
        actionExit->setText(QApplication::translate("GUIWindow", "E&xit", 0));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("GUIWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class GUIWindow: public Ui_GUIWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIWINDOW_H
