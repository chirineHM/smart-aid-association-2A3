#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inter.h"

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
    void on_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    //void on_pushButton_2_clicked();

    void on_supp_clicked();

    void on_load_list_clicked();
    void on_pb_modifier_clicked();
    void on_pb_ok_clicked();

private:
    Ui::MainWindow *ui;
    intervention I;
};

#endif // MAINWINDOW_H
