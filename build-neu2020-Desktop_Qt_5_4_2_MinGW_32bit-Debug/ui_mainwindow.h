/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ctabwidget.h>
#include "mytreewid.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_O;
    QAction *action_S;
    QAction *action_C;
    QAction *action_X;
    QAction *action_C_2;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    CTabWidget *tabWidget;
    QWidget *tab_2;
    QHBoxLayout *horizontal_3;
    QVBoxLayout *verticalLayout_4;
    MytreeWid *treeWidget;
    QTextEdit *textEdit;
    QGraphicsView *graphicsView_2;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *navLayout;
    QLabel *label_Sort;
    QComboBox *cbox_Sort;
    QLabel *label_Sort_info;
    QComboBox *cbox_Sort_info;
    QLabel *label_Find_method;
    QComboBox *cbox_Find;
    QLabel *label_Find_info;
    QComboBox *cbox_Find_txt;
    QLineEdit *Txt_find;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *currentPageLabel;
    QLabel *label_2;
    QLabel *countPageLabel;
    QPushButton *upPushButton;
    QPushButton *downPushButton;
    QLabel *change_txt1;
    QPushButton *btn_head;
    QPushButton *btn_tail;
    QLineEdit *Page_info;
    QLabel *change_page;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(924, 681);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_O = new QAction(MainWindow);
        action_O->setObjectName(QStringLiteral("action_O"));
        action_S = new QAction(MainWindow);
        action_S->setObjectName(QStringLiteral("action_S"));
        action_C = new QAction(MainWindow);
        action_C->setObjectName(QStringLiteral("action_C"));
        action_X = new QAction(MainWindow);
        action_X->setObjectName(QStringLiteral("action_X"));
        action_C_2 = new QAction(MainWindow);
        action_C_2->setObjectName(QStringLiteral("action_C_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new CTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontal_3 = new QHBoxLayout(tab_2);
        horizontal_3->setSpacing(6);
        horizontal_3->setContentsMargins(11, 11, 11, 11);
        horizontal_3->setObjectName(QStringLiteral("horizontal_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        treeWidget = new MytreeWid(tab_2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout_4->addWidget(treeWidget);

        textEdit = new QTextEdit(tab_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setStyleSheet(QStringLiteral("font: 9pt \"Times New Roman\";"));

        verticalLayout_4->addWidget(textEdit);


        horizontal_3->addLayout(verticalLayout_4);

        graphicsView_2 = new QGraphicsView(tab_2);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));

        horizontal_3->addWidget(graphicsView_2);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        navLayout = new QHBoxLayout();
        navLayout->setSpacing(6);
        navLayout->setObjectName(QStringLiteral("navLayout"));
        label_Sort = new QLabel(tab);
        label_Sort->setObjectName(QStringLiteral("label_Sort"));

        navLayout->addWidget(label_Sort);

        cbox_Sort = new QComboBox(tab);
        cbox_Sort->setObjectName(QStringLiteral("cbox_Sort"));
        cbox_Sort->setFocusPolicy(Qt::NoFocus);

        navLayout->addWidget(cbox_Sort);

        label_Sort_info = new QLabel(tab);
        label_Sort_info->setObjectName(QStringLiteral("label_Sort_info"));

        navLayout->addWidget(label_Sort_info);

        cbox_Sort_info = new QComboBox(tab);
        cbox_Sort_info->setObjectName(QStringLiteral("cbox_Sort_info"));
        cbox_Sort_info->setFocusPolicy(Qt::NoFocus);

        navLayout->addWidget(cbox_Sort_info);

        label_Find_method = new QLabel(tab);
        label_Find_method->setObjectName(QStringLiteral("label_Find_method"));

        navLayout->addWidget(label_Find_method);

        cbox_Find = new QComboBox(tab);
        cbox_Find->setObjectName(QStringLiteral("cbox_Find"));
        cbox_Find->setFocusPolicy(Qt::NoFocus);

        navLayout->addWidget(cbox_Find);

        label_Find_info = new QLabel(tab);
        label_Find_info->setObjectName(QStringLiteral("label_Find_info"));

        navLayout->addWidget(label_Find_info);

        cbox_Find_txt = new QComboBox(tab);
        cbox_Find_txt->setObjectName(QStringLiteral("cbox_Find_txt"));
        cbox_Find_txt->setFocusPolicy(Qt::NoFocus);

        navLayout->addWidget(cbox_Find_txt);

        Txt_find = new QLineEdit(tab);
        Txt_find->setObjectName(QStringLiteral("Txt_find"));

        navLayout->addWidget(Txt_find);


        verticalLayout_2->addLayout(navLayout);

        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setStyleSheet(QStringLiteral("border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);

        verticalLayout_2->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        currentPageLabel = new QLabel(tab);
        currentPageLabel->setObjectName(QStringLiteral("currentPageLabel"));

        horizontalLayout->addWidget(currentPageLabel);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        countPageLabel = new QLabel(tab);
        countPageLabel->setObjectName(QStringLiteral("countPageLabel"));

        horizontalLayout->addWidget(countPageLabel);

        upPushButton = new QPushButton(tab);
        upPushButton->setObjectName(QStringLiteral("upPushButton"));

        horizontalLayout->addWidget(upPushButton);

        downPushButton = new QPushButton(tab);
        downPushButton->setObjectName(QStringLiteral("downPushButton"));

        horizontalLayout->addWidget(downPushButton);

        change_txt1 = new QLabel(tab);
        change_txt1->setObjectName(QStringLiteral("change_txt1"));

        horizontalLayout->addWidget(change_txt1);

        btn_head = new QPushButton(tab);
        btn_head->setObjectName(QStringLiteral("btn_head"));

        horizontalLayout->addWidget(btn_head);

        btn_tail = new QPushButton(tab);
        btn_tail->setObjectName(QStringLiteral("btn_tail"));

        horizontalLayout->addWidget(btn_tail);

        Page_info = new QLineEdit(tab);
        Page_info->setObjectName(QStringLiteral("Page_info"));

        horizontalLayout->addWidget(Page_info);

        change_page = new QLabel(tab);
        change_page->setObjectName(QStringLiteral("change_page"));

        horizontalLayout->addWidget(change_page);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 924, 26));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_E = new QMenu(menubar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        MainWindow->setMenuBar(menubar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_E->menuAction());
        menu_F->addAction(action);
        menu_F->addAction(action_S);
        menu_F->addSeparator();
        menu_F->addAction(action_O);
        menu_F->addAction(action_C);
        menu_E->addAction(action_X);
        menu_E->addAction(action_C_2);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266(&N)", 0));
        action_O->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\346\213\251\347\232\204\345\205\203\347\273\204(&O)", 0));
        action_S->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256(&S) ", 0));
        action_C->setText(QApplication::translate("MainWindow", "\345\275\273\345\272\225\345\210\240\351\231\244(&C)", 0));
        action_X->setText(QApplication::translate("MainWindow", "\345\242\236\346\267\273\345\205\203\347\264\240(&X) ", 0));
        action_C_2->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\346\267\273\345\212\240(&C)", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\347\256\227\346\263\225\345\210\206\346\236\220", 0));
        label_Sort->setText(QApplication::translate("MainWindow", "\346\216\222\345\272\217\346\226\271\346\263\225", 0));
        label_Sort_info->setText(QApplication::translate("MainWindow", "\346\216\222\345\272\217\346\214\207\346\240\207", 0));
        label_Find_method->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\346\226\271\346\263\225", 0));
        label_Find_info->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\345\255\227\346\256\265", 0));
        label->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\357\274\232", 0));
        currentPageLabel->setText(QApplication::translate("MainWindow", "0", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\200\273\351\241\265\346\225\260\357\274\232", 0));
        countPageLabel->setText(QApplication::translate("MainWindow", "0", 0));
        upPushButton->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", 0));
        downPushButton->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", 0));
        change_txt1->setText(QApplication::translate("MainWindow", "\350\267\263\350\275\254\345\210\260", 0));
        btn_head->setText(QApplication::translate("MainWindow", "\351\246\226\351\241\265", 0));
        btn_tail->setText(QApplication::translate("MainWindow", "\345\260\276\351\241\265", 0));
        change_page->setText(QApplication::translate("MainWindow", "\351\241\265", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "CTBL\346\237\245\347\234\213\345\231\250", 0));
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0));
        menu_E->setTitle(QApplication::translate("MainWindow", "\345\242\236\346\267\273(&E)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
