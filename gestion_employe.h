#ifndef GESTION_EMPLOYE_H
#define GESTION_EMPLOYE_H

#include <QMainWindow>
#include "employe.h"
#include "profils.h"
#include "rfid.h"

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

    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_load_list_clicked();
    void on_modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_PDF_clicked();
    void on_pb_chercher_clicked();
    void on_pb_chercher_1_clicked();
    void on_pb_chercher_2_clicked();
    void on_pb_trier_clicked();
    void on_pb_trier_1_clicked();
    void on_pb_trier_2_clicked();
    void on_comboBoxModif_currentIndexChanged(const QString &arg1);
    void on_ModifierBouton_clicked();


    void on_supprimer2_clicked();

    void on_load_listProfil_clicked();

    void on_deconnexion_clicked();
    void on_pushButton_24_clicked();
    void update_label_uid();


private:
    Ui::Gestion_Employe *ui;
    Employe E;
    Employe E2;
    profils p;
    QString data;
    Arduino A;
    QString uid;

};





#endif // GESTION_EMPLOYE_H
