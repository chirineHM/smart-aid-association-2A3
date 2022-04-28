#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "employe.h"
#include "profils.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_seconnecter_clicked();

    void on_sinscrire_clicked();

private:
    Ui::Login *ui;

    profils p;
    Employe emp;
};

#endif // LOGIN_H
