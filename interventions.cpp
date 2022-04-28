#include "interventions.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
interventions::interventions()
{
    id_intervention=0;
    id_animal=0;
    id_employe=0;
    etat="";//etatetat
    rapport_sante=" ";//quantite
    date_intervention=QDate();
    IMG_Added="";

    }
interventions::interventions(int id_i,int id_a,int id_e, QString etat,QString rapport,QDate date,QString IMG)
{
    this->id_intervention=id_i;
    this->id_animal=id_a;
    this->id_employe=id_e;
    this->etat=etat;
    this->rapport_sante=rapport;
    this->date_intervention=date;
    this->IMG_Added=IMG;
}
interventions::interventions(int id_i,int id_a,int id_e, QString etat,QString rapport,QDate date)
{
    this->id_intervention=id_i;
    this->id_animal=id_a;
    this->id_employe=id_e;
    this->etat=etat;
    this->rapport_sante=rapport;
    this->date_intervention=date;
   // this->IMG_Added=IMG;
}
int interventions::getid_i(){return id_intervention;}
int interventions::getid_a(){return id_animal;}
int interventions::getid_e(){return id_employe;}
QString interventions::getetat(){return etat ;}
QString interventions::getrapport(){return rapport_sante;}
QDate interventions::getdate(){return date_intervention;}
QString interventions::getimage(){return IMG_Added;}

void interventions::setid_i(int id_i){this->id_intervention=id_i;}
void interventions::setid_a(int id_a){this->id_animal=id_a;}
void interventions::setid_e(int id_e){this->id_employe=id_e;}
void interventions::setetat(QString etat){this->etat=etat;}
void interventions::setrapport(QString rapport){this->rapport_sante=rapport;}
void interventions::setimage(QString IMG){this->IMG_Added=IMG;}
void interventions::setdate(QDate date){this->date_intervention=date;}
bool interventions::add()
{
    QString id_i=QString::number(id_intervention);
    QString id_a=QString::number(id_animal);
    QString id_e=QString::number(id_employe);
    QSqlQuery query;
          query.prepare("INSERT INTO INTERVENTION (ID_INTERVENTION, ETAT , RAPPORT_SANTE, DATE_INTERVENTION,ID_ANIMAL,ID_EMPLOYE) "
                        "VALUES (:id_i, :etat, :rapport, :date, :id_a, :id_e, :IMG_Added)");
          query.bindValue(0, id_i);
          query.bindValue(1, etat);
          query.bindValue(2, rapport_sante);
          query.bindValue(3, date_intervention);

          query.bindValue(4, id_a);
          query.bindValue(5, id_e);
          query.bindValue(6, id_e);
          query.bindValue(7, IMG_Added);

          return  query.exec();

}

QSqlQueryModel* interventions::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM INTERVENTION");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_INTERVENTION"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("RAPPORT_SANTE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_INTERVENTION"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_ANIMAL"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));

    return model;
}
bool interventions::supprimer(int id_intervention)
{
    QSqlQuery query;
          query.prepare("delete from INTERVENTION where id_intervention=:id_intervention ");
          query.bindValue(0, id_intervention);
          return query.exec();
}
bool interventions::modifier()
{
    QSqlQuery query;
          query.prepare("UPDATE INTERVENTION set etat=:etat,rapprot_sante=:rapprot_sante,date_intervention=:date_intervention,id_employe=:id_employe,id_employe=:id_employe where id_intervention=:id_intervention");
          query.bindValue(":id_intervention",id_intervention);
          query.bindValue(":etat",etat);
          query.bindValue(":rapprot_sante",rapport_sante);
          query.bindValue(":date_intervention",date_intervention);
          query.bindValue(":id_animal",id_animal);
          query.bindValue(":id_employe",id_employe);
          query.bindValue(":IMG_ADDED",IMG_Added);
          return query.exec();
}
QSqlQueryModel * interventions::trie_idi()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM INTERVENTION ORDER BY id_intervention ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_intervention"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("etat"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("rapprot_sante"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_intervention"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_animal"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));
    return model;
}
QSqlQueryModel * interventions::trie_ida()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM INTERVENTION ORDER BY id_animal ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_intervention"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("rapprot_sante"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_intervention"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_animal"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));
    return model;
}
QSqlQueryModel * interventions::trie_DATE()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM INTERVENTION ORDER BY date_intervention ");

          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_intervention"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("etat"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("rapprot_sante"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_intervention"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_animal"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));
    return model;
}
bool interventions::rechide(int x){
    QSqlQuery query;
    query.prepare("select * from INTERVENTION where id_employe = :id_employe;");
    query.bindValue(":id_employe", x);
    return query.exec();
}

QSqlQueryModel* interventions::rechercher_ide(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from INTERVENTION where id_employe ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_intervention"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("rapprot_sante"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_intervention"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_animal"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));

            return model;
    }

bool interventions::rechidi(int x){
    QSqlQuery query;
    query.prepare("select * from INTERVENTION where  id_intervention = :id_intervention");
    query.bindValue(":id_intervention", x);
    return query.exec();}

QSqlQueryModel* interventions::rechercher_idi(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from INTERVENTION where id_intervention ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_intervention"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("rapprot_sante"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_intervention"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_animal"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));
            return model;
    }
bool interventions::rechida(QString x){
    QSqlQuery query;
    query.prepare("select * from INTERVENTION where id_animal= :animal;");
    query.bindValue(":id_intervention", x);
    return query.exec();
}
QSqlQueryModel* interventions::rechercher_ida(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from INTERVENTION where id_animal ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_intervention"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("rapprot_sante"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_animal"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMG_ADDED"));
            return model;
    }

