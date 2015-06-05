#ifndef JOURGRAPHICSCENE_H
#define JOURGRAPHICSCENE_H
#include <QGraphicsScene>
#include <iostream>
#include <QString>
#include "duree.h"
#include <QTime>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QRect>
//#include "evenement.h"
#include "evenement1j.h"
#include "agenda.h"
class EvenementGraphicItem : public QGraphicsRectItem
{
    Evenement* evt;
public:
    EvenementGraphicItem(int x,int y,int width,int height,Evenement* e) : QGraphicsRectItem(x,y,width,height,0),evt(e) {}
    Evenement* getEvenement() const { return evt; }
};

class JourGraphicScene : public QGraphicsScene
{
    QString jour;
    QDate date;
    qreal hauteur;
    qreal largeur;
    unsigned int nb_minutes;
public:
    JourGraphicScene(const QString& nom,const QDate& d,qreal x, qreal y, qreal width, qreal height,unsigned int nb_m = 960, QObject* parent = 0 )
        :  QGraphicsScene(x,y,width,height,parent),jour(nom),date(d),hauteur(height),largeur(width),nb_minutes(nb_m) {

    }
    const QDate& getDate() const {return date; }
    void setDate(const QDate d) { date = d;}

    QGraphicsRectItem *ajouterEvenement(const QString titre, const QTime& deb, const Duree& dur,Evenement* e=0, const QColor &coul_contour = QColor("lightGray"), const QColor &coul_fond = QColor("blue"));
    void dessinerFond();
    ~JourGraphicScene() {}
    /*TacheGraphicItem* addRect(TacheGraphicItem* t,const QPen & pen , const QBrush & brush) {
        //QGraphicsScene::addRect(t.rect(),pen,brush);
        QGraphicsScene::addItem(t);
    }*/
    void mise_a_jour();
    void removeAllItems();


};



#endif // JOURGRAPHICSCENE_H
