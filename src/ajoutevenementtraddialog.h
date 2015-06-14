#ifndef AJOUTEVENEMENTTRADDIALOG_H
#define AJOUTEVENEMENTTRADDIALOG_H

#include <QDialog>
#include "evenementpj.h"
#include "rdv.h"
#include "agenda.h"

namespace Ui {
class AjoutEvenementTradDialog;
}

/*! \class AjoutEvenementTradDialog
        \brief Fenetre de dialogue pour la creation et l'ajout d'un evenement traditionnel
*/
class AjoutEvenementTradDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AjoutEvenementTradDialog(QWidget *parent = 0);
    ~AjoutEvenementTradDialog();

private:
    Ui::AjoutEvenementTradDialog *ui;

public slots:
    void activerRdv(int);
    void activerEvenement1j(int);
    void activerEvenementPj(int);
    void accept();
};

#endif // AJOUTEVENEMENTTRADDIALOG_H
