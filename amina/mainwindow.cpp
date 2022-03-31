 #include "mainwindow.h"
#include "ui_mainwindow.h"
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

    evenement E(num,nmbp,nom,lieu,descp,date);
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



     evenement e2(num,nmbp,date_ev,descp,lieu,nom);

     bool test=e2.modifier();

     QMessageBox msgBox;

     if(test)

     {ui->tableView->setModel((E.afficher_num()));
        ui->tab_evenement->setModel(e2.afficher());


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
    painter.drawText(3000,1500,"LISTE Evenements");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(2700,200,7300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Num evenement");
    painter.drawText(2300,3300,"Nom");
    painter.drawText(4300,3300,"Date");
    painter.drawText(6300,3300,"Nbr p");
    painter.drawText(8000,3300,"Lieu");
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

void MainWindow::on_pushButton_6_clicked()
{
    QString nom = ui->lineEdit->text();
    if(ui->checkBox->isChecked())
         ui->tab_evenement->setModel(E.recherche_nom(nom));
    if(ui->checkBox_2->isChecked())
    {
        int num = ui->lineEdit->text().toInt();
        ui->tab_evenement->setModel(E.recherche(num));
    }
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QString newdate= date.toString("dd/MM/yyyy");
    qInfo() << newdate ;
    ui->tableView_2->setModel((E.recherche_date(newdate)));
}

