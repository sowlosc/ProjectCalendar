#ifndef EVENEMENTINFODIALOG_H
#define EVENEMENTINFODIALOG_H

#include <QDialog>
#include "evenement1j.h"
#include "agenda.h"
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

public slots:
    void reject();
};

#endif // EVENEMENTINFODIALOG_H
