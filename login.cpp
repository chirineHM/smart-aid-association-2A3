#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "gestion_employe.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->label_msg->setText("");
}

Login::~Login()
{
    delete ui;
}

void Login::on_seconnecter_clicked()
{
    QSqlQuery query;

    QString nomutil = ui->cin->text();
    QString mdp = ui->password->text();

    if(nomutil == "admin" && mdp == "admin")
    {
        Login::close();
        Gestion_Employe *m = new Gestion_Employe();
        m->show();
    }
    else
    {
        query =p.login(nomutil,mdp);
        if(query.exec())
        {
            if(query.next())
            {
                Login::close();
                MainWindow *m = new MainWindow();
                m->show();

            }
            else
            {
                ui->label_msg->setText("Nom utilisateur ou mdp incorrect.");
            }
        }
    }
}

void Login::on_sinscrire_clicked()
{

    if((ui->cin->text() != "") &&(ui->password->text() != ""))
    {
    QSqlQuery query;

    query =emp.verif(ui->cin->text());
    if(query.exec())
    {
        if(query.next())
        {
            profils p1(ui->cin->text().toUInt(),ui->password->text());

            bool test=p1.ajouter();
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Inscription effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("Inscription effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        {
            ui->label_msg->setText("Utilisateur incorrect.");
        }
    }
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("CHAMP VIDE"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}
