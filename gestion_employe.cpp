#include "gestion_employe.h"
#include "ui_gestion_employe.h"
#include<QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QFloat16>
#include <QSqlQueryModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include "connection.h"

#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>
#include"qrcode.h"
#include<QtSvg/QSvgRenderer>
#include<QSvgRenderer>
#include <QFile>
#include <QFileDialog>
#include<fstream>
#include<iostream>
#include <vector>
#include "login.h"
using qrcodegen::QrCode;
#define EMAIL_RX "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+"\
                 "(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"

Gestion_Employe::Gestion_Employe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gestion_Employe)
{
    ui->setupUi(this);

    QRegExp rxEmail(EMAIL_RX);
        QRegExpValidator *valiEmail = new QRegExpValidator(rxEmail, this);
        ui->le_email_2->setValidator(valiEmail);


        //ui->le_id->setVaslidator(new QIntValidator(0,9999,this));
        ui->table_employes->setModel(E.afficher());
        ui->tableView_profil->setModel(p.afficher());

        ui->comboBoxModif->setModel(E.remplircomboEmploye());


}

Gestion_Employe::~Gestion_Employe()
{
    delete ui;
}


void Gestion_Employe::on_ajouter_clicked()
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
void Gestion_Employe::on_supprimer_clicked()
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

void Gestion_Employe::on_load_list_clicked()
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

//int id_emp=ui->tableView->text().toInt();

    int id_emp=ui->le_id_2->text().toInt();

      int tel_emp=ui->le_tel->text().toInt();

      QString nom_emp=ui->le_nom->text();
      QString prenom_emp=ui->le_prenom->text();
      QString sexe_emp=ui->le_sexe->text();
      QString date_naiss_emp=ui->le_date->text();
      QString adresse_emp=ui->le_adresse->text();
      QString email=ui->le_email_3->text();


 Employe E2(id_emp, tel_emp, nom_emp, prenom_emp, sexe_emp, date_naiss_emp, adresse_emp, email);

 bool test=E2.modifier();

 QMessageBox msgBox;

 if(test)

 {

    ui->table_employes->setModel(E.afficher());

    ui->tableView->setModel(E.afficher_id());

    ui->del_id->setModel(E.afficher_id());

    msgBox.setText("Modification avec succes.");



 }

 else

     msgBox.setText("Echec de Modification.");

     msgBox.exec();

}*/
void Gestion_Employe::on_modifier_clicked()
{

/*
       int id_emp=ui->le_id_2->text().toInt();
       int tel_emp=ui->le_tel_2->text().toInt();





          QString nom_emp=ui->le_nom_2->text();

          QString prenom_emp=ui->le_prenom_2->text();
          QString sexe_emp=ui->le_sexe_2->text();
          QString date_naiss_emp=ui->le_date_2->text();
          QString adresse_emp=ui->le_adresse_2->text();
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
*/

}

void Gestion_Employe::on_tableView_activated(const QModelIndex &index)
{/*
    QSqlQuery query;
           QString id_emp=ui->tableView->model()->data(index).toString();
           query.prepare("select * from EMPLOYE where id_emp='"+id_emp+"'");
           if(query.exec())
           {
               while (query.next())
               {
                  // ui->update_id->setText(query.value(0).toString());
                   ui->le_id_2->setText(query.value(1).toString());
                   ui->le_nom_2->setText(query.value(2).toString());
                   ui->le_prenom_2->setText(query.value(3).toString());
                   ui->le_sexe_2->setText(query.value(4).toString());
                   ui->le_adresse_2->setText(query.value(5).toString());
                   ui->le_tel_2->setText(query.value(6).toString());
                   ui->le_date_2->setText(query.value(7).toString());
                   ui->le_email_3->setText(query.value(8).toString());
               }
            }
               else
               {
                   QMessageBox::critical(nullptr, QObject::tr("Failed"),
                               QObject::tr("Impossible.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
               }
               */

}


void Gestion_Employe::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/planet/Desktop/syrine.projet qt/employe.pdf");


    QPainter painter(&pdf);

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(3000,1500,"LISTE DES EMPLOYES");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(2700,200,7300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Identifiant EMPLOYE");
    painter.drawText(2300,3300,"NOM EMPLOYE");
    painter.drawText(4300,3300,"PRENOM EMPLOYE");
    painter.drawText(6300,3300,"SEXE EMPLOYE");
    painter.drawText(8000,3300,"ADRESSE EMPLOYE");
    painter.drawText(10000,3300,"TEL EMPLOYE");
    painter.drawText(10200,3300,"DATE NAISSANCE EMPLOYE");
    painter.drawText(10400,3300,"EMAIL EMPLOYE");
    QSqlQuery query;
    query.prepare("select * from Employe");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        i = i +500;
    }

    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/planet/Desktop/syrine.projet qt/employe.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void Gestion_Employe::on_pb_chercher_clicked()
{


    QString nom=ui->le_chercher->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where NOM_EMP='"+nom+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));



        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}
void Gestion_Employe::on_pb_chercher_1_clicked()
{


    QString prenom=ui->le_chercher1->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where PRENOM_EMP='"+prenom+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));





        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}
void Gestion_Employe::on_pb_chercher_2_clicked()
{


    QString date_naiss=ui->le_chercher2->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where DATE_NAISS_EMP='"+date_naiss+"'");

       /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));*/


        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}

void Gestion_Employe::on_pb_trier_clicked()
{

    Employe *E = new Employe();
    ui->table_employes->setModel(E->tri());

}
void Gestion_Employe::on_pb_trier_1_clicked()
{

    Employe *E = new Employe();
    ui->table_employes->setModel(E->tri1());

}
void Gestion_Employe::on_pb_trier_2_clicked()
{

    Employe *E = new Employe();
    ui->table_employes->setModel(E->tri2());

}

void Gestion_Employe::on_comboBoxModif_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBoxModif->currentText();

    query =E.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nom_modif->setText(query.value(1).toString());
            ui->prenom_modif->setText(query.value(2).toString());
            ui->sexe_modif->setText(query.value(3).toString());
            ui->adresse_modif->setText(query.value(4).toString());
            ui->tel_modif->setText(query.value(5).toString());
            ui->date_modif->setText(query.value(6).toString());
            ui->email_modif->setText(query.value(7).toString());
        }
    }

}


void Gestion_Employe::on_ModifierBouton_clicked()
{
    if((ui->nom_modif->text() != "") &&(ui->prenom_modif->text() != "")&&(ui->adresse_modif->text() != ""))
    {
        Employe tmp(ui->comboBoxModif->currentText().toInt(),ui->tel_modif->text().toInt(),ui->nom_modif->text(),ui->prenom_modif->text(),ui->adresse_modif->text(),ui->date_modif->text(),ui->sexe_modif->text(),ui->email_modif->text());
        if(tmp.modifier())
        {
            //refresh combobox + tableau
                ui->table_employes->setModel(E.afficher());

        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier un Stock"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }
}





void Gestion_Employe::on_supprimer2_clicked()
{

        bool test=p.supprimer(ui->del_password->currentText().toInt());
        QMessageBox msgBox;
        if(test)
        {   ui->tableView_profil->setModel(p.afficher());
            //ui->tableView->setModel(c.afficher_id());
           // ui->update_id->setModel(c.afficher_id());
            ui->del_id->setModel(E.afficher());
            msgBox.setText("Suppression avec succes.");


        }
        else
            msgBox.setText("Echec de suppression.");
            msgBox.exec();

}

void Gestion_Employe::on_load_listProfil_clicked()
{
    QSqlQuery query;
    QSqlQueryModel *load=new QSqlQueryModel();

       query.prepare("SELECT ID FROM PROFIL");
       query.exec();
       load->setQuery(query);
       ui->del_password->setModel(load);

}

void Gestion_Employe::on_deconnexion_clicked()
{
    Gestion_Employe::close();
    Login *m = new Login();
    m->show();

}



void Gestion_Employe::on_pushButton_24_clicked()
{
    if(ui->table_employes->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
                   int id_emp=ui->table_employes->model()->data(ui->table_employes->model()->index(ui->table_employes->currentIndex().row(),0)).toInt();
                   const QrCode qr = QrCode::encodeText(std::to_string(id_emp).c_str(), QrCode::Ecc::LOW);
                   std::ofstream myfile;
                   myfile.open ("qrcode.svg") ;
                   myfile << qr.toSvgString(1);
                   myfile.close();
                   QSvgRenderer svgRenderer(QString("qrcode.svg"));
                   QPixmap pix( QSize(90, 90) );
                   QPainter pixPainter( &pix );
                   svgRenderer.render( &pixPainter );
                   ui->label_11->setPixmap(pix);
                   QString fileName = QFileDialog::getSaveFileName(this, tr("IMAGE"), qApp->applicationDirPath (),
                                                                                               tr("IMAGE (*.PNG)"));
                                          QFile file(""+fileName+"");
                                                                 file.open(QIODevice::WriteOnly);
                                                                 pix.save(&file, "PNG");

              }
}
