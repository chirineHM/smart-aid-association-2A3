#include "profils.h"

profils::profils()
{
}

profils::profils(int id,int cin,QString password)
{
    this->id=id;
    this->cin=cin;
    this->password=password;
}

profils::profils(int cin,QString password)
{
    this->cin=cin;
    this->password=password;
}



//*******AJOUTER

bool profils::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO profil (cin, PASSWORD ) "
                    "VALUES (:cin, :password)");


query.bindValue(":cin", cin);
query.bindValue(":password", password);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * profils::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from profil");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Password"));


    return model;
}

//*******SUPPRIMPER

bool profils::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from profil where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool profils::modifier(QString cin, QString password,QString id)
{
QSqlQuery query;

query.prepare("UPDATE profil SET cin= :cin, password= :password "
                    " WHERE  ID = :id ");


query.bindValue(":cin", cin);
query.bindValue(":password", password);
query.bindValue(":id", id);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * profils::remplircomboevent()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from profil");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery profils::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from profil where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}


QSqlQuery profils::login(QString cin,QString mdp)
{
    QSqlQuery query;
    query.prepare("select * from profil where cin= '"+cin+"' and password='"+mdp+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}
