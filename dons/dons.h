#ifndef ANIMAUX_H
#define ANIMAUX_H
#include <QString>
#include <QDate>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>


class Dons
{

    int Id_don,id_donneur,id_employe;
    QString type_don	;
    QString quantite_don	;
    QString date_don	;

public:
    Dons();
    Dons(int,int,int,QString,QString,QString);
    int getid();
    int getid_d();
    int getid_e();
    QString gettype();
    QString getquantite();
    QString getdate();

    void setid(int);
    void setid_d(int);
    void setid_e(int);
    void settype(QString);
    void setquantite(QString);
    void setdate(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);


};

#endif // ANIMAUX_H
