#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetmanager.h"
#include "precedencemanager.h"
#include "agenda.h"
#include "tachecomposite.h"
#include "ui_mainwindow.h"
#include "ajouttachedialog.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void maj_treeWidget();
    void construct_recurs_tree(Tache* t,QTreeWidgetItem* root);




private:
    Ui::MainWindow *ui;

    Agenda& ag;
    ProjetManager& pm;
    PrecedenceManager& predm;

public slots:
    void maj_descripteurs();
    void ajouterTache();


private slots:
    void on_Bouton_ajouter_tache_clicked();
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
