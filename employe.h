#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>


class Employe
{

    int id_emp;
    int tel_emp;
    QString nom_emp;
    QString prenom_emp;
    QString adresse_emp;
    QString date_naiss_emp;
    QString sexe_emp;
    QString email;

public:
    Employe();
    Employe(int,int,QString,QString,QString,QString,QString,QString);
    int getid_emp();
    int gettel_emp();
    QString getnom_emp();
    QString getprenom_emp();
    QString getadresse_emp();
    QString getdate_naiss_emp();
    QString getsexe_emp();
    QString getemail();

    void setid_emp(int);
    void settel_emp(int);
    void setnom_emp(QString);
    void setprenom_emp(QString);
    void setadresse_emp(QString);
    void setdate_naiss_emp(QString);
   void setsexe_emp(QString);
   void setemail(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel*  afficher_id();
    QSqlQueryModel*  tri();
    QSqlQueryModel*  tri1();
    QSqlQueryModel*  tri2();
    QSqlQueryModel* remplircomboEmploye();
    QSqlQuery request(QString);

    QSqlQuery verif(QString);

};

#endif // EMPLOYE_H
