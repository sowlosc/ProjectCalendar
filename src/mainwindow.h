#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetmanager.h"
#include "precedencemanager.h"
#include "agenda.h"
#include "tachecomposite.h"
#include "ui_mainwindow.h"

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




private:
    Ui::MainWindow *ui;

    Agenda& ag;
    ProjetManager& pm;
    PrecedenceManager& predm;

public slots:
    void maj_descripteurs();


};







class TreeItem : public QTreeWidgetItem
{

public:
    TreeItem(QTreeWidgetItem * parent) : QTreeWidgetItem(parent) {}
    TreeItem(QTreeWidget * parent) : QTreeWidgetItem(parent) {}

    virtual QString getDescriptionHtml() const = 0;
};


class TreeTacheItem : public TreeItem
{
    Tache* tache;
public:
    TreeTacheItem(QTreeWidgetItem * parent,Tache* pt=0) : TreeItem(parent), tache(pt) {}
    TreeTacheItem(QTreeWidget * parent,Tache* pt=0) : TreeItem(parent), tache(pt) {}

    virtual QString getDescriptionHtml() const;
};

class TreeProjetItem : public TreeItem
{
    Projet* projet;
public:
    TreeProjetItem(QTreeWidgetItem * parent, Projet* pt=0) : TreeItem(parent), projet(pt) {}
    TreeProjetItem(QTreeWidget * parent, Projet* pt=0) : TreeItem(parent), projet(pt) {}

    virtual QString getDescriptionHtml() const;
};

#endif // MAINWINDOW_H
