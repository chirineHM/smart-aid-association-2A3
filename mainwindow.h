#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "evenement.h"
QT_BEGIN_NAMESPACE

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
    void on_pb_clicked();

    void on_pb_supprimer_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_load_list_clicked();

    void on_modifier_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_envoyer_clicked();

    void sendMail();

    void mailSent(QString) ;

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pb_2_clicked();

private:
    Ui::MainWindow *ui;
    evenement E;
};

#endif // MAINWINDOW_H
