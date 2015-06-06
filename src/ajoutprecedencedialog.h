#ifndef AJOUTPRECEDENCEDIALOG_H
#define AJOUTPRECEDENCEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "projetmanager.h"
#include "precedencemanager.h"


namespace Ui {
class AjoutPrecedenceDialog;
}

class AjoutPrecedenceDialog : public QDialog
{
    Q_OBJECT
    QString tacheId;
    QString projet;

public:
    explicit AjoutPrecedenceDialog(const QString tacheId, const QString p, QWidget *parent = 0);
    ~AjoutPrecedenceDialog();

private:
    Ui::AjoutPrecedenceDialog *ui;
    void ajouterPrecedenceRecurs(Tache *t,Tache* pred);

public slots:
    void accept();

};

#endif // AJOUTPRECEDENCEDIALOG_H
