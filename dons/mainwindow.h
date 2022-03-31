#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dons.h"

#include <QMainWindow>
#include <QTableWidget>
#include<QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_add_clicked();

    void on_delete_2_clicked();

    void on_modif_clicked();

    void on_tabWidget_currentChanged(int index);

   // void on_combosupp_activated(const QString &arg1);

   // void on_combomodif_currentIndexChanged(const QString &arg1);

    //void on_combomodif_activated(const QString &arg1);

    void on_tab_modif_activated(const QModelIndex &index);

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

   // void on_tabWidget_tabBarClicked(int index);


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
dons d;
};

#endif // MAINWINDOW_H
