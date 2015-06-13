#ifndef AGENDA_H
#define AGENDA_H

#include <vector>
#include "exception.h"
#include <iostream>
#include "observateur.h"
#include "programmationpartietache.h"
#include "evenementpj.h"
#include "enregistrable.h"

class Tache;

/*! \class Agenda
        \brief Classe permettant de gerer des evenements. Cette classe est un singleton
*/
class Agenda : public Observable, public Enregistrable
{
    /**
     * @brief vector des evenements geres
     */
    std::vector<Evenement*> events;

    static Agenda* instance;
    /**
     * @brief constructeur prive
     */
    Agenda() : Observable(), Enregistrable() {}

    /**
     * @brief destructeur prive
     */
    ~Agenda();
    /**
     * @brief constructeur de recopie prive
     */
    Agenda(const Agenda&);
    /**
     * @brief operateur de recopie prive
     *
     */
    Agenda& operator=(const Agenda&);


public:
    /*! Methode statique permettant de recupere ou creer l'unique instance
    */
    static Agenda& getInstance() { if(!instance) instance = new Agenda; return *instance; }
    /*! Methode statique permettant de liberer l'unique instance
    */
    static void libererInstance() { if(instance) delete instance; instance = 0; }

    /**
     * @brief Insere un evenement dans l'agenda
     * @param evt evenement
     *
     */
    Agenda& operator<<(Evenement& evt);
    /**
     * @brief Supprime un evenement de l'agenda
     * @param evt evenement
     *
     */
    Agenda& operator>>(Evenement* evt);

    /**
     * @brief Retourne les programmations de la tache
     * @param t tache
     *
     */
    std::vector<ProgrammationTache*> getProgrammationTache(const Tache* t);
    /**
     * @brief Verifie s'il n'y a pas d'evenement programme dans l'intervalle de temps
     * @param debut
     * @param fin
     *
     */
    bool isLibre(const QDateTime &debut, const QDateTime &fin);


    void save(const QString& f);
    void load(const QString& f);


    /*! \class iterator
            \brief Classe permettant d'iterer sur le evenements de l'agenda
    */
    class iterator{
        friend class Agenda;
        std::vector<Evenement*>::iterator it;
        iterator(const std::vector<Evenement*>::iterator& iter) : it(iter) {}
    public:
        Evenement& operator*() { return *(*it); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(events.begin()); }//<!Retourne un iterateur sur le premier evenement
    iterator end() { return iterator(events.end()); }//<!Retourne un iterateur sur le dernier evenement

};

#endif // AGENDA_H
