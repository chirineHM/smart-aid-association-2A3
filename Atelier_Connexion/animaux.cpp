#include "animaux.h"
#include"connection.h"
//#include "ui_animaux.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>


Animaux::Animaux()
{
  ID_ANIMAL=0;ESPECE="";SEXE_ANIMAL="";RACE="";AGE=0;POIDS=0;DATE_ACCUEIL="";
}
Animaux::Animaux(int ID_ANIMAL,QString ESPECE,QString SEXE_ANIMAL,QString RACE,float AGE,float POIDS	,QString DATE_ACCUEIL)
{
    this->ID_ANIMAL=ID_ANIMAL;
    this->ESPECE=ESPECE	;
    this->SEXE_ANIMAL=SEXE_ANIMAL;
    this->RACE=RACE	;
    this->AGE=AGE;
    this->POIDS=POIDS;
    this->DATE_ACCUEIL=DATE_ACCUEIL;
}
int Animaux::getid(){return ID_ANIMAL;}
QString Animaux::getespece(){return ESPECE;}
QString Animaux::getsexe(){return SEXE_ANIMAL;}
QString Animaux::geterace(){return RACE;}
float Animaux::getage(){return AGE;}
float Animaux::getpoids(){return POIDS;}
QString Animaux::getdate_acc(){return DATE_ACCUEIL;}

void Animaux::setid(int ID_ANIMAL){this->ID_ANIMAL=ID_ANIMAL;}
void Animaux::setespece(QString ESPECE){this->ESPECE=ESPECE;}
void Animaux::setsexe(QString SEXE_ANIMAL){this->SEXE_ANIMAL=SEXE_ANIMAL;}
void Animaux::setrace(QString RACE){this->RACE=RACE	;}
void Animaux::setage(float AGE){this->AGE=AGE;}
void Animaux::setpoids(float POIDS){this->POIDS=POIDS;}
void Animaux::setdate_acc(QString DATE_ACCUEIL){this->DATE_ACCUEIL=DATE_ACCUEIL;}

bool Animaux::ajouter()
{

    QString idc_QString=QString::number(ID_ANIMAL);
    QString age_QString=QString::number(AGE);
    QString poids_QString=QString::number(POIDS);
        QSqlQuery query;
              query.prepare("INSERT INTO ANIMAUX (ID_ANIMAL,ESPECE, SEXE_ANIMAL,RACE,AGE,POIDS,DATE_ACCUEIL) "
                            "VALUES (:ID_ANIMAL, :ESPECE, :SEXE_ANIMAL, :RACE,:AGE,:POIDS, :DATE_ACCUEIL)");
              query.bindValue(0, idc_QString);
              query.bindValue(1, ESPECE);
              query.bindValue(2, SEXE_ANIMAL);
              query.bindValue(3, RACE);
              query.bindValue(4, age_QString);
              query.bindValue(5, poids_QString);
              query.bindValue(6, DATE_ACCUEIL);


            return  query.exec();
}

QSqlQueryModel* Animaux::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT * FROM ANIMAUX");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL,"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("SEXE_ANIMAL"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("RACE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("AGE"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_ACCUEIL"));



        return model;

}

bool Animaux::supprimer(int ID_ANIMAL)
{
    QSqlQuery query;
          query.prepare(" Delete from ANIMAUX where ID_ANIMAL=:ID_ANIMAL");
          query.bindValue(0, ID_ANIMAL);
        return  query.exec();


}
bool Animaux :: modifier()
{
    QSqlQuery query;
    QString idc_QString=QString::number(ID_ANIMAL);
    QString age_QString=QString::number(AGE);
    QString poids_QString=QString::number(POIDS);
    query.prepare("update ANIMAUX  set "
                  "ESPECE = :ESPECE, SEXE_ANIMAL = :SEXE_ANIMAL, RACE = :RACE, "
                  "AGE = :AGE, POIDS=:POIDS,DATE_ACCUEIL=:DATE_ACCUEIL where ID_ANIMAL = :ID_ANIMAL ;");
    query.bindValue(":ID_ANIMAL", idc_QString);
    query.bindValue(":DATE_ACCUEIL", DATE_ACCUEIL);
    query.bindValue(":ESPECE", ESPECE);
     query.bindValue(":SEXE_ANIMAL", SEXE_ANIMAL);
    query.bindValue(":RACE", RACE);
    query.bindValue(":POIDS", poids_QString);
    query.bindValue(":AGE", age_QString);


    return query.exec();
}
