#include "ajoutevenementtraddialog.h"
#include "ui_ajoutevenementtraddialog.h"
#include <QMessageBox>
AjoutEvenementTradDialog::AjoutEvenementTradDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutEvenementTradDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->checkBox_rdv,SIGNAL(stateChanged(int)),this,SLOT(activerRdv(int)));
    QObject::connect(ui->checkBox_evenement1j,SIGNAL(stateChanged(int)),this,SLOT(activerEvenement1j(int)));
    QObject::connect(ui->checkBox_evenementPj,SIGNAL(stateChanged(int)),this,SLOT(activerEvenementPj(int)));

    ui->dateEdit_date->setDate(QDate::currentDate());
    ui->dateEdit_datefin->setDate(QDate::currentDate().addDays(1));
    ui->timeEdit_duree->setTime(QTime(1,0));
    ui->timeEdit_horaire->setTime(QTime::currentTime());
    ui->timeEdit_horairefin->setTime(QTime::currentTime());

    ui->timeEdit_horaire->setMinimumTime(QTime(6,0));
    ui->timeEdit_horaire->setMaximumTime(QTime(22,0));
    ui->timeEdit_horairefin->setMinimumTime(QTime(6,0));
    ui->timeEdit_horairefin->setMaximumTime(QTime(22,0));

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

    int nbsecs = QDateTime(date,horaire).secsTo(QDateTime::currentDateTime());
    bool fin = true;
    if(nbsecs > 30){
        QMessageBox::warning(this,"Avertissement","Impossible de programmer une tâche dans le passé");
        fin = false;
    }
    if(fin){
        if(ui->checkBox_rdv->isChecked())
        {
            QString lieu = ui->lineEdit_lieu->text();
            QString pers = ui->plainTextEdit_personnes->toPlainText();
            QTime tduree = ui->timeEdit_duree->time();
            Duree duree(tduree.hour(),tduree.minute());

            Rdv evt(date,horaire,duree,sujet,lieu);
            QStringList liste = pers.split("\n");
            for(QStringList::iterator it = liste.begin(); it != liste.end(); ++it)
            {
                try{
                    evt.ajouterPersonne(*it);
                }catch(CalendarException e){
                    QMessageBox::warning(this,"Avertissement",e.getInfo());
                }
            }
            try{
                Agenda::getInstance() << evt;
            }catch(CalendarException e)
            {
                QMessageBox::warning(this,"Avertissement",e.getInfo());
                fin = false;
            }
        }else if(ui->checkBox_evenement1j->isChecked())
        {
            QTime tduree = ui->timeEdit_duree->time();
            Duree duree(tduree.hour(),tduree.minute());
            try{
                Evenement1j evt(date,horaire,duree,sujet);
                Agenda::getInstance() << evt;
            }catch(CalendarException e)
            {
                QMessageBox::warning(this,"Avertissement",e.getInfo());
                fin = false;
            }
        }else if(ui->checkBox_evenementPj->isChecked())
        {
            QDate dateFin = ui->dateEdit_datefin->date();
            QTime horaireFin  = ui->timeEdit_horairefin->time();
            try{
                EvenementPj evt(date,horaire,dateFin,horaireFin,sujet);
                Agenda::getInstance() << evt;
            }catch(CalendarException e)
            {
                QMessageBox::warning(this,"Avertissement",e.getInfo());
                fin = false;
            }
        }
        if(fin)
            done(1);
    }
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
