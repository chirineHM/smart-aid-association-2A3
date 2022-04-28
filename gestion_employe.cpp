#include "gestion_employe.h"
#include "ui_gestion_employe.h"
#include<QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QFloat16>
#include"interventions.h"
#include <QSqlQueryModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include "connection.h"
#include"excel.h"
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
#include "arduino.h"
#include "dons.h"
using qrcodegen::QrCode;
#define EMAIL_RX "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+"\
                 "(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"

Gestion_Employe::Gestion_Employe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gestion_Employe)
{
    ui->setupUi(this);
    ui->menu->setCurrentWidget(ui->menu_2);
    QRegExp rxEmail(EMAIL_RX);
    QRegExpValidator *valiEmail = new QRegExpValidator(rxEmail, this);
    ui->le_email->setValidator(valiEmail);
        //ui->le_id->setVaslidator(new QIntValidator(0,9999,this));
        ui->table_employes->setModel(E.afficher());
        ui->tableView_profil->setModel(p.afficher());
        ui->tab_evenement->setModel(Ev.afficher());ui->tab_evenement->setModel(E.afficher());
        ui->comboBoxModif->setModel(E.remplircomboEmploye());
        ui->tableView->setModel((Ev.afficher_num()));
        //ui->setupUi(this);
            ui->le_id_2->setValidator(new QIntValidator(0,9999,this));
            ui->table_animaux->setModel(An.afficher());
             ui->del_id_2->setModel(An.afficher());


             ui->tab_stock->setModel(d.afficher());
             QSqlQueryModel *modal=new QSqlQueryModel;
             QSqlQuery *qry=new QSqlQuery;
             qry->prepare("select id_don from dons");
             qry->exec();
             modal->setQuery(*qry);
             ui->combosupp->setModel(modal);
             ui->tab_modif->setModel(modal);
             popUp = new PopUp();

             ui->tab_stock->setModel(d.afficher());

             qry->prepare("select ID_INTERVENTION from INTERVENTION");
             qry->exec();
             modal->setQuery(*qry);
           //  ui->del_id_4->setModel(modal);
           //  ui->tab_modif_2->setModel(modal);
        int ret=A.connect_arduino();
            switch(ret){
            case(0):qDebug()<< "arduino is available and is connected to : "<<A.getarduino_port_name();
                break;
            case(1):qDebug()<<"arduino is available but not connected to : "<<A.getarduino_port_name();
                break;
            case(-1):qDebug()<<"arduino is not available";
            }
            QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label_uid()));
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
            ui->tableView_distance->setModel(afficher_distance());
            count=0;



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
    QString email=ui->le_email->text();
    QString rfid=ui->rfid->currentText();

 ui->table_employes->setModel(E.afficher());

 Employe E(id_emp, tel_emp, nom_emp, prenom_emp, adresse_emp, date_naiss_emp, sexe_emp, email, rfid);
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
void Gestion_Employe::on_supprimerE_clicked()
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
    Employe E; E.setid_emp(ui->del_idS->currentText().toInt());

        bool test=E.supprimer(E.getid_emp());
        QMessageBox msgBox;
        if(test)
        {   ui->table_employes->setModel(E.afficher());
            //ui->tableView->setModel(c.afficher_id());
           // ui->update_id->setModel(c.afficher_id());
            ui->del_idS->setModel(E.afficher());
            msgBox.setText("Suppression avec succes.");


        }
        else
            msgBox.setText("Echec de suppression.");
            msgBox.exec();

}



void Gestion_Employe::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/user/Desktop/inegration/syrine.pdf");


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
    painter.drawText(10600,3300,"RFID EMPLOYE");


    const QImage image("C:/Users/planet/Desktop/PIDEVCopie/logo_qt.jpg");
                const QPoint imageCoordinates(1,1);
                painter.drawImage(imageCoordinates,image);

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
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/Desktop/inegration/syrine.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void Gestion_Employe::on_pb_chercherr_clicked()
{


    QString nom=ui->le_chercherr->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where NOM_EMP='"+nom+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));



        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}
void Gestion_Employe::on_pb_chercherr_1_clicked()
{


    QString prenom=ui->le_chercherr1->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where PRENOM_EMP='"+prenom+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));





        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}
void Gestion_Employe::on_pb_chercherr_2_clicked()
{


    QString date_naiss=ui->le_chercherr2->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM EMPLOYE where DATE_NAISS_EMP='"+date_naiss+"'");

       /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));*/


        ui->table_employes->setModel(model);



       qDebug() <<(model->rowCount());


}

void Gestion_Employe::on_pb_trierr_clicked()
{

    Employe *E = new Employe();
    ui->table_employes->setModel(E->tri());

}
void Gestion_Employe::on_pb_trierr_1_clicked()
{

    Employe *E = new Employe();
    ui->table_employes->setModel(E->tri1());

}
void Gestion_Employe::on_pb_trierr_2_clicked()
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
           // ui->email_modif->setText(query.value(7).toString());
        }
    }

}


void Gestion_Employe::on_ModifierBouton_clicked()
{
    if((ui->nom_modif->text() != "") &&(ui->prenom_modif->text() != "")&&(ui->adresse_modif->text() != "")&&(ui->new_rfid->currentText()!= ""))
    {
        Employe tmp(ui->comboBoxModif->currentText().toInt(),ui->tel_modif->text().toInt(),ui->nom_modif->text(),ui->prenom_modif->text(),ui->adresse_modif->text(),ui->date_modif->text(),ui->sexe_modif->text(),ui->email_modif->text(),ui->new_rfid->currentText());
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
            ui->del_password->setModel(E.afficher());
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
           ui->del_idS->setModel(load);
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



void Gestion_Employe::on_pushButton_28_clicked()
{
    if(ui->table_employes->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un employé du Tableau.\n"
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




void Gestion_Employe::update_label_uid()
{
    data.append(A.read_from_arduino());
if(data.length()==11){
    QString message="";
    if (E.rechCarte(data) )
       { QSqlQuery q("select * from employe where rfid='"+data+"'");
        while (q.next()) {

            message="L'employé de rfid "+q.value(8).toString()+" existe dans notre base de données";
}

       /* QMessageBox::information(nullptr, QObject::tr(""),
         QObject::tr(message"click cancel to exit . ") , QMessageBox::Cancel);*/
        QMessageBox::information(this,"employé existant " , message,QMessageBox::Ok);
         A.write_to_arduino("1");


    data.clear();
        }
    else
    {    QMessageBox::critical(nullptr, QObject::tr("employé n'existe pas"),
         QObject::tr("employé n'existe pas.\n"
                     "click cancel to exit . ") , QMessageBox::Cancel);
        A.write_to_arduino("0");

    data.clear();
    }
}

}


void Gestion_Employe::on_ajouter_3_clicked()
{
    ui->menu->setCurrentWidget(ui->menu_2);
}

void Gestion_Employe::on_deconnexion_2_clicked()
{
ui->menu->setCurrentWidget(ui->page_2);
}

void Gestion_Employe::on_deconnexion_3_clicked()
{
    ui->menu->setCurrentWidget(ui->page);
}








/*************SARRA:GESTION ANIMAUX**************/



/*Gestion_Employe::Gestion_Employe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        ui->le_id->setValidator(new QIntValidator(0,9999,this));
        ui->table_animaux->setModel(A.afficher());
         ui->del_id->setModel(A.afficher());

}

Gestion_Employe::~Gestion_Employe()
{
    delete ui;
}*/

void Gestion_Employe::on_pushButton_2_clicked()
{
    int ID_ANIMAL=ui->le_id_2->text().toInt();
    QString ESPECE=ui->le_espece->text();
    QString SEXE_ANIMAL=ui->le_sexe_2->text();
    QString RACE=ui->le_race->text();
    float AGE=ui->le_age->text().toFloat();
    float POIDS=ui->le_poids->text().toFloat();
    QString DATE_ACCUEIL=ui->le_date_2->text();
    QString ID=ui->le_id_2->text();
 Animaux An(ID_ANIMAL,ESPECE,SEXE_ANIMAL,RACE,AGE,POIDS,DATE_ACCUEIL);
 bool test=An.ajouter();
 if(test)

 {   //REFRESH
    // ui->table_commande->setModel(c.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Ajout effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

     QString nomFile ="Historique";
                  QFile file("C:/Users/user/Downloads/Atelier_Connexion/Atelier_Connexion/historique.txt");
                  QString finalmsg="fichier modifie avec succes";
                   if(!file.exists()){
                   finalmsg="fichier cree avec succes";
                   }
                  file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                  QTextStream txt(&file);
                    QString d_info = QDateTime::currentDateTime().toString();

                  QString message2=d_info+" - Un Animal a été ajoutée avec l'identifiant "+ID+"\n";
                  txt << message2;


 }
 else
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                 QObject::tr("Ajout non effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }




void Gestion_Employe::on_tabWidget_currentChanged(int index)
{
    ui->table_animaux->setModel(An.afficher());
}



void Gestion_Employe::on_supp_clicked()
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
    Animaux an; an.setid(ui->del_id_2->currentText().toInt());

QString ID=ui->del_id_2->currentText();
        bool test=an.supprimer(an.getid());

        QMessageBox msgBox;

        if(test)

        {   ui->table_animaux->setModel(an.afficher());

         //   ui->tableView->setModel(c.afficher_id());

            //ui->update_id->setModel(c.afficher_id());

            ui->del_id_2->setModel(an.afficher());

            msgBox.setText("Suppression avec succes.");
            QString nomFile ="Historique";
                         QFile file("C:/Users/user/Downloads/Atelier_Connexion/Atelier_Connexion/historique.txt");
                         QString finalmsg="fichier modifie avec succes";
                          if(!file.exists()){
                          finalmsg="fichier cree avec succes";
                          }
                         file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                         QTextStream txt(&file);
                           QString d_info = QDateTime::currentDateTime().toString();

                         QString message2=d_info+" - Un Animal a été supprimée avec l'identifiant "+ID+"\n";
                         txt << message2;



        }

        else

            msgBox.setText("Echec de suppression.");

            msgBox.exec();



}

void Gestion_Employe::on_load_list_2_clicked()
{
    QSqlQuery query;
        QSqlQueryModel *load=new QSqlQueryModel();

           query.prepare("SELECT ID_ANIMAL FROM ANIMAUX");
           query.exec();
           load->setQuery(query);
           ui->del_id_2->setModel(load);
}

/*void MainWindow::on_pb_modifier_clicked()
{
    int qs = ui->lineEdit->text().toInt();
    QSqlQuery query;
    query.prepare("select * from ANIMAUX where ID_ANIMAL = :ID_ANIMAL ;");
    query.bindValue(":ID_ANIMAL", qs);
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
}*/
/*void MainWindow::on_pb_ok_clicked()
{


     int ID_ANIMAL = ui->le_id_3->text().toInt();
      QString ESPECE = ui->le_espece_2->text();
      QString SEXE_ANIMAL = ui->le_sexe_2 ->text();
      QString RACE = ui->le_race_2->text();
      float  AGE = ui->le_age_2->text().toFloat();
      float  POIDS = ui->le_poids_2->text().toFloat();
      QString DATE_ACCUEIL=ui->le_date_2->text();

      Animaux A(ID_ANIMAL,ESPECE,SEXE_ANIMAL,RACE,AGE,POIDS,DATE_ACCUEIL);
      bool test=A.modifier();
      if(test)
    {
    QMessageBox::information(nullptr, QObject::tr("Modifier un animal"),
                      QObject::tr("animal modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


  ui->table_animaux->setModel(A.afficher());//refresh
    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier une Livraison"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }

*/


/*void MainWindow::on_pb_ok_clicked()
{
    int ID_ANIMAL = ui->lineEdit->text().toInt();
    QString ESPECE = ui->le_espece_2->text();
    QString SEXE_ANIMAL  = ui->le_sexe_2->text();
    QString RACE = ui->le_race_2->text();
    float AGE = ui->le_age_2->text().toFloat();
    float  POIDS = ui->le_poids_2->text().toFloat();
     QString  DATE_ACCUEIL = ui->le_date_2->text();
    Animaux A(ID_ANIMAL,ESPECE,SEXE_ANIMAL,RACE,AGE,POIDS,DATE_ACCUEIL);
    A.modifierF();
       ui->table_animaux->setModel(tmpanimaux.afficher());

}*/

void Gestion_Employe::on_pb_pdf_clicked()
{
    //QPdfWriter pdf("C:/Users/user/Downloads/Atelier_Connexion/Atelier_Connexion/listeAnimaux.pdf");
QPdfWriter pdf("C:/Users/user/Desktop/inegration/sarra.pdf");

    QPainter painter(&pdf);


    int i = 4000;

    painter.setPen(Qt::darkBlue);

    painter.setFont(QFont("Arial", 30));

    painter.drawText(2500,1500,"LISTE DES ANIMAUX");

    painter.setPen(Qt::black);

    painter.setFont(QFont("Arial", 20));

    painter.drawText(2000,2000,"Pet.O.S Smart Aid Association");

    painter.setPen(Qt::black);

    painter.setFont(QFont("Arial", 50));

    painter.drawRect(100,100,9400,2500);
   // painter.drawRect(100,3000,9400,500);

    // painter.drawText(1100,2000,afficheDC);

    //painter.drawRect(2700,200,7300,2600);

    painter.drawRect(0,3000,9600,500);

    painter.setFont(QFont("Arial", 9));

    painter.drawText(300,3300,"Identifiant");

    painter.drawText(1300,3300,"Espece");

    painter.drawText(2300,3300,"Sexe");

    painter.drawText(3300,3300,"Race");

    painter.drawText(4300,3300,"Age");

    painter.drawText(5300,3300,"Poids");

    painter.drawText(6300,3300,"date d'accueil");

    const QImage image("C:/Users/user/Downloads/Atelier_Connexion/Atelier_Connexion/logo3.jpg");
            const QPoint imageCoordinates(1,1);
            painter.drawImage(imageCoordinates,image);




    QSqlQuery query;

    query.prepare("select * from ANIMAUX");

    query.exec();

    while (query.next())

    {

        painter.drawText(300,i,query.value(0).toString());

        painter.drawText(1300,i,query.value(1).toString());

        painter.drawText(2300,i,query.value(2).toString());

        painter.drawText(3300,i,query.value(3).toString());

        painter.drawText(4300,i,query.value(4).toString());

        painter.drawText(5300,i,query.value(5).toString());

        painter.drawText(6300,i,query.value(6).toString());



        i = i +500;

    }


    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);

    if (reponse == QMessageBox::Yes)

    {

        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/Desktop/inegration/sarra.pdf"));


        painter.end();

    }

    if (reponse == QMessageBox::No)

    {

        painter.end();

    }

}

void Gestion_Employe::on_pb_chercher_00_clicked()
{

    QString identifiant=ui->le_chercher_2->text();


        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * FROM ANIMAUX where ID_ANIMAL='"+identifiant+"'");


        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));


        ui->table_animaux->setModel(model);

       qDebug() <<(model->rowCount());



}

void Gestion_Employe::on_pb_chercher_11_clicked()
{


    QString espece=ui->le_chercher1_2->text();


        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * FROM ANIMAUX where ESPECE='"+espece+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));


        ui->table_animaux->setModel(model);



       qDebug() <<(model->rowCount());

}

void Gestion_Employe::on_pb_chercher_22_clicked()
{


    QString race=ui->le_chercher2_2->text();

        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * FROM ANIMAUX where RACE='"+race+"'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));


        ui->table_animaux->setModel(model);



       qDebug() <<(model->rowCount());


}

void Gestion_Employe::on_pb_trier_00_clicked()
{
/*
    QMediaPlayer *player = new QMediaPlayer;
               player->setMedia(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
               player->setVolume(2000);
               player->play();*/
   // QString link="https://console.twilio.com/us1/develop/sms/try-it-out/send-an-sms?frameUrl=%2Fconsole%2Fsms%2Fgetting-started%2Fbuild%3Fx-target-region%3Dus1";
   // QDesktopServices::openUrl(QUrl(link));
    Animaux *an = new Animaux();
    ui->table_animaux->setModel(an->tri());

}

void Gestion_Employe::on_pb_trier_11_clicked()
{

    Animaux *an = new Animaux();
    ui->table_animaux->setModel(an->tri1());

}

void Gestion_Employe::on_pb_trier_22_clicked()
{

    Animaux *an = new Animaux();
    ui->table_animaux->setModel(an->tri2());

}







/*void MainWindow::on_pushButton_2_clicked()
{
    int ID_ANIMAL = ui->le_id1->text().toInt();
     QString ESPECE = ui->le_espece1->text();
     QString SEXE_ANIMAL = ui->le_sexe1 ->text();
     QString RACE = ui->le_race1->text();
     float  AGE = ui->le_age1->text().toFloat();
     float  POIDS = ui->le_poids1->text().toFloat();
     QString DATE_ACCUEIL=ui->le_date1->text();


     Animaux A(ID_ANIMAL,ESPECE,SEXE_ANIMAL,RACE,AGE,POIDS,DATE_ACCUEIL);



      //bool test=A.modifier2();


      QMessageBox msgBox;


      if(test)


      {


         ui->tableView->setModel(A.afficher());


         //ui->tableView->setModel(c.afficher_id());


         //ui->del_id_2->setModel(c.afficher_id());


         msgBox.setText("Modification avec succes.");




      }


      else


          msgBox.setText("Echec de Modification.");


          msgBox.exec();



}*/

void Gestion_Employe::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->table_animaux);

        //colums to export
        obj.addField(0, "ID_ANIMAL", "NUMBER");
        obj.addField(1, "ESPECE", "varchar(20)");
        obj.addField(2, "SEXE_ANIMAL", "varchar(20)");
        obj.addField(3, "RACE", "varchar(20)");
        obj.addField(4, "AGE", "NUMBER");
        obj.addField(5, "POIDS", "NUMBER");
        obj.addField(6, "DATE_ACCUEIL", "varchar(20)");


        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}



void Gestion_Employe::on_ModifierBouton_2_clicked()
{
    if((ui->le_espece_2->text() != "") &&(ui->le_sexe_3->text() != "")&&(ui->le_race_2->text() != "")&&(ui->le_age_2->text() != "")&&(ui->le_poids_2->text() != "")&&(ui->le_date_3->text() != ""))


        {


            Animaux tmp(ui->comboBoxModif_2->currentText().toInt(),ui->le_espece_2->text(),ui->le_sexe_3->text(),ui->le_race_2->text(),ui->le_age_2->text().toInt(),ui->le_poids_2->text().toInt(),ui->le_date_3->text());


            if(tmp.modifier())


            {


                //refresh combobox + tableau


                    ui->table_animaux->setModel(An.afficher());




            }


            else


            {


                QMessageBox::critical(this, QObject::tr("Modifier un Stock"),


                            QObject::tr("Erreur !.\n"


                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    }
}



void Gestion_Employe::on_comboBoxModif_2_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;




        QString id = ui->comboBoxModif_2->currentText();




        query =An.request(id);


        if(query.exec())


        {


            while(query.next())


            {


                ui->le_espece_2->setText(query.value(1).toString());


                ui->le_sexe_3->setText(query.value(2).toString());


                ui->le_race_2->setText(query.value(3).toString());


                ui->le_age_2->setText(query.value(4).toString());


                ui->le_poids_2->setText(query.value(5).toString());


                ui->le_date_3->setText(query.value(6).toString());





            }


        }




}




void Gestion_Employe::on_pb_clicked()
{
    int num=ui->le_num_2->text().toInt();
        QString nom=ui->le_nom_2->text();
        QString lieu=ui->le_lieu_2->text();
        QString date=ui->la_date->text();
        int nmbp=ui->le_nmbp->text().toInt();
        QString descp=ui->le_descp_2->text();
        int idemp=ui->le_num_supp_2->currentText().toInt();
        evenement Ev(num,nmbp,nom,lieu,descp,date,idemp);
       //  ui->tab_evenement->setModel(E.afficher());
         bool test=Ev.ajouter();
         QMessageBox msgBox ;
         if(test)
         {
             ui->tab_evenement->setModel(Ev.afficher());
              ui->tableView->setModel((Ev.afficher_num()));
             msgBox.setText("ajout avec succes.");
         }
        else
             msgBox.setText("echec d'ajout");
         msgBox.exec();
}

void Gestion_Employe::on_pb_supprimer_clicked()
{
    evenement Ev; Ev.setnum(ui->le_num_supp->currentText().toInt());

            bool test=Ev.supprimer(Ev.getnum());
            QMessageBox msgBox;
            if(test)
            {   ui->tab_evenement->setModel(Ev.afficher());
                ui->tableView->setModel((Ev.afficher_num()));

                ui->le_num_supp->setModel(Ev.afficher());
                msgBox.setText("Suppression avec succes.");


            }
            else
                msgBox.setText("Echec de suppression.");
                msgBox.exec();


}

void Gestion_Employe::on_load_list_3_clicked()
{
    QSqlQuery query;
    QSqlQueryModel *load=new QSqlQueryModel();

       query.prepare("SELECT num FROM evenements");
       query.exec();
       load->setQuery(query);
       ui->le_num_supp->setModel(load);

}

void Gestion_Employe::on_modifier_clicked()
{
    int num=ui->num_mod->text().toInt();
           QString nom=ui->nom_mod->text();
           QString lieu=ui->lieu_mod->text();
           QString date_ev=ui->date_mod->text();
           int nmbp=ui->nb_mod->text().toInt();
           QString descp=ui->descp_mod->text();
           bool test=Ev.modifier(num,nmbp,date_ev,descp,lieu,nom);
         QMessageBox msgBox;

         if(test)

         {ui->tableView->setModel((Ev.afficher_num()));
            ui->tab_evenement->setModel(Ev.afficher());


            //ui->del_id_2->setModel(c.afficher_id());

            msgBox.setText("Modification avec succes.");



         }

         else

             msgBox.setText("Echec de Modification.");

             msgBox.exec();
}

void Gestion_Employe::on_tableView_activated(const QModelIndex &index)
{
              QSqlQuery query;
              QString num=ui->tableView->model()->data(index).toString();
              query.prepare("select * from EVENEMENTS where num='"+num+"'");
              if(query.exec())
              {
                  while (query.next())
                  {
                      QString d = query.value(2).toString();
                      qDebug() << d;
                      QDateTime t = QDateTime::fromString(d,"dd/MM/yyyy");
                      qDebug() << t;
                     // ui->update_id->setText(query.value(0).toString());
                      ui->num_mod->setText(query.value(0).toString());
                      ui->nom_mod->setText(query.value(1).toString());
                       ui->lieu_mod->setText(query.value(4).toString());
                           ui->date_mod->setDateTime(t);

                      ui->nb_mod->setText(query.value(3).toString());

                      ui->descp_mod->setText(query.value(5).toString());
                  }
               }
                  else
                  {
                      QMessageBox::critical(nullptr, QObject::tr("Failed"),
                                  QObject::tr("Impossible.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
                  }

}

void Gestion_Employe::on_pushButton_3_clicked()
{
    ui->tab_evenement->setModel(Ev.tri_num());
}

void Gestion_Employe::on_pushButton_4_clicked()
{
    ui->tab_evenement->setModel(Ev.tri_nom());
}

void Gestion_Employe::on_pushButton_5_clicked()
{
    ui->tab_evenement->setModel(Ev.tri_date());
}

void Gestion_Employe::on_pushButton_6_clicked()
{
    ui->tab_evenement->setModel(Ev.tri_nbrp());
}

void Gestion_Employe::on_pushButton_7_clicked()
{

    QPdfWriter pdf("C:/Users/LENOVO/Desktop/event.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 30));
    QPixmap pxpic;
    pxpic.load("C:/Users/LENOVO/Desktop/amina/Atelier_Connexion/1.png");
    painter.drawPixmap(100,100,780,780,pxpic);
    painter.drawText(900,650,"Pet.O.S");
    painter.drawText(3000,2500,"LISTE Evenements");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Num evenement");
    painter.drawText(2300,3300,"Nom");
    painter.drawText(4300,3300,"Date");
    painter.drawText(6300,3300,"Nbr p");
    painter.drawText(8000,3300,"Lien");
    QSqlQuery query;
    query.prepare("select * from EVENEMENTS");
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

    int reponse = QMessageBox::question(this, "GÃ©nerer PDF", "<PDF EnregistrÃ©>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/LENOVO/Desktop/event.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}


void Gestion_Employe::on_calendarWidget_clicked(const QDate &date)
{
    QString newdate= date.toString("dd/MM/yyyy");
        qInfo() << newdate ;
        ui->tableView_2->setModel((Ev.recherche_date(newdate)));
}

/*void Gestion_Employe::sendMail()
{
    Smtp* smtp = new Smtp("aminaattafi8@gmail.com", "uigvnrzkbdcrriaw","smtp.gmail.com",465,30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("promotion", ui->lineEdit_10->text() , ui->lineEdit_9->text(),ui->textEdit->toPlainText());
}*/

/*void Gestion_Employe::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}*/



void Gestion_Employe::on_envoyer_clicked()
{
    connect(ui->envoyer, SIGNAL(clicked()),this, SLOT(sendMail()));
}

void Gestion_Employe::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
        QSqlQuery   *query= new QSqlQuery();
        query->prepare("SELECT * FROM EVENEMENTS WHERE NUM  LIKE'"+arg1+"%' or NOM  LIKE'"+arg1+"%' or LIEU  LIKE'"+arg1+"%'");
         query->exec();
         if (query->next()) {
         model->setQuery(*query);
         ui->tab_evenement->setModel(model);
         }
         else {
             QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                             QObject::tr("NO MATCH FOUND !!\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void Gestion_Employe::on_pb_2_clicked()
{
            QSqlQuery query;
            QSqlQueryModel *load=new QSqlQueryModel();
            query.prepare("SELECT ID_EMP FROM EMPLOYE");
            query.exec();
            load->setQuery(query);
            ui->le_num_supp_2->setModel(load);

}
void Gestion_Employe::update_label_51()
{


    set=A.read_from_arduino();
    ui->label_52->setNum(i);
    if(set=="1"){
        ui->label->setText("animal dispo");   // si les données reçues de arduino via la liaison série sont égales à 0
        ui->pushButton_8->setVisible(true);
     }
    if(set=="0"){
        ui->label_51->setText("pas d'animal");   // si les données reçues de arduino via la liaison série sont égales à 0
        ui->pushButton_8->setVisible(false);
     }
}

void Gestion_Employe::on_pushButton_8_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino
        i++;
}

void Gestion_Employe::on_deconnexion_4_clicked()
{
ui->menu->setCurrentWidget(ui->page_3);
}

void Gestion_Employe::on_pushButton_20_clicked()
{
    int id=ui->le_id_4->text().toInt();
    int id_d=ui->le_idd->text().toInt();
    int id_e=ui->le_ide_2->text().toInt();
    QString type=ui->le_type->currentText();
    QString quant=ui->le_quantite->text();
    QDate date=ui->le_date_5->date();


    dons d(id,id_d,id_e,type,quant,date);
    bool test=d.add();
    if(test)
    {
        popUp->setPopupText("ajouté avec succes");

        popUp->show();
        ui->tab_stock->setModel(d.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
void Gestion_Employe::on_supp_2_clicked()
{
    dons d1;
    d1.setid(ui->combosupp->currentText().toInt());
    bool test=d1.supprimer(d1.getid());
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select id_don from dons");
    qry->exec();
    modal->setQuery(*qry);
    ui->combosupp->setModel(modal);
    if(test)
    {
        popUp->setPopupText("supprimé avec succes");

        popUp->show();
        ui->tab_stock->setModel(d.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("supp successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" supp non.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_Employe::on_ModifierBouton_3_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select id_don from dons");
    qry->exec();
    modal->setQuery(*qry);
    int id=ui->comboBoxModif_4->currentText().toInt();
    int id_d=ui->le_idd_3->text().toInt();
    int id_e=ui->le_ide_4->text().toInt();
    QString type=ui->le_type_2->text();
    QString quant=ui->le_quantite_2->text();
    QDate date=ui->le_date_6->date();

     dons d2(id,id_d,id_e,type,quant,date);
     bool test=d2.modifier();
     QMessageBox msgBox;
     if(test)
     {
         popUp->setPopupText("modifié avec succes");

         popUp->show();
         msgBox.setText("Modification avec succes.");
           ui->tab_stock->setModel(d2.afficher());

     }
     else
         msgBox.setText("Echec de Modification.");
     msgBox.exec();
    }

void Gestion_Employe::on_pushButton_21_clicked()
{
    QPdfWriter pdf("C:/Users/user/Desktop/inegration/dali.pdf");

    QPainter painter(&pdf);

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"LISTE DONS");
    painter.setPen(Qt::black);

        painter.setFont(QFont("Arial", 20));

        painter.drawText(2000,2000,"Pet.O.S Smart Aid Association");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 25));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 9));
    painter.drawText(400,3300,"id_don");
    painter.drawText(2000,3300,"type_don");
    painter.drawText(3400,3300,"quantite_don");
    painter.drawText(5000,3300,"date ");
    painter.drawText(6400,3300,"id_employe");
     painter.drawText(7800,3300,"id_donneur");
     const QImage image("C:/dali/LOGO.jpg");
                 const QPoint imageCoordinates(1,1);
                 painter.drawImage(imageCoordinates,image);

    QSqlQuery query;
    query.prepare("select * from Dons");
    query.exec();
    while (query.next())
    {
        painter.drawText(400,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(3400,i,query.value(2).toString());
        painter.drawText(4700,i,query.value(3).toString());
        painter.drawText(7000,i,query.value(4).toString());
        painter.drawText(8000,i,query.value(5).toString());

        i = i +350;
    }

    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/Desktop/inegration/dali.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void Gestion_Employe::on_pushButton_22_clicked(){
    // background //
                  QLinearGradient gradient(0, 0, 0, 400);
                  gradient.setColorAt(0, QColor(90, 90, 90));
                  gradient.setColorAt(0.38, QColor(105, 105, 105));
                  gradient.setColorAt(1, QColor(70, 70, 70));
                  ui->plot->setBackground(QBrush(gradient));

                  QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                  amande->setAntialiased(false);
                  amande->setStackingGap(1);
                   //couleurs
                  amande->setName("statistiques des dons selon la somme  ");
                  amande->setPen(QPen(QColor(111, 9, 176).lighter(170)));
                  amande->setBrush(QColor(111, 9, 176));

                   //axe des abscisses
                  QVector<double> ticks;
                  QVector<QString> labels;
                  d.statistique(&ticks,&labels);

                  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                  textTicker->addTicks(ticks, labels);
                  ui->plot->xAxis->setTicker(textTicker);
                  ui->plot->xAxis->setTickLabelRotation(60);
                  ui->plot->xAxis->setSubTicks(false);
                  ui->plot->xAxis->setTickLength(0, 4);
                  ui->plot->xAxis->setRange(0, 8);
                  ui->plot->xAxis->setBasePen(QPen(Qt::white));
                  ui->plot->xAxis->setTickPen(QPen(Qt::white));
                  ui->plot->xAxis->grid()->setVisible(true);
                  ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                  ui->plot->xAxis->setTickLabelColor(Qt::white);
                  ui->plot->xAxis->setLabelColor(Qt::white);

                  // axe des ordonnées
                  ui->plot->yAxis->setRange(0,10);
                  ui->plot->yAxis->setPadding(5);
                  ui->plot->yAxis->setLabel("Statistiques");
                  ui->plot->yAxis->setBasePen(QPen(Qt::white));
                  ui->plot->yAxis->setTickPen(QPen(Qt::white));
                  ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                  ui->plot->yAxis->grid()->setSubGridVisible(true);
                  ui->plot->yAxis->setTickLabelColor(Qt::white);
                  ui->plot->yAxis->setLabelColor(Qt::white);
                  ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                  ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


                  QVector<double> PlaceData;
                  QSqlQuery q1("select quantite_don from dons");
                  while (q1.next()) {
                                int  nbr_fautee = q1.value(0).toInt();
                                PlaceData<< nbr_fautee;
                                  }
                  amande->setData(ticks, PlaceData);

                  ui->plot->legend->setVisible(true);
                  ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                  ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                  ui->plot->legend->setBorderPen(Qt::NoPen);
                  QFont legendFont = font();
                  legendFont.setPointSize(5);
                  ui->plot->legend->setFont(legendFont);
                  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}



void Gestion_Employe::on_tabWidget_8_currentChanged(int index)
{

        ui->tab_stock->setModel(d.afficher());
        index=0;
        QSqlQueryModel *modal=new QSqlQueryModel;
        QSqlQuery *qry=new QSqlQuery;
        qry->prepare("select id_don from dons");
        qry->exec();
        modal->setQuery(*qry);
        ui->combosupp->setModel(modal);
        ui->comboBoxModif_4->setModel(modal);
        ui->tab_modif->setModel(modal);


}
void Gestion_Employe::on_pb_chercher_1_clicked()
{
    dons D;
       QString choix=ui->comboBox_2->currentText();

       if (choix=="Id")
       {
           QString Id = ui->lineEdit_rech->text();
           ui->tab_stock->setModel(D.rechercher(Id));
       }
       if (choix=="Type")
       {
           QString Type = ui->lineEdit_rech->text();
           ui->tab_stock->setModel(D.recherchertype(Type));
       }
       if (choix=="Quantite")
       {
           QString Quantite = ui->lineEdit_rech->text();
           ui->tab_stock->setModel(D.rechercherquantite(Quantite));
       }


    }
void Gestion_Employe::on_comboBox_3_activated(const QString &arg1){

         dons D;
         QString choix=ui->comboBox_3->currentText();
         if (choix=="Tri par Id")
         {
             ui->tab_stock->setModel(D.trie_TYPE());
             ui->tab_stock->setModel(D.afficher());
             bool test=D.trie_TYPE();//tri Nom
             if (test)
             {

         ui->tab_stock->setModel(D.trie_TYPE());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri par ID effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri ID failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }
         if (choix=="Tri par Quantite")
         {
             ui->tab_stock->setModel(D.trie_QUANTITE());
             ui->tab_stock->setModel(D.afficher());
             bool test=D.trie_QUANTITE();//tri QUANTITE
             if (test)
             {

         ui->tab_stock->setModel(D.trie_QUANTITE());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri quantite effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri quantite failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }
         if (choix=="Tri par Date")
         {
             ui->tab_stock->setModel(D.trie_DATE());
             ui->tab_stock->setModel(D.afficher());
             bool test=D.trie_DATE();//tri DATE
             if (test)
             {

         ui->tab_stock->setModel(D.trie_DATE());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri DATE effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri DATE failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }

    }



void Gestion_Employe::on_pushButton_23_clicked()
{

    int id_i=ui->le_idi->text().toInt();
    int id_a=ui->le_ida->text().toInt();
    int id_e=ui->le_ide->text().toInt();
    QString etat=ui->le_vaccin->text();
    QString rapport=ui->le_rapport->text();
    //QString image=ui->IMG_Added->setPixmap(QPixmap::fromImage(image));
     // QString image=ui->IMG_Added->text();

    QDate date=ui->le_dateint->date();



    interventions
            d(id_i,id_a,id_e,etat,rapport,date);
    bool test=d.add();
    if(test)
    {
        ui->table_animaux_2->setModel(d.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_Employe::on_ModifierBouton_4_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select id_intervention from INTERVENTION");
    qry->exec();
    modal->setQuery(*qry);
    int id=ui->comboBoxModif_5->currentText().toInt();
    int id_a=ui->le_ida1->text().toInt();
    int id_e=ui->le_ide1->text().toInt();
    QString etat=ui->le_vaccin1->text();
    QString rapport=ui->le_rapport1->text();
    //QString image=ui->IMG_Added->text();
    QDate date=ui->dateEdit->date();

     interventions d2(id,id_a,id_e,etat,rapport,date);
     bool test=d2.modifier();
     QMessageBox msgBox;
     if(test)
     {
         msgBox.setText("Modification avec succes.");
           ui->table_animaux_2->setModel(d2.afficher());

     }
     else
         msgBox.setText("Echec de Modification.");
     msgBox.exec();
}


void Gestion_Employe::on_pb_pdfint_clicked()
{
   QPdfWriter pdf("D:/PDF/interventions.pdf");

   QPainter painter(&pdf);

   int i = 4000;
   painter.setPen(Qt::red);
   painter.setFont(QFont("Time New Roman", 25));
   painter.drawText(3000,1400,"LISTE interventions");
   painter.setPen(Qt::black);
   painter.setFont(QFont("Time New Roman", 25));
   painter.setPen(Qt::black);

       painter.setFont(QFont("Arial", 20));

       painter.drawText(2000,2000,"Pet.O.S Smart Aid Association");
   // painter.drawText(1100,2000,afficheDC);
   painter.drawRect(100,100,9400,2500);
   painter.drawRect(100,3000,9400,500);
   painter.setFont(QFont("Time New Roman", 9));
   painter.drawText(400,3300,"id_intervention");
   painter.drawText(2000,3300,"etat");
   painter.drawText(3400,3300,"rapport_sante");
   painter.drawText(5000,3300,"date ");
   painter.drawText(6400,3300,"id_employe");
    painter.drawText(7800,3300,"id_animal");
    const QImage image("C:/Users/ADMIN/Desktop/Final/Atelier_Connexion/LOGO.jpg");
                     const QPoint imageCoordinates(1,1);
                     painter.drawImage(imageCoordinates,image);

   QSqlQuery query;
   query.prepare("select * from INTERVENTION");
   query.exec();
   while (query.next())
   {
       painter.drawText(400,i,query.value(0).toString());
       painter.drawText(2000,i,query.value(1).toString());
       painter.drawText(3400,i,query.value(2).toString());
       painter.drawText(4700,i,query.value(3).toString());
       painter.drawText(7000,i,query.value(4).toString());
       painter.drawText(8000,i,query.value(5).toString());

       i = i +350;
   }

   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
   if (reponse == QMessageBox::Yes)
   {
       QDesktopServices::openUrl(QUrl::fromLocalFile("D:/PDF/interventions.pdf"));

       painter.end();
   }
   if (reponse == QMessageBox::No)
   {
       painter.end();
   }
}


void Gestion_Employe::on_pushButton_26_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("CHOOSE"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {

            image = image.scaledToWidth(ui->IMG_Added->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->IMG_Added->height(), Qt::SmoothTransformation);
            ui->IMG_Added->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("ERROR"),
            QObject::tr("Add Failed !"), QMessageBox::Ok);
        }
    }
}






void Gestion_Employe::on_pb_chercher_int_clicked()
{
    interventions D;
       QString choix=ui->comboBox_2->currentText();

       if (choix=="ID_intervention")
       {
           QString Id = ui->lineEdit_rech->text();
           ui->table_animaux_2->setModel(D.rechercher_idi(Id));
       }
       if (choix=="ID_animal")
       {
           QString ida = ui->lineEdit_rech->text();
           ui->table_animaux_2->setModel(D.rechercher_ida(ida));
       }
       if (choix=="ID_employe")
       {
           QString rapport_sante = ui->lineEdit_rech->text();
           ui->table_animaux_2->setModel(D.rechercher_ide(rapport_sante));
       }


}

void Gestion_Employe::on_comboBox_int2_activated(const QString &arg1)
{
    interventions D;
    QString choix=ui->comboBox_int2->currentText();
    if (choix=="Id_intervention")
    {
        ui->table_animaux_2->setModel(D.trie_idi());
        ui->table_animaux_2->setModel(D.afficher());
        bool test=D.trie_idi();//tri Nom
        if (test)
        {

    ui->table_animaux_2->setModel(D.trie_idi());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri par ID intervention effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri idi failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="Id_animal")
    {
        ui->table_animaux_2->setModel(D.trie_ida());
        ui->table_animaux_2->setModel(D.afficher());
        bool test=D.trie_ida();//tri rapport_sante
        if (test)
        {

    ui->table_animaux_2->setModel(D.trie_ida());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri id animal effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri id animal failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if (choix=="Date")
    {
        ui->table_animaux_2->setModel(D.trie_DATE());
        ui->table_animaux_2->setModel(D.afficher());
        bool test=D.trie_DATE();//tri DATE
        if (test)
        {

    ui->table_animaux_2->setModel(D.trie_DATE());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("tri DATE effectué \n"
                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

        }
        else
              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                          QObject::tr("tri DATE failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void Gestion_Employe::on_tabWidget_9_currentChanged(int index)
{
    ui->table_animaux_2->setModel(d.afficher());
    index=0;
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select ID_INTERVENTION from INTERVENTION");
    qry->exec();
    modal->setQuery(*qry);
    ui->del_id_4->setModel(modal);
    ui->comboBoxModif_5->setModel(modal);
    ui->tab_modif_2->setModel(modal);
}

void Gestion_Employe::on_tab_modif_2_activated(const QModelIndex &index)
{
    QString id=ui->tab_modif_2->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * from INTERVENTION where id_intervention='"+id+"' ");
    while (qry.next())
    {
        ui->le_type_2->setText(qry.value(1).toString());
        ui->le_ida1->setText(qry.value(2).toString());
        ui->le_vaccin1->setText(qry.value(4).toString());
        ui->le_ide1->setText(qry.value(4).toString());
        ui->dateEdit->setDate(qry.value(3).toDate());



    }
}

void Gestion_Employe::on_supp_3_clicked()
{
    interventions d1;
    d1.setid_i(ui->del_id_4->currentText().toInt());
    bool test=d1.supprimer(d1.getid_i());
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select id_intervention from INTERVENTION");
    qry->exec();
    modal->setQuery(*qry);
    ui->del_id_4->setModel(modal);
    if(test)
    {
        ui->table_animaux_2->setModel(d.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("supp successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" supp non.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_Employe::on_tab_modif_activated(const QModelIndex &index)
{
    QString id=ui->tab_modif->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * from dons where id_don='"+id+"' ");
    while (qry.next())
    {
        ui->le_type_2->setText(qry.value(1).toString());
        ui->le_quantite_2->setText(qry.value(2).toString());
        ui->le_idd_3->setText(qry.value(4).toString());
        ui->le_ide_4->setText(qry.value(4).toString());
        ui->le_date_6 ->setDate(qry.value(3).toDate());



    }
}

void Gestion_Employe::on_deconnexion_5_clicked()
{
     ui->menu->setCurrentWidget(ui->page_4);
}
void Gestion_Employe::update_lcd(const QString Distance)
{

    ui->lcdNumber_Distance->display(Distance);

}
bool Gestion_Employe::insert_distance(float distance)
{
    QSqlQuery query;
    QString dis = QString::number(distance);
    query.prepare("INSERT INTO distance (distance,date_distance)"
                  "VALUES(:distance,:date_distance)");
    query.bindValue(":distance",dis);
    query.bindValue(":date_distance",date_distance);
    return query.exec();
}
 QSqlQuery * Gestion_Employe::search(QDateTime date_insert)
{
     QSqlQuery * model = new QSqlQuery();
     model->prepare("select id_distance from distance where date_distance=:date_distance");
     model->bindValue(":date_distance",date_insert);
     model->exec();
   return model;}
QSqlQueryModel * Gestion_Employe::afficher_distance()
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("select * from distance");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Distance"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Distance_Cm"));
        return model;
}
bool Gestion_Employe::modifier_distance(QString id,float distance)
{
    QSqlQuery query;
        QString dis= QString::number(distance);
        query.prepare("UPDATE distance SET distance=:distance WHERE id_distance=:id_distance;");
        query.bindValue(":distance",dis);
        query.bindValue(":id_distance",id);
        return query.exec();
}

QSqlQuery * Gestion_Employe::search_newDistance(QString id_distance)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select distance from distance where id_distance=:id_distance");
    model->bindValue(":id_distance",id_distance);
    model->exec();
  return model;

}
void Gestion_Employe::update_label()
{
 data1=A.read_from_arduino();
 buffer = QString::fromStdString(data.toStdString());

float Distance= buffer.toFloat();
if (!count)
{
 date_distance= QDateTime::currentDateTime();
 bool test=insert_distance(Distance);
 if (test)
 {
     QSqlQuery *m = search(date_distance);
                    if(m->next())
                    {
                        int id = m->value(0).toInt();
                id_distance = QString::number(id);
                        count=1;
                    }
 }
 else{ qDebug() << "Error_insertion";}
}
else
{
    bool test = modifier_distance(id_distance,Distance);
                if(test)
                {
                    qDebug() << " - Update = TRUE";
                    ui->tableView_distance->setModel(afficher_distance());
                }
                else qDebug() << " - Update = False";
}
/*QSqlQuery *tab = search_newDistance(id_distance);
                if(tab->next())
                {
                    Distance = tab->value(1).toFloat();
                }
*/

        if( Distance > 10.0)
{
            ui->label_etat->setText("alerte"); // si les données reçues de arduino via la liaison série sont superiere a 10
        // alors afficher ON
         // QMessageBox::information(nullptr, QObject::tr("ok"),
                      //  QObject::tr("le chat est sorti de son cage !.\n"
                              //      "Click Cancel to exit."), QMessageBox::Cancel);

          popUp->setPopupText("Alerte! le chat est sorti de son cage!!!!!");

        popUp->show();
        }
        else //if ( Distance < 10.0)
{
            ui->label_etat->setText("l'animal est dans son cage");   // si les données reçues de arduino via la liaison série sont inferieur a 10
         //alors afficher ON
}


       Gestion_Employe::update_lcd(buffer);


}






void Gestion_Employe::on_pushButton_clicked()
{
     ui->menu->setCurrentWidget(ui->menu_2);
}

void Gestion_Employe::on_push_button4_clicked()
{
     ui->menu->setCurrentWidget(ui->menu_2);
}

void Gestion_Employe::on_pushButton9_clicked()
{
       ui->menu->setCurrentWidget(ui->menu_2);
}

void Gestion_Employe::on_pushButton_25_clicked()
{
    ui->menu->setCurrentWidget(ui->menu_2);

}
