#include "arduinomain.h"
#include "ui_arduinomain.h"

arduinomain::arduinomain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arduinomain)
{
    ui->setupUi(this);
}

arduinomain::~arduinomain()
{
    delete ui;
}
