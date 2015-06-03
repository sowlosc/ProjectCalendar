#include "jourgraphicscene.h"

QGraphicsRectItem* JourGraphicScene::ajouterEvenement(const QString titre, const QTime &deb, const Duree &dur,Evenement*e, const QColor& coul_contour, const QColor& coul_fond)
{
    dessinerFond();

    int mins_ecoulees = -deb.secsTo(QTime(6,0)) / 60;
    QTime fin = deb;
    fin.addSecs(mins_ecoulees * 60);

    qreal y = ( hauteur / nb_minutes ) * mins_ecoulees;
    qreal h = ( hauteur / nb_minutes ) * dur.getDureeEnHeures()*60;
    std::cout << " y = "<<y<<"\n";
    std::cout << "duree = "<<dur.getDureeEnHeures();
    std::cout << "h = "<<h<<"\n";
    //QGraphicsRectItem *rect = new QGraphicsRectItem(0,y,largeur,h,0);
    //QGraphicsRectItem *rect =  QGraphicsScene::addRect(0-3,y,largeur+6,h,QPen(coul_contour),QBrush(coul_fond));
    TacheGraphicItem *rect =  JourGraphicScene::addRect(TacheGraphicItem(-3,y,largeur+6,h,e),QPen(coul_contour),QBrush(coul_fond));
    rect->setFlag(QGraphicsItem::ItemIsSelectable);
    //rect->setFlag(QGraphicsItem::ItemIsFocusable);

    rect->setZValue(1);


    int Xtxt = 0,Ytxt = y;
    QString s;
    if(dur.getDureeEnMinutes()<30)
        return 0;
    else if(dur.getDureeEnMinutes()<75)
    {
        Xtxt = -3;
        Ytxt = y - 3;
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");
    }else if(dur.getDureeEnMinutes() >= 75)
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm") + "\n" + titre;
    else
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");


    QGraphicsTextItem *txt = QGraphicsScene::addText(s,QFont("Helvetica",8));
    txt->setTextWidth(95);
    txt->setX(Xtxt);
    txt->setY(Ytxt);
    txt->setZValue(2);
    return rect;
}

void JourGraphicScene::dessinerFond()
{
    qreal r = (hauteur / nb_minutes) * 30;
    qreal x = r;
    while( x < 960)
    {
        QGraphicsScene::addLine(-5,x,105,x,QPen(QColor("lightGray"),1,Qt::PenStyle(Qt::DashDotLine)))->setZValue(0);
        x += r;
    }
}


void JourGraphicScene::mise_a_jour()
{
    clear();
    Agenda& ag = Agenda::getInstance();
    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
    {
        if((*it).getDate() == date)
           ajouterEvenement("losc",(*it).getHoraire(),Duree(1,0),&(*it));
    }
}

