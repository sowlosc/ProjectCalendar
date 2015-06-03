#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetmanager.h"
#include "precedencemanager.h"
//#include "agenda.h"
#include "tachecomposite.h"
#include "ui_mainwindow.h"
#include "ajouttachedialog.h"
#include <iostream>
#include "observateur.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Observateur
{
    Q_OBJECT

public:

    static MainWindow& getInstance() { if(!instance) instance = new MainWindow; return *instance; }
    static void libererInstance() { if(instance) delete instance; instance = 0; }

    void maj_treeWidget();
    void construct_recurs_tree(Tache* t,QTreeWidgetItem* root);
    void mise_a_jour();



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

#endif // MAINWINDOW_H
