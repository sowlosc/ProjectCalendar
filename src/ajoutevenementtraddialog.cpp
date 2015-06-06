#include "ajoutevenementtraddialog.h"
#include "ui_ajoutevenementtraddialog.h"

AjoutEvenementTradDialog::AjoutEvenementTradDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutEvenementTradDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->checkBox_rdv,SIGNAL(stateChanged(int)),this,SLOT(activerRdv(int)));
    QObject::connect(ui->checkBox_evenement1j,SIGNAL(stateChanged(int)),this,SLOT(activerEvenement1j(int)));
    QObject::connect(ui->checkBox_evenementPj,SIGNAL(stateChanged(int)),this,SLOT(activerEvenementPj(int)));

    ui->dateEdit_date->setDate(QDate::currentDate());
    ui->dateEdit_datefin->setDate(QDate::currentDate());
    ui->timeEdit_duree->setTime(QTime(1,0));
    ui->timeEdit_horaire->setTime(QTime(12,0));
    ui->timeEdit_horairefin->setTime(QTime(12,0));
    int x=0;

    ui->label_lieu->setVisible(x);
    ui->label_personnes->setVisible(x);
    ui->lineEdit_lieu->setVisible(x);
    ui->plainTextEdit_personnes->setVisible(x);
    ui->timeEdit_horairefin->setVisible(x);
    ui->label_horairefin->setVisible(x);
    ui->label_datefin->setVisible(x);
    ui->dateEdit_datefin->setVisible(x);
}

AjoutEvenementTradDialog::~AjoutEvenementTradDialog()
{
    delete ui;
}

void AjoutEvenementTradDialog::accept()
{
    QString sujet = ui->lineEdit_sujet->text();
    QDate date = ui->dateEdit_date->date();
    QTime horaire = ui->timeEdit_horaire->time();

    if(ui->checkBox_rdv->isChecked())
    {
        QString lieu = ui->lineEdit_lieu->text();
        QString pers = ui->plainTextEdit_personnes->toPlainText();
        QTime tduree = ui->timeEdit_duree->time();
        Duree duree(tduree.hour(),tduree.minute());

        Rdv evt(date,horaire,duree,sujet,lieu);
        QStringList liste = pers.split("\n");
        for(QStringList::iterator it = liste.begin(); it != liste.end(); ++it)
            evt.ajouterPersonne(*it);
        Agenda::getInstance() << evt;

    }else if(ui->checkBox_evenement1j->isChecked())
    {
        QTime tduree = ui->timeEdit_duree->time();
        Duree duree(tduree.hour(),tduree.minute());
        Evenement1j evt(date,horaire,duree,sujet);
        Agenda::getInstance() << evt;
    }else if(ui->checkBox_evenementPj->isChecked())
    {
        QDate dateFin = ui->dateEdit_datefin->date();
        QTime horaireFin  = ui->timeEdit_horairefin->time();
        EvenementPj evt(date,horaire,dateFin,horaireFin,sujet);
        Agenda::getInstance() << evt;
    }

    done(1);
}



void AjoutEvenementTradDialog::activerRdv(int x)
{
    ui->label_lieu->setVisible(x);
    ui->label_personnes->setVisible(x);
    ui->lineEdit_lieu->setVisible(x);
    ui->plainTextEdit_personnes->setVisible(x);
    ui->timeEdit_duree->setVisible(x);
    ui->label_duree->setVisible(x);
}

void AjoutEvenementTradDialog::activerEvenement1j(int x)
{
    ui->timeEdit_duree->setVisible(x);
    ui->label_duree->setVisible(x);

}
void AjoutEvenementTradDialog::activerEvenementPj(int x)
{
    ui->timeEdit_horairefin->setVisible(x);
    ui->label_horairefin->setVisible(x);
    ui->label_datefin->setVisible(x);
    ui->dateEdit_datefin->setVisible(x);
}
