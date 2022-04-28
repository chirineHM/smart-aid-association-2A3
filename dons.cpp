#include "dons.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
dons::dons()
{
    id_don=0;
    id_donneur=0;
    id_employe=0;
    type_don="";
    quantite_don=" ";
    date_don=QDate();

    }

/*Distance::Distance(float dis)
{
    this->distance=dis;

}*/
//float Distance::getdis(){return distance;}
//void Distance::setdis(float dis){this->distance=dis;}

dons::dons(int id,int id_d,int id_e, QString type,QString quant,QDate date)
{
    this->id_don=id;
    this->id_donneur=id_d;
    this->id_employe=id_e;
    this->type_don=type;
    this->quantite_don=quant;
    this->date_don=date;
}
int dons::getid(){return id_don;}
int dons::getid_d(){return id_donneur;}
int dons::getid_e(){return id_employe;}
QString dons::gettype(){return type_don;}
QString dons::getquant(){return quantite_don;}
QDate dons::getdate(){return date_don;}
void dons::setid(int id){this->id_don=id;}
void dons::setid_d(int id_d){this->id_donneur=id_d;}
void dons::setid_e(int id_e){this->id_employe=id_e;}
void dons::settype(QString type){this->type_don=type;}
void dons::setquant(QString quant){this->quantite_don=quant;}
void dons::setdate(QDate date){this->date_don=date;}
bool dons::add()
{
    QString id_d=QString::number(id_don);
    QString id_do=QString::number(id_donneur);
    QString id_em=QString::number(id_employe);
    QSqlQuery query;
          query.prepare("INSERT INTO Dons (id_don, type_don , quantite_don, date_don,id_donneur,id_employe) "
                        "VALUES (:id, :type, :quant, :date, :id_d, :id_e)");
          query.bindValue(0, id_d);
          query.bindValue(1, type_don);
          query.bindValue(2, quantite_don);
          query.bindValue(3, date_don);
          query.bindValue(4, id_do);
          query.bindValue(5, id_em);
          return  query.exec();

}

QSqlQueryModel* dons::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM Dons");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_don"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_don"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite_don"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_donneur"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
    return model;
}
bool dons::supprimer(int id_don)
{
    QSqlQuery query;
          query.prepare("delete from dons where id_don=:id_don ");
          query.bindValue(0, id_don);
          return query.exec();
}
bool dons::modifier()
{
    QSqlQuery query;
          query.prepare("UPDATE dons set type_don=:type_don,quantite_don=:quantite_don,date_don=:date_don,id_donneur=:id_donneur,id_employe=:id_employe where id_don=:id_don");
          query.bindValue(":id_don",id_don);
          query.bindValue(":type_don",type_don);
          query.bindValue(":quantite_don",quantite_don);
          query.bindValue(":date_don",date_don);
          query.bindValue(":id_donneur",id_donneur);
          query.bindValue(":id_employe",id_employe);
          return query.exec();
}
QSqlQueryModel * dons::trie_TYPE()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM dons ORDER BY id_don ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_don"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_don"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantite_don"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_don"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_donneur"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
    return model;
}
QSqlQueryModel * dons::trie_QUANTITE()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM dons ORDER BY quantite_don ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_don"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_don"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantite_don"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_don"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_donneur"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
    return model;
}
QSqlQueryModel * dons::trie_DATE()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM dons ORDER BY date_don ");

          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_don"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_don"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantite_don"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_don"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("id_donneur"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
    return model;
}
bool dons::rech(int x){
    QSqlQuery query;
    query.prepare("select * from dons where id_don = :id_don;");
    query.bindValue(":id_don", x);
    return query.exec();
}

QSqlQueryModel* dons::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from dons where id_don ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_don"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_don"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite_don"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_donneur"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));

            return model;
    }

bool dons::rechtype(QString x){
    QSqlQuery query;
    query.prepare("select * from dons where  type_don = :type_don");
    query.bindValue(":type_don", x);
    return query.exec();}

QSqlQueryModel* dons::recherchertype(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from dons where type_don ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_don"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_don"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite_don"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_donneur"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
            return model;
    }
bool dons::rechquantite(QString x){
    QSqlQuery query;
    query.prepare("select * from dons where quantite_don= :quantite_don;");
    query.bindValue(":quantite_don", x);
    return query.exec();
}
QSqlQueryModel* dons::rechercherquantite(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from dons where quantite_don ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_don"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_don"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite_don"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_donneur"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_employe"));
            return model;
    }
void dons::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
 QSqlQuery query,query1;

    query.prepare("SELECT quantite_don FROM dons where quantite_don between  0 and 20");////////////////
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }
    query.prepare("SELECT quantite_don FROM dons where quantite_don between 20 and 35");/////////////////
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    query.prepare("SELECT quantite_don FROM dons where quantite_don between 35 and 50");///////////////
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }





    *ticks << 1 << 2 << 3  ;
    *labels << "[0,20]" << "[20,35]" << "[35,50]" ;///////////////////////////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(*ticks, *labels);
}


