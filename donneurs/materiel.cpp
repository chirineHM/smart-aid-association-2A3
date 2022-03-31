#include "materiel.h"
#include <QDate>

donneur::donneur(int id,QString nom,QString prenom,int tel,QString adresse,QDate date)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->adresse=adresse;
    this->date=date;

}

int donneur::gettel(){return tel;}
QString donneur::getnom(){return nom;}
QString donneur::getprenom(){return prenom;}
int donneur::getid(){return id;}

QString donneur::getAdresse(){return adresse;}
QDate donneur::getDate(){return date;}



void donneur::settel(int tel){this->tel=tel  ;}
void donneur::setnom(QString nom){this->nom=nom;}
void donneur::setid(int id){this->id=id  ;}
void donneur::setprenom(QString prenom){this->prenom=prenom   ;}
void donneur::setAdresse(QString adresse){this->adresse=adresse   ;}
void donneur::setDate(QDate date){this->date=date   ;}





bool donneur::ajouter()
{
    QSqlQuery query;
    QString res =QString::number(id);
    QString te =QString::number(tel);


          query.prepare("INSERT INTO DONNEURS(ID_DONNEUR,NOM,PRENOM,TEL,ADRESSE,DATE_NAISSANCE) "
                        "VALUES (:id,:nom, :prenom,:tel,:adresse,:date)");

           query.bindValue(":id",res);
          query.bindValue(":nom" , nom);
          query.bindValue(":prenom",prenom);
          query.bindValue(":tel", te);
          query.bindValue(":adresse",adresse);
          query.bindValue(":date",date);


    return query.exec();
}

QSqlQuery * donneur::search_data(QString source)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select * from DONNEURS where ID_DONNEUR='"+source+"");
    model->exec();
  return model;
}
bool donneur::supprimer(QString source)
{
     QSqlQuery query;
     query.prepare("DELETE from DONNEURS where ID_DONNEUR= :id ");
     query.bindValue(":id",source);
     return query.exec();
}



QSqlQueryModel * donneur::afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from DONNEURS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date"));

        return model;
}

bool donneur::modifier(int id ,QString nom , QString prenom,int tel,QString adresse ,QDate date )
{
    QSqlQuery query;

    query.prepare("UPDATE DONNEURS SET NOM= :nom, PRENOM= :prenom , TEL= :tel,ADRESSE= :adresse,DATE_NAISSANCE= :date where ID_DONNEUR = :id ");

    query.bindValue(":id", id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":tel",tel);
        query.bindValue(":adresse", adresse);
        query.bindValue(":date",date);


            return    query.exec();
}


QSqlQueryModel *donneur::tri_nom(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from DONNEURS order by NOM asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DONNEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE"));


    return model;
}
