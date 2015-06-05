#include "evenementinfodialog.h"
#include "ui_evenementinfodialog.h"

EvenementInfoDialog::EvenementInfoDialog(Evenement* e,QWidget *parent) :
    QDialog(parent),evt(e),
    ui(new Ui::EvenementInfoDialog)
{
    ui->setupUi(this);

    //recuperation des donnees de l'evenemnet et affichage
    ui->textBrowser->setPlainText(evt->toString());



}

EvenementInfoDialog::~EvenementInfoDialog()
{
    delete ui;
}


void EvenementInfoDialog::reject()
{
    Agenda::getInstance() >> evt;
    QDialog::done(0);
}
