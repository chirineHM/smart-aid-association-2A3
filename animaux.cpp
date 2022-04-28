#include "animaux.h"
#include"connection.h"
//#include "ui_animaux.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QDebug>

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
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
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
/*bool Animaux :: modifier()
{
    QSqlQuery query;
    QString idc_QString=QString::number(ID_ANIMAL);
    QString age_QString=QString::number(AGE);
    QString poids_QString=QString::number(POIDS);
    query.prepare("update ANIMAUX  set "
                  "ESPECE = :ESPECE, SEXE_ANIMAL = :SEXE_ANIMAL, RACE = :RACE, "
                  "AGE = :AGE, POIDS = :POIDS,DATE_ACCUEIL = :DATE_ACCUEIL where ID_ANIMAL = :ID_ANIMAL ;");
    query.bindValue(":ID_ANIMAL", idc_QString);
    query.bindValue(":DATE_ACCUEIL", DATE_ACCUEIL);
    query.bindValue(":ESPECE", ESPECE);
     query.bindValue(":SEXE_ANIMAL", SEXE_ANIMAL);
    query.bindValue(":RACE", RACE);
    query.bindValue(":POIDS", poids_QString);
    query.bindValue(":AGE", age_QString);


    return query.exec();
}

bool Animaux::modifier2()

    {


        QSqlQuery query;QString res =QString::number(ID_ANIMAL);
        QString age_QString=QString::number(AGE);
        QString poids_QString=QString::number(POIDS);

            query.prepare("UPDATE ANIMAUX SET  ESPECE = :ESPECE, SEXE_ANIMAL = :SEXE_ANIMAL, RACE = :RACE,AGE = :AGE,POIDS = :POIDS,DATE_ACCUEIL= :DATE_ACCUEIL WHERE ID_ANIMAL=:ID_ANIMAL ");
            query.bindValue(":ID_ANIMAL", res);
            query.bindValue(":ESPECE", ESPECE);

            query.bindValue(":SEXE_ANIMAL", SEXE_ANIMAL);

            query.bindValue(":RACE", RACE);

            query.bindValue(":AGE", age_QString);

            query.bindValue(":POIDS", poids_QString);

            query.bindValue(":DATE_ACCUEIL", DATE_ACCUEIL);


             return query.exec();


    }*/



QSqlQueryModel* rechercher_identifiant(int  identifiant)
{

    QSqlQuery * q = new  QSqlQuery ();

                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from ANIMAUX where ID_ANIMAL=:identifiant");
                     q->bindValue(":identifiant",identifiant );
                     q->exec();

         model->setQuery(*q);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("ESPECE"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));


         return model;
}
QSqlQueryModel * Animaux::tri(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM ANIMAUX ORDER BY AGE");
   q->exec();
   model->setQuery(*q);

   return model;
}
QSqlQueryModel * Animaux::tri1(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM ANIMAUX ORDER BY ESPECE");
   q->exec();
   model->setQuery(*q);

   return model;
}
QSqlQueryModel * Animaux::tri2(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM ANIMAUX ORDER BY DATE_ACCUEIL");
   q->exec();
   model->setQuery(*q);

   return model;
}


/***********************************************/

/*void Animaux::modifierF(){
    QSqlQuery query;
    QString res= QString::number(ID_ANIMAL);
    query.prepare("UPDATE ANIMAUX  SET ESPECE=:ESPECE, SEXE_ANIMAL=:SEXE_ANIMAL, RACE=:RACE, AGE=:AGE,POIDS=:POIDS , DATE_ACCUEIL=:DATE_ACCUEIL WHERE ID_ANIMAL=:id ;");
    query.bindValue(":id", res);
    query.bindValue(":ESPECE", ESPECE);
    query.bindValue(":SEXE_ANIMAL", SEXE_ANIMAL);
    query.bindValue(":RACE", RACE);
    query.bindValue(":AGE", AGE);
    query.bindValue(":POIDS",POIDS);
    query.bindValue(":DATE_ACCUEIL",DATE_ACCUEIL);

    query.exec();
}*/

bool Animaux::modifier()

    {


        QSqlQuery query;

            query.prepare("UPDATE ANIMAUX SET ESPECE= :ESPECE, SEXE_ANIMAL= :SEXE_ANIMAL, RACE= :RACE, AGE= :AGE, POIDS= :POIDS, DATE_ACCUEIL= :DATE_ACCUEIL WHERE ID_ANIMAL= :ID_ANIMAL ");

            query.bindValue(":ID_ANIMAL", ID_ANIMAL);

            query.bindValue(":ESPECE", ESPECE);

            query.bindValue(":SEXE_ANIMAL", SEXE_ANIMAL);

            query.bindValue(":RACE", RACE);

            query.bindValue(":AGE", AGE);

            query.bindValue(":POIDS", POIDS);

            query.bindValue(":DATE_ACCUEIL", DATE_ACCUEIL);



             return query.exec();


    }

QSqlQueryModel * Animaux::remplircomboAnimal()

{

    QSqlQueryModel * mod= new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select ID_ANIMAL from ANIMAUX");

    query.exec();

    mod->setQuery(query);

    return mod;

}



QSqlQuery Animaux::request(QString id)

{

    QSqlQuery query;

    query.prepare("select * from ANIMAUX where ID_ANIMAL= '"+id+"'");

    query.addBindValue(id);

    query.exec();

    return query;

}
