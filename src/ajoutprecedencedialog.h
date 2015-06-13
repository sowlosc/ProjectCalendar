#ifndef AJOUTPRECEDENCEDIALOG_H
#define AJOUTPRECEDENCEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "projetmanager.h"
#include "precedencemanager.h"


namespace Ui {
class AjoutPrecedenceDialog;
}
/*! \class AjoutPrecedenceDialog
        \brief Fenetre de dialogue pour l'ajout de contraintes de precedence
*/
class AjoutPrecedenceDialog : public QDialog
{
    Q_OBJECT
    Tache* tache;
    Projet* projet;

public:
    explicit AjoutPrecedenceDialog(Tache* t, Projet* p, QWidget *parent = 0);
    ~AjoutPrecedenceDialog();

private:
    Ui::AjoutPrecedenceDialog *ui;
    void ajouterPrecedenceRecurs(Tache *t,Tache* pred);
    void ajouterPredRecurs(Tache *t,Tache* pred);


public slots:
    void accept();

};

#endif // AJOUTPRECEDENCEDIALOG_H
