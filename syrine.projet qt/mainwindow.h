#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"

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

    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_load_list_clicked();
    void on_modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Employe E;
    Employe E2;
};

#endif // MAINWINDOW_H
