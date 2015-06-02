#ifndef AJOUTTACHEDIALOG_H
#define AJOUTTACHEDIALOG_H

#include <QDialog>

#include "tacheunitaire.h"
#include "tachecomposite.h"
#include "projetmanager.h"
//#include "mainwindow.h"
//class TreeItem;

namespace Ui {
class AjoutTacheDialog;
}

class AjoutTacheDialog : public QDialog
{
    Q_OBJECT
    QString nomProjet;
    QString nomTacheComposite;
public:
    explicit AjoutTacheDialog(QWidget *parent , const QString& proj, const QString& tCompo="");
    //explicit AjoutTacheDialog(QWidget *parent ,Projet *p = 0);
    ~AjoutTacheDialog();

private:
    Ui::AjoutTacheDialog *ui;

public slots:
    void activerDuree(int b);
    void accept();
};

#endif // AJOUTTACHEDIALOG_H
