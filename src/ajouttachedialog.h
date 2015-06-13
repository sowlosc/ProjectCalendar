#ifndef AJOUTTACHEDIALOG_H
#define AJOUTTACHEDIALOG_H

#include <QDialog>

#include "tacheunitaire.h"
#include "tachecomposite.h"
#include "projetmanager.h"


namespace Ui {
class AjoutTacheDialog;
}


/*! \class AjoutTacheDialog
        \brief Fenetre de dialogue pour l'ajout d'une tache a un projet
*/
class AjoutTacheDialog : public QDialog
{
    Q_OBJECT
    QString nomProjet;
    QString nomTacheComposite;
public:
    explicit AjoutTacheDialog(QWidget *parent , const QString& proj, const QString& tCompo="");
    ~AjoutTacheDialog();

private:
    Ui::AjoutTacheDialog *ui;

public slots:
    void activerDuree(int b);
    void activerLimiteDuree(int b);
    void desactiverLimiteDuree(int b);
    void accept();
};

#endif // AJOUTTACHEDIALOG_H
