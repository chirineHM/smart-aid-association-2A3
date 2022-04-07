#ifndef PROFILS_H
#define PROFILS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class profils
{
public:
    profils();
    profils(int,int,QString);
    profils(int,QString);


    bool ajouter();
    bool supprimer(int);

    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboevent();
    QSqlQuery request(QString);
    bool modifier(QString,QString,QString);

    QSqlQuery login(QString,QString);

private:
    int id;
    int cin;
    QString password;

};

#endif // PROFILS_H
