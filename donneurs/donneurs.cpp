#include "donneurs.h"
#include "ui_donneurs.h"
#include "donneur.h"
#include <QMessageBox>

donneurs::donneurs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::donneurs)
{
    ui->setupUi(this);
    ui->tableView->setModel (don.afficher());

}

donneurs::~donneurs()
{
    delete ui;
}




void donneurs::on_pushButton_5_clicked()
{
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QDate date=ui->date->date();

    int tel=ui->tel->text().toInt();
    QString adresse=ui->adresse->text();
    int id=ui->id->text().toInt();

     donneur d (id,nom,prenom,tel,adresse,date);

     bool test=d.ajouter() ;

     if(test)
     {
ui->tableView->setModel(d.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                  "click Cance to exit."), QMessageBox::Cancel);
     }


     else

         QMessageBox::critical (nullptr, QObject::tr("Not OK"),
                     QObject::tr("Ajout non effectué.\n to exit.click Cancel"),QMessageBox::Cancel);

}


//modifier
void donneurs::on_pushButton_6_clicked()
{
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QDate date=ui->date->date();

    int tel=ui->tel->text().toInt();
    QString adresse=ui->adresse->text();
    int id=ui->id->text().toInt();

     donneur d (id,nom,prenom,tel,adresse,date);

        bool    test1=d.modifier(id,nom,prenom,tel,adresse,date);

 //si id existe on modifie sinon msg erreur

        if (test1)
              {
            ui->tableView->setModel(don.afficher());

                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}
}
/*
//supprimer
void materiaux::on_pushButton_10_clicked()
{
    materiel m1; m1.setid(ui->idsup->text().toInt());
    bool test=m1.supprimer(m1.getid());
    QMessageBox msgBox;
    if(test)
    {
        ui->tableView->setModel(mat.afficher());
        msgBox.setText("suppression avec succes.");
    }
    else
          msgBox.setText("echec d'ajout");
                msgBox.exec();

}
*/
void donneurs::on_tableView_activated(const QModelIndex &index)
{

    selected=ui->tableView->model()->data(index).toString();
    qDebug()<< selected;

    int id=ui->tableView->model()->data(index).toInt();

    QSqlQuery query;
    query.prepare("select * from DONNEURS where ID_DONNEUR =:id");
    query.bindValue(":id",id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->id4->setText(query.value(0).toString());
            ui->nom4->setText(query.value(1).toString());
            ui->pre4->setText(query.value(2).toString());
            ui->date4->setDate(query.value(3).toDate());
            ui->tel4->setText(query.value(4).toString());
            ui->adr4->setText(query.value(5).toString());

        }
    }
}





void donneurs::on_recherche_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
      QSqlQuery   *query= new QSqlQuery();
      query->prepare("SELECT * FROM DONNEURS WHERE ID_DONNEUR LIKE '"+arg1+"%' or NOM LIKE '"+arg1+"%' or PRENOM LIKE '"+arg1+"%' or TEL LIKE '"+arg1+"%' or ADRESSE LIKE '"+arg1+"%'");
       query->exec();
       if (query->next()) {
       model->setQuery(*query);
       ui->tableView->setModel(model);
       }
       else {
           QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                           QObject::tr("Aucun résultat trouvé !.\n"
                                       "Cliquez sur OK pour quitter."), QMessageBox::Ok);
           ui->recherche->clear();}
}


void donneurs::on_checkBox_4_clicked()
{
    ui->tableView->setModel(don.tri_nom());

}




void donneurs::on_pushButton_clicked()
{
    if(selected!="")
    {
        bool test=don.supprimer(selected);
        if(test)
        {
            ui->tableView->setModel(don.afficher());
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("Supprimé avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
            selected="";
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : La suppression a échoué. sélectionnez l'identifiant ou Cin Or (aucune colonne n'est sélectionnée ou la ligne n'existe pas)\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
            selected="";
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Sélectionner"),
                    QObject::tr("Veuillez sélectionner l'Id ou le Cin du client (Double clic).\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
}


void donneurs::on_pushButton_9_clicked()
{
    donneur d;
    QString nom=ui->nom4->text();
    QString prenom=ui->pre4->text();
    QDate date=ui->date4->date();

    int tel=ui->tel->text().toInt();
    QString adresse=ui->adr4->text();
    int id=ui->id4->text().toInt();



        bool test=don.modifier(id,nom,prenom,tel,adresse,date);
        if(test)
        {
            ui->tableView->setModel(don.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);

        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification non effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);
        }
}

