#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inter.h"
#include<QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        ui->le_id->setValidator(new QIntValidator(0,9999,this));
        ui->table_animaux->setModel(I.afficher());
         ui->del_id->setModel(I.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int ID_ANIMAL=ui->le_id->text().toInt();
    int ID_intervention=ui->le_age->text().toInt();
    int ID_veterinaire=ui->le_poids->text().toInt();
    QString Etat_vaccin=ui->le_espece->text();
    QString Etat_castration=ui->le_sexe->text();
    QString Rapport_sante=ui->le_race->text();

    QString DATE_intervention=ui->le_date->text();

 intervention I(ID_intervention,ID_ANIMAL,ID_veterinaire,Etat_vaccin,Etat_castration,Rapport_sante,DATE_intervention);
 bool test=I.ajouter();
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
    ui->table_animaux->setModel(I.afficher());
}



void MainWindow::on_supp_clicked()
{
   /* Animaux a;
    a.setid(ui->del_id->currentText().toInt());
   // a.setid(ui->supp->text().toInt());
    bool test=a.supprimer(a.getid());
    if(test)

    {   //REFRESH
       // ui->table_commande->setModel(c.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("supp effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->del_id->setModel(a.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("supp non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
    intervention i; i.setidi(ui->del_id->currentText().toInt());


        bool test=i.supprimer(i.getidi());

        QMessageBox msgBox;

        if(test)

        {   ui->table_animaux->setModel(i.afficher());

         //   ui->tableView->setModel(c.afficher_id());

            //ui->update_id->setModel(c.afficher_id());

            ui->del_id->setModel(i.afficher());

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

           query.prepare("SELECT ID_INTERVENTION FROM INTERVENTION");
           query.exec();
           load->setQuery(query);
           ui->del_id->setModel(load);
}
void MainWindow::on_pb_modifier_clicked()
{
    int qs = ui->lineEdit->text().toInt();
    QSqlQuery query;
    query.prepare("select * from INTERVENTION where ID_INTERVENTION = :ID_INTERVENTION ;");
    query.bindValue(":ID_INTERVENTION", qs);
    query.exec();
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(query);
    QSqlRecord sr = model->record(0);
    ui->le_espece_2->setText(sr.value(1).toString());
    ui->le_sexe_2->setText(sr.value(2).toString());
    ui->le_race_2->setText(sr.value(3).toString());
    ui->le_age_2->setText(sr.value(4).toString());
    ui->le_poids_2->setText(sr.value(5).toString());
    ui->le_date_2->setText(sr.value(6).toString());
}
void MainWindow::on_pb_ok_clicked()
{


      int ID_ANIMAL = ui->le_id_3->text().toInt();
      QString Etat_vaccin = ui->le_espece_2->text();
      QString Etat_castration = ui->le_sexe_2 ->text();
      QString Rapport_sante = ui->le_race_2->text();
      int  ID_intervention = ui->le_age_2->text().toInt();
      int  ID_veterinaire = ui->le_poids_2->text().toInt();
      QString DATE_intervention=ui->le_date_2->text();

      intervention I(ID_intervention,ID_ANIMAL,ID_veterinaire,Etat_vaccin,Etat_castration,Rapport_sante,DATE_intervention);
      bool test=I.ajouter();
      if(test)
    {
    QMessageBox::information(nullptr, QObject::tr("Modifier une intervention"),
                      QObject::tr("intervention modifiée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


  // ui->table_animaux->setModel(tmplivraison.afficher());//refresh
    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier "),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }


