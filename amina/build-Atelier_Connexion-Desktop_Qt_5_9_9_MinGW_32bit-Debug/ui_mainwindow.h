/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_11;
    QDateTimeEdit *la_date_2;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *le_num_2;
    QLineEdit *le_nom_2;
    QLineEdit *le_lieu_2;
    QLineEdit *le_nmbp;
    QLineEdit *le_descp_2;
    QPushButton *pb;
    QPushButton *pushButton_9;
    QWidget *tab_5;
    QWidget *tab_4;
    QTableView *tableView_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(776, 389);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 20, 611, 411));
        label->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/paw 1.jpg")));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(130, 10, 481, 301));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 24, 47, 16));
        label_2->setStyleSheet(QStringLiteral("font: 75 8pt \"Adobe Caslon Pro Bold\";"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 50, 47, 14));
        label_3->setStyleSheet(QLatin1String("font: 75 8pt \"Adobe Caslon Pro Bold\";\n"
""));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 150, 47, 14));
        label_11->setStyleSheet(QLatin1String("font: 75 8pt \"Adobe Caslon Pro Bold\";\n"
""));
        la_date_2 = new QDateTimeEdit(tab_3);
        la_date_2->setObjectName(QStringLiteral("la_date_2"));
        la_date_2->setGeometry(QRect(70, 110, 111, 22));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 180, 47, 14));
        label_12->setStyleSheet(QStringLiteral("font: 75 8pt \"Adobe Caslon Pro Bold\";"));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 80, 47, 14));
        label_13->setStyleSheet(QStringLiteral("font: 75 8pt \"Adobe Caslon Pro Bold\";"));
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 110, 47, 14));
        label_14->setStyleSheet(QStringLiteral("font: 75 8pt \"Adobe Caslon Pro Bold\";"));
        le_num_2 = new QLineEdit(tab_3);
        le_num_2->setObjectName(QStringLiteral("le_num_2"));
        le_num_2->setGeometry(QRect(70, 20, 113, 20));
        le_nom_2 = new QLineEdit(tab_3);
        le_nom_2->setObjectName(QStringLiteral("le_nom_2"));
        le_nom_2->setGeometry(QRect(70, 50, 113, 20));
        le_lieu_2 = new QLineEdit(tab_3);
        le_lieu_2->setObjectName(QStringLiteral("le_lieu_2"));
        le_lieu_2->setGeometry(QRect(70, 80, 113, 20));
        le_nmbp = new QLineEdit(tab_3);
        le_nmbp->setObjectName(QStringLiteral("le_nmbp"));
        le_nmbp->setGeometry(QRect(70, 150, 113, 20));
        le_descp_2 = new QLineEdit(tab_3);
        le_descp_2->setObjectName(QStringLiteral("le_descp_2"));
        le_descp_2->setGeometry(QRect(70, 180, 113, 20));
        pb = new QPushButton(tab_3);
        pb->setObjectName(QStringLiteral("pb"));
        pb->setGeometry(QRect(310, 70, 75, 23));
        pb->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        pushButton_9 = new QPushButton(tab_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(310, 110, 75, 23));
        pushButton_9->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tableView_2 = new QTableView(tab_4);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(60, 40, 256, 192));
        pushButton_10 = new QPushButton(tab_4);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(380, 30, 75, 23));
        pushButton_10->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        pushButton_11 = new QPushButton(tab_4);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(380, 70, 75, 23));
        pushButton_11->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        pushButton_12 = new QPushButton(tab_4);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(380, 110, 75, 23));
        pushButton_12->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        pushButton_13 = new QPushButton(tab_4);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(380, 190, 75, 23));
        pushButton_13->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        pushButton_14 = new QPushButton(tab_4);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(380, 150, 75, 23));
        pushButton_14->setStyleSheet(QLatin1String("background-color:black;\n"
"color:white;\n"
"border-style:outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:white;"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 776, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion des Clients", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Num", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "nom ", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "nb partcp", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "descrip", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "lieu", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Date", Q_NULLPTR));
        pb->setText(QApplication::translate("MainWindow", "valider", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "Annuler", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "ajouter un evenement", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "chercher", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "Trier", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("MainWindow", "exporter PDF", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("MainWindow", "Envoie mail", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindow", "Calendrier", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "afficher l'evenement", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
