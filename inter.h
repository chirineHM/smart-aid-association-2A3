#ifndef INTERVENTION_H
#define INTERVENTION_H
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>


class intervention
{


    int ID_intervention;
    int ID_ANIMAL;
    int ID_veterinaire	;
    QString Etat_castration	;
    QString Etat_vaccin	;
    QString Rapport_sante	;
    QString  DATE_intervention;
public:
    intervention();
    intervention(int,int,int,QString,QString,QString,QString);
    int getidi();
    int getida();
    int getidv();
    QString getev();
    QString getec();
    QString getrapport();
    QString getdate_inter();

    void setidi(int);
    void setida(int);
    void setidv(int);
    void setev(QString);
    void setec(QString);
    void setrapport(QString);
    void setdate_inter(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();


};

#endif
