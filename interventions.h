#ifndef INTERVENTIONS_H
#define INTERVENTIONS_H
#include<QString>
#include <QDate>
#include<QSqlQueryModel>
#include <qcustomplot.h>
class interventions
{
public:
    interventions();
    interventions(int,int,int,QString,QString,QDate);
    interventions(int,int,int,QString,QString,QDate,QString);
    int getid_i();
    int getid_e();
    int getid_a();
    QDate getdate();
    QString getetat();
    QString getrapport();
     QString getimage();

    void setid_i(int);
    void setid_e(int);
    void setid_a(int);
    void setetat(QString);
    void setrapport(QString);
    void setdate(QDate);
    void setimage(QString);
    bool add();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trie_idi();
    QSqlQueryModel * trie_ida();
    QSqlQueryModel * trie_DATE();
    //QSqlQueryModel* afficher1();
    bool rechide(int);
    QSqlQueryModel* rechercher_ide(QString);
    bool rechidi(int);
    QSqlQueryModel* rechercher_idi(QString);
    bool rechida(QString);
    QSqlQueryModel* rechercher_ida(QString);
  void statistique(QVector<double>* ticks,QVector<QString> *labels);
  interventions PDF();

private:
    int id_intervention;
    int id_employe;
    int id_animal;
    QString etat;
    QString rapport_sante;
    QString IMG_Added;
    QDate date_intervention;

};

#endif // INTERVENTIONS_H
