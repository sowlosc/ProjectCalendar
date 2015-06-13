#include "ajouttachedialog.h"
#include <QMessageBox>
#include "ui_ajouttachedialog.h"

AjoutTacheDialog::AjoutTacheDialog(QWidget *parent , const QString& proj, const QString& tCompo) :
    QDialog(parent), nomProjet(proj), nomTacheComposite(tCompo),
    ui(new Ui::AjoutTacheDialog)
{
    ui->setupUi(this);
    ui->dateEdit_dispo->setDate(QDate::currentDate());
    ui->dateEdit_ech->setDate(QDate::currentDate());
    QObject::connect(ui->checkBox_composite,SIGNAL(stateChanged(int)),this,SLOT(activerDuree(int)));
    QObject::connect(ui->checkBox_unitaire_non_preemptive,SIGNAL(stateChanged(int)),this,SLOT(activerLimiteDuree(int)));
    QObject::connect(ui->checkBox_unitaire_preemptive,SIGNAL(stateChanged(int)),this,SLOT(desactiverLimiteDuree(int)));

}


AjoutTacheDialog::~AjoutTacheDialog()
{
    delete ui;
}


void AjoutTacheDialog::activerDuree(int b)
{
    bool x = (b?false:true);
    ui->label_duree->setVisible(x);
    ui->timeEdit_duree->setVisible(x);
}


void AjoutTacheDialog::activerLimiteDuree(int b)
{
    ui->timeEdit_duree->setMaximumTime(QTime(12,0,0));
}
void AjoutTacheDialog::desactiverLimiteDuree(int b)
{
    ui->timeEdit_duree->setMaximumTime(QTime(23,59,59));
}

void AjoutTacheDialog::accept()
{
    QString id = ui->lineEdit_id->text();
    QString titre = ui->lineEdit_titre->text();
    QString desc = ui->textEdit_desc->toPlainText();
    QDate dispo = ui->dateEdit_dispo->date();
    QDate ech = ui->dateEdit_ech->date();

    //verification titre et id non vides
    if(id!="" && titre!="")
    {
        bool fin = true;
        Tache* t;
        try{
            //creation de la tache
            if(ui->checkBox_composite->isChecked())
            {
                t = new TacheComposite(id,titre,dispo,ech,desc);
            }else if(ui->checkBox_unitaire_non_preemptive->isChecked())
            {
                QTime time = ui->timeEdit_duree->time();
                Duree duree(time.hour(),time.minute());
                t = new TacheUnitaire(id,titre,dispo,ech,desc,duree,false);
            }else
            {
                QTime time = ui->timeEdit_duree->time();
                Duree duree(time.hour(),time.minute());
                t = new TacheUnitaire(id,titre,dispo,ech,desc,duree,true);
            }
        }catch(CalendarException e)
        {
            QMessageBox::warning(this,"Avertissement",e.getInfo());
            fin = false;
        }
        if(fin){
            if(nomTacheComposite == "")
            {
                //on ajoute dans un projet
                ProjetManager& pm = ProjetManager::getInstance();
                Projet& proj = pm.getProjet(nomProjet);
                try{
                    proj.ajouterTache(t);
                }catch(CalendarException e)
                {
                    QMessageBox::warning(this,"Avertissement",e.getInfo());
                    fin = false;
                }
            }else
            {
                //on ajoute dans une tache composite
                ProjetManager& pm = ProjetManager::getInstance();
                Projet& proj = pm.getProjet(nomProjet);
                TacheComposite* tc = dynamic_cast<TacheComposite*>(proj.getTache(nomTacheComposite));
                try{
                    tc->ajouterSousTache(t);
                }catch(CalendarException e)
                {
                    QMessageBox::warning(this,"Avertissement",e.getInfo());
                    fin = false;
                }
            }
        }
        if(fin){ //on notifie l'ajout a l'observateur pour qu'il se mette a jour
            ProjetManager::getInstance().notifier();
            this->done(1);
        }
    }

}
