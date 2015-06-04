#ifndef EVENEMENTINFODIALOG_H
#define EVENEMENTINFODIALOG_H

#include <QDialog>
#include "evenement1j.h"
namespace Ui {
class EvenementInfoDialog;
}

class EvenementInfoDialog : public QDialog
{
    Q_OBJECT
    Evenement *evt;
public:
    explicit EvenementInfoDialog(Evenement* e,QWidget *parent = 0);
    ~EvenementInfoDialog();

private:
    Ui::EvenementInfoDialog *ui;
};

#endif // EVENEMENTINFODIALOG_H
