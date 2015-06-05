#include "evenementinfodialog.h"
#include "ui_evenementinfodialog.h"

EvenementInfoDialog::EvenementInfoDialog(Evenement* e,QWidget *parent) :
    QDialog(parent),evt(e),
    ui(new Ui::EvenementInfoDialog)
{
    ui->setupUi(this);

    //recuperation des donnees de l'evenemnet et affichage
    ui->textBrowser->setPlainText(evt->toString());

    QObject::connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->pushButton_supprimer,SIGNAL(clicked()),this,SLOT(supprimer_evt()));

}

EvenementInfoDialog::~EvenementInfoDialog()
{
    delete ui;
}


void EvenementInfoDialog::supprimer_evt()
{
    Agenda::getInstance() >> evt;
    QDialog::done(0);
}
