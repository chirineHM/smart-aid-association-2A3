#include "inter.h"
#include"connection.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>


intervention::intervention()
{
 ID_intervention=0; ID_veterinaire=0; ID_ANIMAL=0;Etat_vaccin="";Etat_castration="";Rapport_sante="";DATE_intervention="";
}
intervention::intervention(int ID_intervention ,int ID_ANIMAL  , int ID_veterinaire ,QString Etat_vaccin,QString Etat_castration,QString Rapport_sante	,QString DATE_intervention)
{
    this->ID_intervention=ID_intervention;
    this->ID_ANIMAL=ID_ANIMAL;
    this->ID_veterinaire=ID_veterinaire;
    this->Etat_vaccin=Etat_vaccin	;
    this->Etat_castration=Etat_castration;
    this->Rapport_sante=Rapport_sante	;
    this->DATE_intervention=DATE_intervention;
}
int intervention::getidi(){return ID_intervention;}
int intervention::getida(){return ID_ANIMAL;}
int intervention::getidv(){return ID_veterinaire;}
QString intervention::getev(){return Etat_vaccin;}
QString intervention::getec(){return Etat_castration;}

QString intervention::getrapport(){return Rapport_sante;}
QString intervention::getdate_inter(){return DATE_intervention;}

void intervention::setidi(int ID_intervention){this->ID_intervention=ID_intervention;}
void intervention::setida(int ID_ANIMAL){this->ID_ANIMAL=ID_ANIMAL;}
void intervention::setidv(int ID_veterinaire){this->ID_veterinaire=ID_veterinaire;}
void intervention::setev(QString Etat_vaccin){this->Etat_vaccin=Etat_vaccin;}
void intervention::setec(QString Etat_castration){this->Etat_castration=Etat_castration;}
void intervention::setrapport(QString Rapport_sante){this->Rapport_sante=Rapport_sante	;}
void intervention::setdate_inter(QString DATE_inter){this->DATE_intervention=DATE_inter;}

bool intervention::ajouter()
{

    QString idi_QString=QString::number(ID_intervention);
    QString ida_QString=QString::number(ID_ANIMAL);
    QString idv_QString=QString::number(ID_veterinaire);
        QSqlQuery query;
              query.prepare("INSERT INTO INTERVENTION (ID_intervention,ID_ANIMAL,ID_veterinaire,Etat_vaccin,Etat_castration,Rapport_sante,DATE_intervention) "
                            "VALUES (:ID_intervention,:ID_ANIMAL,:ID_veterinaire, :Etat_vaccin, :Etat_castration, :Rapport_sante, :DATE_intervention)");
              query.bindValue(0, idi_QString);
              query.bindValue(1, ida_QString);
              query.bindValue(2, idv_QString);
              query.bindValue(3, Etat_vaccin);
              query.bindValue(4, Etat_castration);
              query.bindValue(5, Rapport_sante);

              query.bindValue(6, DATE_intervention);


            return  query.exec();
}

QSqlQueryModel* intervention::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT * FROM INTERVENTION");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_intervention"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_veterinaire"));

            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat_vaccin"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat_castration"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Rapport_sante"));
        return  model;


}

bool intervention::supprimer(int ID_intervention)
{

    QSqlQuery query;
              query.prepare(" Delete from INTERVENTION where ID_intervention=:ID_intervention");
              query.bindValue(0, ID_intervention);
            return  query.exec();
}
bool intervention::modifier()
{
QSqlQuery query;
query.prepare(" Delete from INTERVENTION where ID_intervention=:ID_intervention");
query.bindValue(0, ID_intervention);
{
    QSqlQuery query;
    QString idi_QString=QString::number(ID_intervention);
    QString age_QString=QString::number(ID_ANIMAL);
    QString poids_QString=QString::number(ID_veterinaire);
    query.prepare("update INTERVENTION set "
                  "Etat_vaccin = :Etat_vaccin, ,Etat_castration = :Etat_castration, Rapport_sante = :Rapport_sante, "
                  "DATE_ACCUEIL=:DATE_ACCUEIL where ID_intervention = :ID_intervention ;");
    query.bindValue(":ID_intervention", idi_QString);
    query.bindValue(":DATE_intervention", DATE_intervention);
    query.bindValue(":Etat_vaccin", Etat_vaccin);
     query.bindValue(":Etat_castration", Etat_castration);
    query.bindValue(":Rapport_sante", Rapport_sante);


    return query.exec();
}
}
