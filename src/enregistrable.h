#ifndef ENREGISTRABLE_H
#define ENREGISTRABLE_H
#include <QString>
/*! \class Enregistrable
        \brief Classe definissant l'interface d'objets qui peuvent etre
        enregistres et charges à partir de fichier xml
*/
class Enregistrable
{
public:
    /**
     * @brief constructeur
     */
    Enregistrable(){}
    ~Enregistrable(){}

    /**
     * @brief Permet d'enregistrer dans un fichier xml
     * @param f
     */
    virtual void save(const QString& f) = 0;
    /**
     * @brief Permet de charger a partir d'un fichier xml
     * @param f
     */
    virtual void load(const QString& f) = 0;
};

#endif // ENREGISTRABLE_H
