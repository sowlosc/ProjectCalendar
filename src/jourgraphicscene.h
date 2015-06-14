#ifndef JOURGRAPHICSCENE_H
#define JOURGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QString>
//#include "duree.h"
#include <QTime>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QRect>
#include "evenement1j.h"
#include "evenementpj.h"
#include "agenda.h"

/*! \class EvenementGraphicItem
        \brief Classe representant un evenements sur l'agenda
*/
class EvenementGraphicItem : public QGraphicsRectItem
{
    Evenement* evt;
public:
    //! Constructeur a partir des coordonnees x et y, d'une largeur, d'une hauteur et d'un pointeur sur un evenement
    /*! \param x axe horizontal
        \param y axe vertical
        \param width largeur
        \param height hauteur
        \param e pointeur sur un evenement
        */
    EvenementGraphicItem(int x,int y,int width,int height,Evenement* e) : QGraphicsRectItem(x,y,width,height,0),evt(e) {}

    Evenement* getEvenement() const { return evt; }
};

/*! \class JourGraphicScene
        \brief Classe permettant d'afficher les evenements sur l'agenda
*/
class JourGraphicScene : public QGraphicsScene, public Observateur
{

    QString jour;
    QDate date;
    qreal hauteur;
    qreal largeur;
    unsigned int nb_minutes;
public:
    //! Constructeur a partir d'un nom, de coordonnees x et y, d'une largeur, d'une hauteur, d'un nombre total de minutes et d'un widget parent
    /*! \param nom string
     * \param x axe horizontal
        \param y axe vertical
        \param width largeur
        \param height hauteur
        \param nb_min nombre de minutes
        \param parent widget parent
        */
    JourGraphicScene(const QString& nom,qreal x, qreal y, qreal width, qreal height,unsigned int nb_m = 960, QObject* parent = 0 )
        :  QGraphicsScene(x,y,width,height,parent),jour(nom),hauteur(height),largeur(width),nb_minutes(nb_m) {}

    const QDate& getDate() const { return date; }
    void setDate(const QDate& d) {
        date = d;
        if(date >= QDate::currentDate())
        {
            this->setBackgroundBrush(QBrush("#FFFFFF"));
        }else
            this->setBackgroundBrush(QBrush("lightGray"));
     }

    /**
     * @brief Ajoute un evenement dans l'agenda graphique
     * @param titre
     * @param deb horaire de debut
     * @param dur duree
     * @param e evenement
     * @param coul_fond couleur du fond
     * @param coul_contour couleur du texte
     *
     */
    QGraphicsRectItem *ajouterEvenement(const QString& titre, const QTime& deb, const Duree& dur,Evenement* e=0,
                                        const QColor &coul_fond = QColor("blue"),const QColor &coul_contour = QColor("black"));
    /**
     * @brief Desssine le fond de l'agenda
     */
    void dessinerFond();

    ~JourGraphicScene() {}
    /**
     * @brief Actualise l'agenda
     */
    void mise_a_jour();
    /**
     * @brief Vide l'agenda
     */
    void removeAllItems();


};



#endif // JOURGRAPHICSCENE_H
