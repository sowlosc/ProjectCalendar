#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include <map>
#include <sstream>

/*! \class TacheComposite
        \brief Classe representant une tache composite
*/
class TacheComposite : public Tache
{
    /**
     * @brief Envsembles des sous-taches
     */
    std::map<QString, Tache*> sousTaches;

public:
    /**
     * @brief constructeur
     * @param id identificateur
     * @param t titre
     * @param dispo date de disponibilite
     * @param ech date d'echeance
     * @param txt description
     */
    TacheComposite(const QString& id,
                   const QString& t,
                   const QDate& dispo,
                   const QDate& ech,
                   const QString& txt) : Tache(id,t,dispo,ech,txt) {}
    virtual ~TacheComposite();

    virtual QString toString() const;
    virtual bool isComposite() const { return true; }
    virtual void toXml(QXmlStreamWriter&) const;
    static TacheComposite* getFromXml(QXmlStreamReader&);

    /**
     * @brief Ajoute une sous-taches
     * @param t pointeur sur la tache a ajouter
     */
    void ajouterSousTache(Tache* t);
    /**
     * @brief Retire une sous-tache
     * @param t pointeur sur la sous-tache
     */
    void retirerSousTache(Tache* t);


    /**
     * @brief Retourne un pointeur sur la sous-tache
     * @param id identificateur
     * @return pointeur sur la sous-tache ou 0
     */
    Tache *getSousTache(const QString& id);
    /**
     * @brief Verifie si la tache contient la sous-tache
     * @param t titre de la sous-tache
     * @return true ou false
     */
    bool contientSousTache(const Tache* t);

    virtual bool isProgrammed() const;

    /**
     * @brief Retourne le map des sous-taches si elle contient la tache sinon cherche dans les sous-taches
     * @param id identificateur de la tache recherchee
     *
     */
    std::map<QString, Tache*>* getTacheMap(const QString &id);


    /*! \class iterator
            \brief Classe permettant d'iterer sur les sous-taches d'une tache composite
    */
    class iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString, Tache*>::iterator& iter) : it(iter) {}
    public:
        Tache& operator*() { return *(it->second); }
        iterator& operator++ (){ ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur sur la premiere sous-tache
     *
     */
    iterator begin() { return iterator(sousTaches.begin()); }
    /**
     * @brief Retourne un iterateur apres la derniere sous-tache
     *
     */
    iterator end() { return iterator(sousTaches.end()); }


    /*! \class const_iterator
            \brief Classe permettant d'iterer sur les sous-taches d'une tache composite
    */
    class const_iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::const_iterator it;
        const_iterator(const std::map<QString, Tache*>::const_iterator& iter) : it(iter) {}
    public:
        const Tache& operator*() { return *(it->second); }
        const_iterator& operator++ (){ ++it; return *this; }
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur const sur la premiere sous-tache
     *
     */
    const_iterator begin() const { return const_iterator(sousTaches.begin()); }
    /**
     * @brief Retourne un iterateur const apres la derniere sous-tache
     *
     */
    const_iterator end() const { return const_iterator(sousTaches.end()); }
};

#endif // TACHECOMPOSITE_H
