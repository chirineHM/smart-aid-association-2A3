#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnect()
{
 db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("test-bd");//inserer le nom de la source de donnÃ©es ODBC
db.setUserName("sarra");//inserer nom de l'utilisateur
db.setPassword("manager");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
