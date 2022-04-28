#ifndef STOCK_H
#define STOCK_H

#include<QString>
#include <QDate>
#include<QSqlQueryModel>
#include <qcustomplot.h>
class dons
{
public:
    dons();
    dons(int,int,int,QString,QString,QDate);

    int getid();
    int getid_e();
    int getid_d();
    QDate getdate();
    QString gettype();
    QString getquant();
    void setid(int);
    void setid_e(int);
    void setid_d(int);
    void settype(QString);
    void setquant(QString);
    void setdate(QDate);
    bool add();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trie_TYPE();
    QSqlQueryModel * trie_QUANTITE();
    QSqlQueryModel * trie_DATE();
    //QSqlQueryModel* afficher1();
    bool rech(int);
    QSqlQueryModel* rechercher(QString);
    bool rechtype(QString);
    QSqlQueryModel* recherchertype(QString);
    bool rechquantite(QString);
    QSqlQueryModel* rechercherquantite(QString);
  void statistique(QVector<double>* ticks,QVector<QString> *labels);
  dons PDF();

private:
    int id_don;
    int id_employe;
    int id_donneur;
    QString type_don;
    QString quantite_don;
    QDate date_don;
};

#endif // STOCK_H
