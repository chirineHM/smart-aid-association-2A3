#include "employe.h"
#include"connection.h"
//#include "ui_employe.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QObject>


Employe::Employe()
{
  id_emp=0;tel_emp=0;nom_emp="";prenom_emp="";adresse_emp="";date_naiss_emp="";sexe_emp="";email="";
}
Employe::Employe(int id_emp,int tel_emp,QString nom_emp,QString prenom_emp,QString adresse_emp,QString date_naiss_emp,QString sexe_emp,QString email)
{
    this->id_emp=id_emp;
    this->tel_emp=tel_emp;
    this->nom_emp=nom_emp;
    this->prenom_emp=prenom_emp;
    this->adresse_emp=adresse_emp;
    this->date_naiss_emp=date_naiss_emp;
    this->sexe_emp=sexe_emp;
    this->email=email;
}
int Employe::getid_emp(){return id_emp;}
int Employe::gettel_emp(){return tel_emp;}
QString Employe::getnom_emp(){return nom_emp;}
QString Employe::getprenom_emp(){return prenom_emp;}
QString Employe::getadresse_emp(){return adresse_emp;}
QString Employe::getdate_naiss_emp(){return date_naiss_emp;}
QString Employe::getsexe_emp(){return sexe_emp;}
QString Employe::getemail(){return email;}

void Employe::setid_emp(int id_emp){this->id_emp=id_emp;}
void Employe::settel_emp(int tel_emp){this->tel_emp=tel_emp;}
void Employe::setnom_emp(QString nom_emp){this->nom_emp=nom_emp;}
void Employe::setprenom_emp(QString prenom_emp){this->prenom_emp=prenom_emp;}
void Employe::setadresse_emp(QString adresse_emp){this->adresse_emp=adresse_emp	;}
void Employe::setdate_naiss_emp(QString date_naiss_emp) {this->date_naiss_emp=date_naiss_emp;}
void Employe::setsexe_emp(QString sexe_emp){this->sexe_emp=sexe_emp;}
void Employe::setemail(QString email){this->email=email;}

bool Employe::ajouter()
{

    QString id_QString=QString::number(id_emp);
    QString tel_QString=QString::number(tel_emp);
        QSqlQuery query;
              query.prepare("INSERT INTO Employe (id_emp, nom_emp, prenom_emp, sexe_emp, adresse_emp, tel_emp, date_naiss_emp, email) "
                            "VALUES (:id_emp, :nom_emp, :prenom_emp, :sexe_emp, :adresse_emp, :tel_emp, :date_naiss_emp_emp, :email)");
              query.bindValue(0, id_QString);
              query.bindValue(1, nom_emp);
              query.bindValue(2, prenom_emp);
              query.bindValue(3, sexe_emp);
              query.bindValue(4, adresse_emp);
              query.bindValue(5, tel_QString);
              query.bindValue(6, date_naiss_emp);
              query.bindValue(7, email);


            return  query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT * FROM Employe");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant employé"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom employé"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prénom employé"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe employé"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse employé"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("tel employé"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("date naissance employé"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("email employé"));



        return model;

}
bool Employe::supprimer(int id_emp)
{
    QSqlQuery query;
          query.prepare(" Delete from Employe where id_emp=:id_emp");
          query.bindValue(0, id_emp);
        return  query.exec();


}
bool Employe::modifier()
    {

        QSqlQuery query;
            query.prepare("UPDATE Employe SET nom_emp= :nom_emp, prenom_emp= :prenom_emp, sexe_emp= :sexe_emp, adresse_emp= :adresse_emp, tel_emp= :tel_emp, date_naiss_emp= :date_naiss_emp, email= :email WHERE id_emp= :id_emp ");
            query.bindValue(":id_emp", id_emp);
            query.bindValue(":nom_emp", nom_emp);
            query.bindValue(":prenom_emp", prenom_emp);
            query.bindValue(":sexe_emp", sexe_emp);
            query.bindValue(":adresse_emp", adresse_emp);
            query.bindValue(":tel_emp", tel_emp);
            query.bindValue(":date_naiss_emp", date_naiss_emp);
            query.bindValue(":email", email);
             return query.exec();

    }
QSqlQueryModel*  Employe ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select id_emp from Employe");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_emp"));
return model;
}

QSqlQueryModel * Employe::tri(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM EMPLOYE ORDER BY NOM_EMP");
   q->exec();
   model->setQuery(*q);

   return model;
}
QSqlQueryModel * Employe::tri1(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM EMPLOYE ORDER BY PRENOM_EMP");
   q->exec();
   model->setQuery(*q);

   return model;
}
QSqlQueryModel * Employe::tri2(){

   QSqlQuery *q = new QSqlQuery();
   QSqlQueryModel *model = new QSqlQueryModel();
   q->prepare("SELECT * FROM Employe ORDER BY DATE_NAISS_EMP");
   q->exec();
   model->setQuery(*q);

   return model;
}

//******REMPLIR COMBO BOX

QSqlQueryModel * Employe::remplircomboEmploye()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select id_emp from Employe");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery Employe::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from Employe where id_emp= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

QSqlQuery Employe::verif(QString cin)
{
    QSqlQuery query;
    query.prepare("select * from Employe where id_emp= '"+cin+"'");
    query.addBindValue(cin);
    query.exec();
    return query;
}

