#include "connection.h"

Connection::Connection()
{}

bool Connection::ouvrirConnexion()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Pet.O.S");
    db.setUserName("sarra");//inserer nom de l'utilisateur
    db.setPassword("manager");//inserer mot de passe de cet utilisateur
if (db.open())
    test=true;
return  test;
}
QSqlDatabase Connection::getdb()
{
    return db;
}

void Connection::fermerConnexion()
{db.close();}
