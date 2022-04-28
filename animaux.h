#ifndef ANIMAL_H
#define ANIMAL_H
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QSqlQueryModel>
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
    //bool modifier();
    //bool modifier2();
  //void modifierF();
  bool modifier();
  QSqlQueryModel* remplircomboAnimal();

      QSqlQuery request(QString);




  QSqlQueryModel* rechercher_identifiant(int  identifiant);
  QSqlQueryModel *tri();
  QSqlQueryModel *tri1();
  QSqlQueryModel *tri2();



};


#endif // ANIMAL_H
