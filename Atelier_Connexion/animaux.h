#ifndef ANIMAUX_H
#define ANIMAUX_H
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>


class Animaux
{

    int ID_ANIMAL;
    QString ESPECE	;
    QString SEXE_ANIMAL	;
    QString RACE	;
    float AGE;
    float POIDS	;
    QString  DATE_ACCUEIL;
public:
    Animaux();
    Animaux(int,QString,QString,QString,float,float,QString);
    int getid();
    QString getespece();
    QString getsexe();
    QString geterace();
    float getage();
    float getpoids();
    QString getdate_acc();

    void setid(int);
    void setespece(QString);
    void setsexe(QString);
    void setrace(QString);
    void setage(float);
    void setpoids(float);
    void setdate_acc(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();


};

#endif // ANIMAUX_H
