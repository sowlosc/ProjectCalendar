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


void AjoutTacheDialog::accept()
{
    QString id = ui->lineEdit_id->text();
    QString titre = ui->lineEdit_titre->text();
    QString desc = ui->textEdit_desc->toPlainText();
    QDate dispo = ui->dateEdit_dispo->date();
    QDate ech = ui->dateEdit_ech->date();


    if(id!="" && titre!="" && dispo<=ech)
    {

        Tache* t;
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

        bool fin = true;
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
        if(fin){
            ProjetManager::getInstance().notifier(); //on notifie l'ajout a l'observateur pour qu'il se mette a jour
            this->done(1);
        }
    }

}
