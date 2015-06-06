#include "ajoutprecedencedialog.h"
#include "ui_ajoutprecedencedialog.h"

AjoutPrecedenceDialog::AjoutPrecedenceDialog(const QString t, const QString p, QWidget *parent) :
    QDialog(parent),tacheId(t), projet(p),
    ui(new Ui::AjoutPrecedenceDialog)
{
    ui->setupUi(this);

    Projet& proj = ProjetManager::getInstance().getProjet(projet);

    std::map<QString, Tache*> *map = proj.getTacheMap(tacheId);

    for(std::map<QString,Tache*>::iterator it = map->begin(); it != map->end() ; ++it )
    {
        if(it->second->getId() != tacheId ){
            std::cout<<"affichage de "<<it->second->getTitre().toStdString()<<"\n";
            ui->selecteur_tache_pred->addItem(it->second->getTitre());
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
    PrecedenceManager::getInstance().ajouterPrecedence(*pred,*succ);
}
