#include "ajoutprecedencedialog.h"
#include "ui_ajoutprecedencedialog.h"

AjoutPrecedenceDialog::AjoutPrecedenceDialog(const QString t, const QString p, QWidget *parent) :
    QDialog(parent),tacheId(t), projet(p),
    ui(new Ui::AjoutPrecedenceDialog)
{
    ui->setupUi(this);

    ui->label->setText("Tache devant être terminée avant "+tacheId+ " :");

    Projet& proj = ProjetManager::getInstance().getProjet(projet);

    Tache* tache = proj.getTache(tacheId);

    std::map<QString, Tache*> *map = proj.getTacheMap(tacheId);

    for(std::map<QString,Tache*>::iterator it = map->begin(); it != map->end() ; ++it )
    {
        if(it->second->getId() != tacheId ){
            bool ok = true;
            for(Tache::const_succ_iterator succIter = it->second->beginSucc() ; succIter != it->second->endSucc() ; ++succIter)
                if((*succIter)->getId() == tacheId)
                    ok = false;
            if(ok){                
                std::cout<<"affichage de "<<it->second->getTitre().toStdString()<<"\n";
                ui->selecteur_tache_pred->addItem(it->second->getId());
            }
        }
    }


}

AjoutPrecedenceDialog::~AjoutPrecedenceDialog()
{
    delete ui;
}

void AjoutPrecedenceDialog::accept()
{
    Tache* pred = ProjetManager::getInstance().getProjet(projet).getTache(ui->selecteur_tache_pred->currentText());
    Tache* succ = ProjetManager::getInstance().getProjet(projet).getTache(tacheId);

    ajouterPrecedenceRecurs(succ,pred);
    done(1);
}



void AjoutPrecedenceDialog::ajouterPrecedenceRecurs(Tache* t,Tache* pred) //double recurs pour ajouter tous les preds a tous les succs
{
    ajouterPredRecurs(t,pred);
    if(t->isComposite()){
        TacheComposite *tc = dynamic_cast<TacheComposite*>(t);
        for(TacheComposite::iterator it = tc->begin(); it != tc->end() ; ++it)
            ajouterPrecedenceRecurs(&(*it),pred);
    }
}

void AjoutPrecedenceDialog::ajouterPredRecurs(Tache*t, Tache*pred)
{
    PrecedenceManager::getInstance().ajouterPrecedence(*pred,*t);
    if(pred->isComposite()){
        TacheComposite *tc = dynamic_cast<TacheComposite*>(pred);
        for(TacheComposite::iterator it = tc->begin() ; it!= tc->end() ; ++it)
            ajouterPredRecurs(t,&(*it));
    }
}
