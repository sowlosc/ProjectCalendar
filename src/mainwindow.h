#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetmanager.h"
#include "precedencemanager.h"
#include "agenda.h"
#include "tachecomposite.h"

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

};

#endif // MAINWINDOW_H
