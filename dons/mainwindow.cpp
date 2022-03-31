#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dons.h"
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     ui->tab_stock->setModel(d.afficher());
     QSqlQueryModel *modal=new QSqlQueryModel;
     QSqlQuery *qry=new QSqlQuery;
     qry->prepare("select id_don from dons");
     qry->exec();
     modal->setQuery(*qry);
     ui->combosupp->setModel(modal);
     ui->tab_modif->setModel(modal);



}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_clicked()
{
    int id=ui->le_id->text().toInt();
    int id_d=ui->le_idd->text().toInt();
    int id_e=ui->le_ide->text().toInt();
    QString type=ui->le_type->currentText();
    QString quant=ui->le_quant->text();
    QDate date=ui->le_date->date();


    dons d(id,id_d,id_e,type,quant,date);
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
    qry->prepare("select id_don from dons");
    qry->exec();
    modal->setQuery(*qry);
    int id=ui->combomodif->currentText().toInt();
    int id_d=ui->le_idd2->text().toInt();
    int id_e=ui->le_ide2->text().toInt();
    QString type=ui->le_type_2->text();
    QString quant=ui->le_quant_2->text();
    QDate date=ui->date_2->date();

     dons d2(id,id_d,id_e,type,quant,date);
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
    qry->prepare("select id_don from dons");
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
    qry.prepare("select * from dons where id_don='"+id+"' ");
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

         dons D;
         QString choix=ui->comboBox->currentText();
         if (choix=="Id")
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
                               QObject::tr("tri type failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }
         if (choix=="Quantite")
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
void MainWindow::on_pushButton_clicked(){
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





void MainWindow::on_pushButton_3_clicked()
{
    QPdfWriter pdf("C:/dali/dons.pdf");

    QPainter painter(&pdf);

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"LISTE DONS");
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
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/dali/dons.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}


