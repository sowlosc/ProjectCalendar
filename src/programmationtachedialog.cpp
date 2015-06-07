#include "programmationtachedialog.h"
#include "ui_programmationtachedialog.h"

ProgrammationTacheDialog::ProgrammationTacheDialog(TacheUnitaire *t, QWidget *parent) :
    QDialog(parent),tache(t),
    ui(new Ui::ProgrammationTacheDialog)
{
    ui->setupUi(this);
    ui->label_duree->setVisible(0);
    ui->timeEdit_duree->setVisible(0);
    ui->dateEdit_date->setDate(QDate::currentDate());
    ui->timeEdit_horaire->setTime(QTime(12,0));
    QObject::connect(ui->checkBox_partie_tache,SIGNAL(stateChanged(int)),this,SLOT(activerDuree(int)));
}

ProgrammationTacheDialog::~ProgrammationTacheDialog()
{
    delete ui;
}


void ProgrammationTacheDialog::activerDuree(int x)
{
    ui->label_duree->setVisible(x);
    ui->timeEdit_duree->setVisible(x);
}


void ProgrammationTacheDialog::accept()
{
    QDate date = ui->dateEdit_date->date();
    QTime horaire = ui->timeEdit_horaire->time();

    bool ok = true;

    for(Tache::const_succ_iterator it = tache->beginSucc() ; it != tache->endSucc() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);

        for(std::vector<ProgrammationTache*>::const_iterator at = progs.begin() ; at != progs.end() ; ++at)
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()) <= QDateTime(date,horaire))
                ok = false;
    }

    for(Tache::const_pred_iterator it = tache->beginPred() ; it != tache->endPred() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);

        for(std::vector<ProgrammationTache*>::iterator at = progs.begin() ; at != progs.end() ; ++at)
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()) >= QDateTime(date,horaire))
                ok = false;
    }

    if(ok){
        if(ui->checkBox_partie_tache->isChecked())
        {
            QTime duree = ui->timeEdit_duree->time();
            ProgrammationPartieTache prog(date,horaire,Duree(duree.hour(),duree.minute()),tache);
            Agenda::getInstance() << prog;
        }else
        {
            ProgrammationTache prog(date,horaire,tache);
            Agenda::getInstance() << prog;
        }
    }
    done(1);
}
