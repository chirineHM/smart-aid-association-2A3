#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interventions.h"
#include"connection.h"
#include <QSqlQuery>
#include<QMessageBox>
#include<QComboBox>
#include "QSqlQuery"
#include "qcustomplot.h"
#include <QTableView>
#include <qmessagebox.h>
#include <QIntValidator>
#include <QSqlQuery>
#include <QScrollBar>
#include <qfiledialog.h>
#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QComboBox>
#include <QPixmap>
#include <connection.h>
#include <imagehlp.h>
#include "popup.h"
#include "Arduino.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_stock->setModel(d.afficher());
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("select ID_INTERVENTION from INTERVENTION");
    qry->exec();
    modal->setQuery(*qry);
    ui->combosupp->setModel(modal);
    ui->tab_modif->setModel(modal);


    // read_from_arduino();



         int ret=A.connect_arduino(); // lancer la connexion à arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                 break;
              case(-1):qDebug() << "arduino is not available";
              }
               QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}
MainWindow::~MainWindow()
{
   delete ui;
}



void MainWindow::on_add_clicked()
{
   int id_i=ui->le_idi->text().toInt();
   int id_a=ui->le_ida->text().toInt();
   int id_e=ui->le_idemp->text().toInt();
   QString etat=ui->le_vaccin->currentText();
   QString rapport=ui->le_rapport->text();
   //QString image=ui->IMG_Added->setPixmap(QPixmap::fromImage(image));
    // QString image=ui->IMG_Added->text();

   QDate date=ui->le_dateint->date();



   interventions d(id_i,id_a,id_e,etat,rapport,date);
   bool test=d.add();
   if(test)
   {
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

void MainWindow::on_delete_2_clicked()
{
   interventions d1;
   d1.setid_i(ui->combosupp->currentText().toInt());
   bool test=d1.supprimer(d1.getid_i());
   QSqlQueryModel *modal=new QSqlQueryModel;
   QSqlQuery *qry=new QSqlQuery;
   qry->prepare("select id_intervention from INTERVENTION");
   qry->exec();
   modal->setQuery(*qry);
   ui->combosupp->setModel(modal);
   if(test)
   {
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





void MainWindow::on_modif_clicked()
{
   QSqlQueryModel *modal=new QSqlQueryModel;
   QSqlQuery *qry=new QSqlQuery;
   qry->prepare("select id_intervention from INTERVENTION");
   qry->exec();
   modal->setQuery(*qry);
   int id=ui->combomodif->currentText().toInt();
   int id_a=ui->le_idd2->text().toInt();
   int id_e=ui->le_ide2->text().toInt();
   QString etat=ui->le_type_2->text();
   QString rapport=ui->le_quant_2->text();
   QString image=ui->IMG_Added->text();
   QDate date=ui->date_2->date();

    interventions d2(id,id_a,id_e,etat,rapport,date,image);
    bool test=d2.modifier();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Modification avec succes.");
          ui->tab_stock->setModel(d2.afficher());

    }
    else
        msgBox.setText("Echec de Modification.");
    msgBox.exec();
   }


void MainWindow::on_tabWidget_currentChanged(int index)
{
   ui->tab_stock->setModel(d.afficher());
   index=0;
   QSqlQueryModel *modal=new QSqlQueryModel;
   QSqlQuery *qry=new QSqlQuery;
   qry->prepare("select ID_INTERVENTION from INTERVENTION");
   qry->exec();
   modal->setQuery(*qry);
   ui->combosupp->setModel(modal);
   ui->combomodif->setModel(modal);
   ui->tab_modif->setModel(modal);

}




void MainWindow::on_tab_modif_activated(const QModelIndex &index)
{
   QString id=ui->tab_modif->model()->data(index).toString();

   QSqlQuery qry;
   qry.prepare("select * from INTERVENTION where id_intervention='"+id+"' ");
   while (qry.next())
   {
       ui->le_type_2->setText(qry.value(1).toString());
       ui->le_quant_2->setText(qry.value(2).toString());
       ui->le_idd2->setText(qry.value(4).toString());
       ui->le_ide2->setText(qry.value(4).toString());
       ui->date_2->setDate(qry.value(3).toDate());



   }
}
void MainWindow::on_comboBox_activated(const QString &arg1){

        interventions D;
        QString choix=ui->comboBox->currentText();
        if (choix=="Id_intervention")
        {
            ui->tab_stock->setModel(D.trie_idi());
            ui->tab_stock->setModel(D.afficher());
            bool test=D.trie_idi();//tri Nom
            if (test)
            {

        ui->tab_stock->setModel(D.trie_idi());
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
            ui->tab_stock->setModel(D.trie_ida());
            ui->tab_stock->setModel(D.afficher());
            bool test=D.trie_ida();//tri rapport_sante
            if (test)
            {

        ui->tab_stock->setModel(D.trie_ida());
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

void MainWindow::on_pushButton_2_clicked()
{
   interventions D;
      QString choix=ui->comboBox_2->currentText();

      if (choix=="ID_intervention")
      {
          QString Id = ui->lineEdit_rech->text();
          ui->tab_stock->setModel(D.rechercher_idi(Id));
      }
      if (choix=="ID_animal")
      {
          QString ida = ui->lineEdit_rech->text();
          ui->tab_stock->setModel(D.rechercher_ida(ida));
      }
      if (choix=="ID_employe")
      {
          QString rapport_sante = ui->lineEdit_rech->text();
          ui->tab_stock->setModel(D.rechercher_ide(rapport_sante));
      }


   }






void MainWindow::on_pushButton_3_clicked()
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


void MainWindow::on_Inserer_IMG_clicked()
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





