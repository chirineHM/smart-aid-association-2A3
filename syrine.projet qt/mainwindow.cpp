#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include<QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>
//#include <QRegExpValidator>
/*#define EMAIL_RX "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+"\
                 "(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        //ui->le_id->setVaslidator(new QIntValidator(0,9999,this));
        ui->table_employes->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int id_emp=ui->le_id->text().toInt();
    int tel_emp=ui->le_tel->text().toInt();
    QString nom_emp=ui->le_nom->text();
    QString prenom_emp=ui->le_prenom->text();
    QString adresse_emp=ui->le_adresse->text();
    QString date_naiss_emp=ui->le_date->text();
    QString sexe_emp=ui->le_sexe->text();
    QString email=ui->le_email_2->text();

 ui->table_employes->setModel(E.afficher());

 Employe E(id_emp, tel_emp, nom_emp, prenom_emp, adresse_emp, date_naiss_emp, sexe_emp, email);
 bool test=E.ajouter();
 if(test)

 {   //REFRESH
     ui->table_employes->setModel(E.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Ajout effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }
 else
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                 QObject::tr("Ajout non effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_supprimer_clicked()
{
    /*
    Employe E;
    E.setid_emp(ui->le_id->text().toInt());
    bool test=E.supprimer(E.getid_emp());
     ui->table_employes->setModel(E.afficher());
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Suppression avec succes.");


    }
    else
        msgBox.setText("Echec de suppression.");
        msgBox.exec();*/
    Employe E; E.setid_emp(ui->del_id->currentText().toInt());

        bool test=E.supprimer(E.getid_emp());
        QMessageBox msgBox;
        if(test)
        {   ui->table_employes->setModel(E.afficher());
            //ui->tableView->setModel(c.afficher_id());
           // ui->update_id->setModel(c.afficher_id());
            ui->del_id->setModel(E.afficher());
            msgBox.setText("Suppression avec succes.");


        }
        else
            msgBox.setText("Echec de suppression.");
            msgBox.exec();

}

void MainWindow::on_load_list_clicked()
{
    QSqlQuery query;
    QSqlQueryModel *load=new QSqlQueryModel();

       query.prepare("SELECT ID_EMP FROM EMPLOYE");
       query.exec();
       load->setQuery(query);
       ui->del_id->setModel(load);


}
/*void MainWindow::on_modifier_clicked()

 {

//int id_emp=ui->id_update->text().toInt();

    //int id_emp=ui->le_id->text().toInt();

      //int tel_emp=ui->le_tel->text().toInt();

      QString nom_emp=ui->le_nom->text();
      QString prenom_emp=ui->le_prenom->text();
      QString sexe_emp=ui->le_sexe->text();
      QString date_naiss_emp=ui->le_date->text();
      QString adresse_emp=ui->le_adresse->text();
      QString email=ui->le_email_3->text();


// Employe E(id_emp, nom_emp, prenom_emp, sexe_emp, date_naiss_emp, adresse_emp, tel_emp, email);

 bool test=E.modifier();

 QMessageBox msgBox;

 if(test)

 {

    ui->table_employes->setModel(E.afficher());

    //ui->tableView->setModel(E.afficher_id());

    //ui->del_id->setModel(E.afficher_id());

    msgBox.setText("Modification avec succes.");



 }

 else

     msgBox.setText("Echec de Modification.");

     msgBox.exec();

}*/
void MainWindow::on_modifier_clicked()
{


       int id_emp=ui->le_id->text().toInt();
       int tel_emp=ui->le_tel->text().toInt();



          //int nmbp=ui->nb_mod->text().toInt();

          QString nom_emp=ui->le_nom->text();

          QString prenom_emp=ui->le_prenom->text();
          QString sexe_emp=ui->le_sexe->text();
          QString date_naiss_emp=ui->le_date->text();
          QString adresse_emp=ui->le_adresse->text();
          QString email=ui->le_email_3->text();

     Employe E2(id_emp,tel_emp,nom_emp,prenom_emp,date_naiss_emp,adresse_emp,email,sexe_emp);

     bool test=E2.modifier();

     QMessageBox msgBox;

     if(test)

     {ui->tableView->setModel(E.afficher_id());
        ui->table_employes->setModel(E2.afficher());


        //ui->del_id_2->setModel(c.afficher_id());

        msgBox.setText("Modification avec succes.");



     }

     else

         msgBox.setText("Echec de Modification.");

         msgBox.exec();


}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QSqlQuery query;
           QString id_emp=ui->tableView->model()->data(index).toString();
           query.prepare("select * from EMPLOYE where id_emp='"+id_emp+"'");
           if(query.exec())
           {
               while (query.next())
               {
                  // ui->update_id->setText(query.value(0).toString());
                   ui->le_id->setText(query.value(1).toString());
                   ui->le_nom->setText(query.value(2).toString());
                   ui->le_prenom->setText(query.value(3).toString());
                   ui->le_sexe->setText(query.value(4).toString());
                   ui->le_adresse->setText(query.value(5).toString());
                   ui->le_tel->setText(query.value(6).toString());
                   ui->le_date->setText(query.value(7).toString());
                   ui->le_email_3->setText(query.value(8).toString());
               }
            }
               else
               {
                   QMessageBox::critical(nullptr, QObject::tr("Failed"),
                               QObject::tr("Impossible.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
               }

}
