#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDate"
#include "QtDebug"
#include "connection.h"
#include <QMessageBox>
#include <QPixmap>
#include<QSystemTrayIcon>
#include <QApplication>
#include<QSystemTrayIcon>
#include <QApplication>
#include <QModelIndex>
#include <QItemDelegate>
#include <QSize>
#include <QSpinBox>
#include <iostream>
#include <QDesktopServices>

#include <QIntValidator>
#include <QtGui>
#include "QString"
#include<QUrl>
#include <QPainter>
#include <QRectF>
#include <QStaticText>
#include"evenement.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_num_2->setValidator(  new QIntValidator(0, 9999999, this));
    ui->tab_evenement->setModel(E.afficher());
    ui->tableView->setModel((E.afficher_num()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_clicked()
{
    int num=ui->le_num_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString lieu=ui->le_lieu_2->text();
    QString date=ui->la_date->text();
    int nmbp=ui->le_nmbp->text().toInt();
    QString descp=ui->le_descp_2->text();
    int idemp=ui->le_num_supp_2->currentText().toInt();
    evenement E(num,nmbp,nom,lieu,descp,date,idemp);
   //  ui->tab_evenement->setModel(E.afficher());
     bool test=E.ajouter();
     QMessageBox msgBox ;
     if(test)
     {
         ui->tab_evenement->setModel(E.afficher());
          ui->tableView->setModel((E.afficher_num()));
         msgBox.setText("ajout avec succes.");
     }
    else
         msgBox.setText("echec d'ajout");
     msgBox.exec();
}


void MainWindow::on_pb_supprimer_clicked()
{
    evenement E; E.setnum(ui->le_num_supp->currentText().toInt());

        bool test=E.supprimer(E.getnum());
        QMessageBox msgBox;
        if(test)
        {   ui->tab_evenement->setModel(E.afficher());
            ui->tableView->setModel((E.afficher_num()));

            ui->le_num_supp->setModel(E.afficher());
            msgBox.setText("Suppression avec succes.");


        }
        else
            msgBox.setText("Echec de suppression.");
            msgBox.exec();

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->tab_evenement->setModel(E.afficher());
}

void MainWindow::on_load_list_clicked()
{
    QSqlQuery query;
    QSqlQueryModel *load=new QSqlQueryModel();

       query.prepare("SELECT num FROM evenements");
       query.exec();
       load->setQuery(query);
       ui->le_num_supp->setModel(load);
}

void MainWindow::on_modifier_clicked()
{
       int num=ui->num_mod->text().toInt();
       QString nom=ui->nom_mod->text();
       QString lieu=ui->lieu_mod->text();
       QString date_ev=ui->date_mod->text();
       int nmbp=ui->nb_mod->text().toInt();
       QString descp=ui->descp_mod->text();
       bool test=E.modifier(num,nmbp,date_ev,descp,lieu,nom);
     QMessageBox msgBox;

     if(test)

     {ui->tableView->setModel((E.afficher_num()));
        ui->tab_evenement->setModel(E.afficher());


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

void MainWindow::on_pushButton_clicked()
{
    ui->tab_evenement->setModel(E.tri_num());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tab_evenement->setModel(E.tri_nom());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tab_evenement->setModel(E.tri_date());
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tab_evenement->setModel(E.tri_nbrp());
}

void MainWindow::on_pushButton_5_clicked()
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

    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
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

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QString newdate= date.toString("dd/MM/yyyy");
    qInfo() << newdate ;
    ui->tableView_2->setModel((E.recherche_date(newdate)));

}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("aminaattafi8@gmail.com", "uigvnrzkbdcrriaw","smtp.gmail.com",465,30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("promotion", ui->lineEdit_10->text() , ui->lineEdit_9->text(),ui->textEdit->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_envoyer_clicked()
{
    connect(ui->envoyer, SIGNAL(clicked()),this, SLOT(sendMail()));
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
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

void MainWindow::on_pb_2_clicked()
{
        QSqlQuery query;
        QSqlQueryModel *load=new QSqlQueryModel();
        query.prepare("SELECT ID_EMP FROM EMPLOYE");
        query.exec();
        load->setQuery(query);
        ui->le_num_supp_2->setModel(load);
}
