#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
evenement::evenement()
{
num=0 ; nmbp=0; date_ev="QString" ; nom="  " ; lieu= " "; descp=" ";}

evenement::evenement(int num,int nmbp,QString nom,QString lieu,QString descp,QString date_ev)
{this->num=num; this->nom=nom;this->nmbp=nmbp;this->lieu=lieu;this->descp=descp;this->date_ev=date_ev;}

int evenement::getnum(){return num;}
int evenement :: getnmbp(){return nmbp;}
QString evenement::getnom(){return nom;}
QString evenement:: getlieu(){return lieu;}
QString evenement:: getdescp(){return descp;}
QString evenement :: getdate(){return date_ev;}


void evenement::setnum(int num){this->num=num;}
void evenement:: setnmbp(int nmbp){this->nmbp=nmbp;}
void evenement:: setnom(QString nom) {this->nom=nom;}
void evenement:: setlieu(QString lieu){this->lieu=lieu;}
void evenement::setdescp(QString descp){this->descp=descp;}
void evenement::setdate(QString date_ev){this->date_ev=date_ev;}

bool evenement::ajouter()
{

    QString num_string=QString::number(num);
    QString NMBP_string=QString::number(nmbp);
    //QString ID_EMP_string=QString::number(ID_EMP);
    QSqlQuery query;


          query.prepare("INSERT INTO EVENEMENTS (date_ev,descp,lieu,nmbp,nom,num) "
                        "VALUES (:date_ev,:descp,:lieu,:nmbp,:nom,:num)");
          query.bindValue(":date_ev", date_ev);
          query.bindValue(":descp", descp);

          query.bindValue(":lieu", lieu);
          query.bindValue(":nmbp", NMBP_string);
          query.bindValue(":nom", nom);
          query.bindValue(":num", num_string);






         return query.exec();



}
bool evenement::supprimer(int num)
{ QSqlQuery query;

        query.prepare("Delete from evenements where num=:num");
          query.bindValue(0, num );

         return query.exec();

}
QSqlQueryModel* evenement::afficher()
{
    QSqlQueryModel*  model=new QSqlQueryModel();


    model->setQuery("select * FROM evenements");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));



    return model;


}
bool evenement::modifier()
    {
        QSqlQuery query;
            query.prepare("UPDATE EVENEMENTS SET date_ev=:date_ev, descp=:descp, lieu=:lieu, nmbp=:nmbp,nom=:nom, num=:num WHERE num=:num ");
            query.bindValue(":date_ev", date_ev);
            query.bindValue(":descp", descp);
            query.bindValue(":lieu", lieu);
            query.bindValue(":nmbp", nmbp);
            query.bindValue(":nom", nom);
            query.bindValue(":num", num);
             return query.exec();

    }
QSqlQueryModel*  evenement ::afficher_num()
{
    QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select num from EVENEMENTS");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
return model;
}

QSqlQueryModel * evenement::tri_num()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EVENEMENTS order by NUM");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));
    return model;
}

QSqlQueryModel * evenement::tri_nom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EVENEMENTS order by NOM");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));
    return model;
}

QSqlQueryModel * evenement::tri_date()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EVENEMENTS order by DATE_EV");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));
    return model;
}

QSqlQueryModel * evenement::tri_nbrp()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EVENEMENTS order by NMBP");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));
    return model;
}

QSqlQueryModel * evenement::recherche(int num)
{
    QString res=QString::number(num);
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * from EVENEMENTS where NUM like '"+res+"%';");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));

 return model;
}

QSqlQueryModel * evenement::recherche_nom(QString nom)
{
    QString res=nom;
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * from EVENEMENTS where NOM like '"+res+"%';");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));

 return model;
}

QSqlQueryModel * evenement::recherche_date(QString d)
{
    QString res=nom;
    QSqlQueryModel * model =new QSqlQueryModel();
     model->setQuery("SELECT * from EVENEMENTS where DATE_EV like '"+d+"%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("num"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_ev"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("nmbp"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("descp"));
     return model;
}
