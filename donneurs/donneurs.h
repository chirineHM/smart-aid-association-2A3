#ifndef MATERIAUX_H
#define MATERIAUX_H
#include "materiel.h"
#include <QDialog>

namespace Ui {
class donneurs;
}

class donneurs : public QDialog
{
    Q_OBJECT

public:
    explicit donneurs(QWidget *parent = nullptr);
    ~donneurs();

private slots:
    void on_pushButton_5_clicked();


    void on_pushButton_6_clicked();




    void on_recherche_textChanged(const QString &arg1);

    void on_checkBox_4_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::donneurs *ui;
    donneur don;
    QString selected;



};

#endif // MATERIAUX_H
