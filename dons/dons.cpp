#include "dons.h"
#include"connection.h"
//#include "ui_dons.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>


Dons::Dons()
{
  Id_don=0;id_donneur=0;id_employe=0;type_don="";quantite_don="";date_don="";
}
Dons::Dons(int Id_don,int id_donneur ,int id_employe,QString type_don,QString quantite_don,QString date_don)
{
    this->Id_don=Id_don;

    this->id_donneur=id_donneur;
    this->id_employe=id_employe;
    this->type_don=type_don	;
    this->quantite_don=quantite_don;
    this->date_don=date_don	;

}
int Dons::getid(){return Id_don;}
int Dons::getid_d(){return id_donneur;}
int Dons::getid_e(){return id_employe;}
QString Dons::gettype(){return type_don;}
QString Dons::getquantite(){return quantite_don;}
QString Dons::getdate(){return date_don;}

void Dons::setid(int Id_don){this->Id_don=Id_don;}
void Dons::setid_d(int id_donneur){this->id_donneur=id_donneur;}
void Dons::setid_e(int id_employe){this->id_employe=id_employe;}
void Dons::settype(QString type_don){this->type_don=type_don;}
void Dons::setquantite(QString quantite_don){this->quantite_don=quantite_don;}

void Dons::setdate(QString date_don){this->date_don=date_don;}

bool Dons::ajouter()
{

    QString idc_QString=QString::number(Id_don);
        QSqlQuery query;
              query.prepare("INSERT INTO DONS (Id_don,id_donneur,id_employe,type_don,quantite_don,date_don) "
                            "VALUES (:id_don, :id_donneur, :id_employe, :type_don,:quantite_don, :date_don)");
              query.bindValue(0, idc_QString);
              query.bindValue(1, id_donneur);
              query.bindValue(2, id_employe);
              query.bindValue(3, type_don);
              query.bindValue(4,quantite_don);
              query.bindValue(6, date_don);


            return  query.exec();
}

QSqlQueryModel* Dons::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT * FROM Dons");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id_don,"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_donneur"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_don"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantite_don"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("date_don"));



        return model;

}
bool Dons::supprimer(int Id_don)
{
    QSqlQuery query;
          query.prepare(" Delete from ANIMAUX where Id_donL=:Id_don");
          query.bindValue(0, Id_don);
        return  query.exec();


}
