#ifndef GESTION_EMPLOYE_H
#define GESTION_EMPLOYE_H
#include <QMainWindow>
#include "QDate"
#include "QtDebug"
#include "connection.h"
#include <QMessageBox>
#include <QPixmap>
#include<QSystemTrayIcon>
#include <QApplication>
#include<QSystemTrayIcon>
#include <QApplication>
#include <QModelIndex>
#include <QItemDelegate>
#include <QSize>
#include <QSpinBox>
#include <iostream>
#include <QDesktopServices>
#include <QIntValidator>
#include <QtGui>
#include "QString"
#include<QUrl>
#include <QPainter>
#include <QRectF>
#include <QStaticText>
#include"evenement.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include "employe.h"
#include "animaux.h"
#include "profils.h"
#include "arduino.h"
#include "evenement.h"
#include "smtp.h"
#include "dons.h"
#include "popup.h"
#include "qcustomplot.h"
#include "dons.h"
#include "popup.h"
#include "arduino.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QMainWindow>
#include <QTableWidget>
#include<QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class Gestion_Employe;

}

class Gestion_Employe : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gestion_Employe(QWidget *parent = nullptr);
    ~Gestion_Employe();
private slots:
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino
      void update_lcd(const QString Distance);
     //void update_lcd(const QString Humidity,const QString temp,const QString heat);

    void on_ajouter_clicked();
    void on_supprimerE_clicked();
    void on_load_list_clicked();
    void on_modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_PDF_clicked();
    void on_pb_chercherr_clicked();
    void on_pb_chercherr_1_clicked();
    void on_pb_chercherr_2_clicked();
    void on_pb_trierr_clicked();
    void on_pb_trierr_1_clicked();
    void on_pb_trierr_2_clicked();
    void on_comboBoxModif_currentIndexChanged(const QString &arg1);
    void on_ModifierBouton_clicked();


    void on_supprimer2_clicked();

    void on_load_listProfil_clicked();

    void on_deconnexion_clicked();
    void on_pushButton_28_clicked();
    void update_label_uid();
  // void sendMail();
   //void mailSent(QString status);
    //void on_pushButton_clicked();

    void on_ajouter_3_clicked();

    void on_deconnexion_2_clicked();

    void on_deconnexion_3_clicked();

    /********************** SARRA : GESTION ANIMAUX ********************************/
    void on_pushButton_2_clicked();

    void on_tabWidget_currentChanged(int index);
    void on_supp_clicked();
    void on_load_list_2_clicked();
    void on_pb_modifier_clicked();
    //void on_pb_ok_clicked();
    void on_pb_pdf_clicked();
     void on_pb_chercher_00_clicked();
     void on_pb_chercher_11_clicked();
     void on_pb_chercher_22_clicked();
     void on_pb_trier_00_clicked();
     void on_pb_trier_11_clicked();
     void on_pb_trier_22_clicked();
     void on_pb_excel_clicked();

   // void on_pushButton_2_clicked();


     void on_comboBoxModif_2_currentIndexChanged(const QString &arg1);
     void on_ModifierBouton_2_clicked();



     void on_pb_clicked();

     void on_pb_supprimer_clicked();

     void on_tab_evenement_activated(const QModelIndex &index);

     void on_load_list_3_clicked();

     void on_pushButton_3_clicked();

     void on_pushButton_4_clicked();

     void on_pushButton_5_clicked();

     void on_pushButton_6_clicked();

     void on_pushButton_7_clicked();

     void on_calendarWidget_clicked(const QDate &date);

     void on_envoyer_clicked();

     void on_lineEdit_textChanged(const QString &arg1);

     void on_pb_2_clicked();

     void update_label_51();

     void on_pushButton_8_clicked();

     void on_deconnexion_4_clicked();

     void on_pushButton_20_clicked();

     void on_supp_2_clicked();

     void on_ModifierBouton_3_clicked();

     void on_pushButton_21_clicked();

     void on_pushButton_22_clicked();

     void on_tabWidget_8_currentChanged(int index);

     void on_pb_chercher_1_clicked();

     void on_comboBox_3_activated(const QString &arg1);

     void on_pushButton_23_clicked();

     void on_ModifierBouton_4_clicked();

     void on_pushButton_26_clicked();

     void on_pb_pdfint_clicked();

     void on_pb_chercher_int_clicked();

     void on_comboBox_int2_activated(const QString &arg1);

     void on_tabWidget_9_currentChanged(int index);

     void on_tab_modif_2_activated(const QModelIndex &index);

     void on_supp_3_clicked();

     void on_tab_modif_activated(const QModelIndex &index);

     void on_deconnexion_5_clicked();

       bool insert_distance(float);
        QSqlQuery * search(QDateTime date_insert);
       QSqlQueryModel * afficher_distance();
       bool modifier_distance(QString id,float);
       QSqlQuery * search_newDistance(QString id_distance);

       void on_ajouter_4_clicked();

       void on_comboBoxModif_4_activated(const QString &arg1);

       void on_pushButton_clicked();

       void on_push_button4_clicked();

       void on_pushButton9_clicked();

       void on_pushButton_25_clicked();

private:
    Ui::Gestion_Employe *ui;
    Employe E;
    Employe E2;
    profils p;
    QString data;
    Arduino A;
    QString uid;
    evenement Ev;
    QByteArray set; // variable contenant les données reçues
    int i=0;
    Arduino As; // objet temporaire

    /********************** SARRA : GESTION ANIMAUX ********************************/

    Animaux An;
      Animaux tmpanimaux;
      dons d;
       PopUp *popUp;
       QByteArray data1;

       QString buffer; // tableau des valeur recçues
       int count;
      QString id_distance;
      QDateTime date_distance;
};




#endif // GESTION_EMPLOYE_H
