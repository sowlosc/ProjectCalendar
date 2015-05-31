#ifndef AJOUTTACHEDIALOG_H
#define AJOUTTACHEDIALOG_H

#include <QDialog>

#include "tacheunitaire.h"
#include "tachecomposite.h"
#include "projetmanager.h"
#include "mainwindow.h"
//class TreeItem;

namespace Ui {
class AjoutTacheDialog;
}

class AjoutTacheDialog : public QDialog
{
    Q_OBJECT
    TacheComposite *tCompo;
    Projet *projet;
public:
    explicit AjoutTacheDialog(QWidget *parent = 0,TacheComposite *tc = 0);
    explicit AjoutTacheDialog(QWidget *parent = 0,Projet *p = 0);
    ~AjoutTacheDialog();

private:
    Ui::AjoutTacheDialog *ui;

public slots:
    void activerDuree(int b);
    void accept();
};

#endif // AJOUTTACHEDIALOG_H
