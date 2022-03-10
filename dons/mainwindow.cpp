#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dons.h"
#include<QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        ui->le_id->setValidator(new QIntValidator(0,9999,this));
        ui->table_dons->setModel(D.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int Id_don=ui->le_id->text().toInt();
    int id_donneur=ui->le_d->text().toInt();
    int id_employe=ui->le_e->text().toInt();
    QString type_don=ui->le_type->text();
    QString quantite_don=ui->le_quantite->text();

    QString date_don=ui->le_date->text();

 Dons D(Id_don,id_donneur,id_employe,type_don,quantite_don,date_don);
 bool test=D.ajouter();
 if(test)

 {   //REFRESH
    // ui->table_commande->setModel(c.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Ajout effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }
 else
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                 QObject::tr("Ajout non effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }




void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->table_dons->setModel(D.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    Dons d;
    d.setid(ui->supp->text().toInt());
    bool test=d.supprimer(d.getid());
    if(test)

    {   //REFRESH
       // ui->table_commande->setModel(c.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("supp effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("supp non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
