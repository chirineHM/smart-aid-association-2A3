#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QString>

class evenement
{
public:
    evenement();
    evenement(int,int,QString,QString,QString,QString,int);
   int getnum();
   int getnmbp();
   QString getnom();
   QString getlieu();
   QString getdescp();
   QString getdate();
    void setnum(int);
   void setnmbp(int);
   void setnom(QString);
   void setlieu(QString);
   void setdescp(QString);
   void setdate(QString);

   bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
   bool modifier(int num,int nmbp,QString date_ev,QString descp,QString lieu,QString nom);
   QSqlQueryModel* afficher_num();
   QSqlQueryModel* tri_num();
   QSqlQueryModel* tri_nom();
   QSqlQueryModel* tri_date();
   QSqlQueryModel* tri_nbrp();
   QSqlQueryModel *recherche_nom(QString nom);
   QSqlQueryModel *recherche(int num);
   QSqlQueryModel *recherche_date(QString d);
   evenement PDF();



private:
    int num , nmbp,idemp;
    QString nom, lieu, descp,date_ev;




};


#endif // EVENEMENT_H
