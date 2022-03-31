#include "connection.h"

Connection::Connection()
{

}

bool Connection::CreateConnection()
{bool test=false;

 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("petos");
db.setUserName("chirine");//inserer nom de l'utilisateur
db.setPassword("esprit");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::CloseConnection(){db.close();}
