#ifndef RDV_H
#define RDV_H

#include "evenement1j.h"
#include <QtXml>

class Rdv : public Evenement1j
{
    QString lieu;
    std::vector<QString> personnes;
public:


    Rdv( const QDate& ddeb,
         const QTime& tdeb,
         const Duree& dur,
         const QString& suj,
         const QString& l)
            : Evenement1j(ddeb,tdeb,dur,suj), lieu(l) {}
    virtual ~Rdv(){}

    const QString& getLieu() const { return lieu; }
    void setLieu(const QString& l) { lieu = l; }
    const std::vector<QString>& getPersonnes() const { return personnes; }
    void ajouterPersonne(const QString& nom);
    void retirerPersonne(const QString& nom);

    virtual QString toString() const;
    virtual Rdv* clone() const;

    void toXml(QXmlStreamWriter &) const;
    static Rdv* getFromXml(QXmlStreamReader &xml);

    class personnes_iterator{
        std::vector<QString>::iterator it;
        friend class Rdv;
        personnes_iterator(const std::vector<QString>::iterator iter) : it(iter) {}
    public:
        QString& operator*() { return *it; }
        personnes_iterator& operator++() { ++it; return *this; }
        bool operator!=(const personnes_iterator& at) { return it != at.it; }
    };

    personnes_iterator begin_personnes() { return personnes_iterator(personnes.begin()); }
    personnes_iterator end_personnes() { return personnes_iterator(personnes.end()); }

    class const_personnes_iterator{
        std::vector<QString>::const_iterator it;
        friend class Rdv;
        const_personnes_iterator(const std::vector<QString>::const_iterator iter) : it(iter) {}
    public:
        const QString& operator*() { return *it; }
        const_personnes_iterator& operator++() { ++it; return *this; }
        bool operator!=(const const_personnes_iterator& at) { return it != at.it; }
    };

    const_personnes_iterator begin_personnes() const { return const_personnes_iterator(personnes.begin()); }
    const_personnes_iterator end_personnes() const { return const_personnes_iterator(personnes.end()); }

};

#endif // RDV_H
