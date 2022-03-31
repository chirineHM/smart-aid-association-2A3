#ifndef MATERIEL_H
#define MATERIEL_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QDate>
class donneur
{
    QString nom, prenom,adresse;
    QDate date;

    int id,tel;
public:
    donneur(){}
    donneur(int,QString,QString,int,QString,QDate);
    //getters

        int gettel();
        int getid();
        QString getnom();
        QString getprenom();
        QString getAdresse();
        QDate getDate();
        //setters

          void settel(int);
          void setid(int);
          void setnom(QString);
          void setprenom(QString);
          void setAdresse(QString);
          void setDate(QDate);



          bool ajouter();

           QSqlQueryModel * afficher();

        bool modifier(int id ,QString nom ,QString prenom ,int tel, QString adresse,QDate date);
  bool supprimer(QString source);
  QSqlQuery * search_data(QString source);
  QSqlQueryModel *tri_nom();

};

#endif // MATERIEL_H
