#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetmanager.h"
//#include "precedencemanager.h"
#include "tachecomposite.h"
#include "ui_mainwindow.h"
#include "ajouttachedialog.h"
#include "ajoutprojetdialog.h"
#include <iostream>
//#include "observateur.h"
#include "evenementtrad.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsTextItem>
#include "jourgraphicscene.h"
#include "evenementinfodialog.h"
#include "ajoutevenementtraddialog.h"
#include "ajoutprecedencedialog.h"
#include "programmationtachedialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Observateur
{
    Q_OBJECT

private:
    JourGraphicScene *scenes[7];
public:

    static MainWindow& getInstance() { if(!instance) instance = new MainWindow; return *instance; }
    static void libererInstance() {
        ProjetManager::libererInstance();
        Agenda::libererInstance();
        PrecedenceManager::libereInstace();
        if(instance) delete instance;
        instance = 0;
    }

    void maj_treeWidget();
    void construct_recurs_tree(Tache* t,QTreeWidgetItem* root);
    void mise_a_jour();
    void maj_listePrecedences();
    void closeEvent(QCloseEvent *);


private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow *instance;
    Ui::MainWindow *ui;
    Agenda& ag;
    ProjetManager& pm;
    PrecedenceManager& predm;



public slots:
    void maj_descripteurs();
    void ajouterTache();
    void supprimerTache();
    void supprimerProjet();
    void ajouterProjet();
    void detaillerEvenement_lundi();
    void detaillerEvenement_mardi();
    void detaillerEvenement_mercredi();
    void detaillerEvenement_jeudi();
    void detaillerEvenement_vendredi();
    void detaillerEvenement_samedi();
    void detaillerEvenement_dimanche();
    void maj_dates();
    void ajouterEvenementTrad();
    void ajouterPrecedence();
    void supprimerPrecedence();
    void programmerTache();
    void load();
    void save();
    void exporterProgrammationsSemaine();
    void exporterProgrammationsProjet();

};





/*
 * Specialisation de TreeItem
 * pour pouvoir les lier à
 * des taches et des projets
 * */


class TreeItem : public QTreeWidgetItem
{

public:
    TreeItem(QTreeWidgetItem * parent) : QTreeWidgetItem(parent) {}
    TreeItem(QTreeWidget * parent) : QTreeWidgetItem(parent) {}
    //~TreeItem() { std::cout << "---------------****> destruction TreeItem" << "\n";}

    TreeItem* getParentProject();

    virtual QString getDescriptionHtml() const = 0;
    virtual bool isUnitaire() const = 0;
    virtual bool isProjetItem() const = 0;
};

class TreeTacheItem : public TreeItem
{
    Tache* tache;
public:
    TreeTacheItem(QTreeWidgetItem * parent,Tache* pt=0) : TreeItem(parent), tache(pt) {}
    TreeTacheItem(QTreeWidget * parent,Tache* pt=0) : TreeItem(parent), tache(pt) {}
    Tache* getTache() const { return tache; }
    virtual QString getDescriptionHtml() const;
    virtual bool isUnitaire() const { return !tache->isComposite(); }
    virtual bool isProjetItem() const { return false; }
};

class TreeProjetItem : public TreeItem
{
    Projet* projet;
public:
    TreeProjetItem(QTreeWidgetItem * parent, Projet* pt=0) : TreeItem(parent), projet(pt) {}
    TreeProjetItem(QTreeWidget * parent, Projet* pt=0) : TreeItem(parent), projet(pt) {}
    Projet* getProjet() const { return projet; }

    virtual QString getDescriptionHtml() const;
    virtual bool isUnitaire() const { return false; }
    virtual bool isProjetItem() const { return true; }

};

class ListPrecedenceItem : public QListWidgetItem
{
    const Precedence* precedence;
public:
    ListPrecedenceItem(const QString& txt, const Precedence* pr, QListWidget* parent) : QListWidgetItem(txt,parent), precedence(pr) {}

    const Precedence* getPrecedence() const { return precedence; }
};

#endif // MAINWINDOW_H
