#include "ajoutprojetdialog.h"
#include "ui_ajoutprojetdialog.h"
#include "projetmanager.h"
#include <QMessageBox>

AjoutProjetDialog::AjoutProjetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutProjetDialog)
{
    ui->setupUi(this);
    ui->dateEdit_disponibilite->setDate(QDate::currentDate());
    ui->dateEdit_echeance->setDate(QDate::currentDate());
}

AjoutProjetDialog::~AjoutProjetDialog()
{
    delete ui;
}


void AjoutProjetDialog::accept()
{
    QString titre = ui->lineEdit_titre->text();
    QString desc = ui->textEdit_description->toPlainText();
    QDate dispo = ui->dateEdit_disponibilite->date();
    QDate ech = ui->dateEdit_echeance->date();

    if(titre!="")
    {
        bool fin = true;
        try
        {
            ProjetManager::getInstance().ajouterProjet(titre,desc,dispo,ech);
        }catch(CalendarException e)
        {
            QMessageBox::warning(this,"Avertissement",e.getInfo());
            fin = false;
        }
        if(fin)
            done(1);
    }
}
