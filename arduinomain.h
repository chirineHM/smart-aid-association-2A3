#ifndef ARDUINOMAIN_H
#define ARDUINOMAIN_H

#include <QDialog>

namespace Ui {
class arduinomain;
}

class arduinomain : public QDialog
{
    Q_OBJECT

public:
    explicit arduinomain(QWidget *parent = nullptr);
    ~arduinomain();

private:
    Ui::arduinomain *ui;
};

#endif // ARDUINOMAIN_H
