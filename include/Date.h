#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>

/** Classe Date : Gère les dates dans le système (consultations, antécédents, etc...)
    Utilisez la norme de date au format jour/mois/année de préférence
*/

class Date {
public:
    // Constructeur par défaut (date d'aujourd'hui ou vide)
    Date();

    // Constructeur avec paramètres
    Date(int jour, int mois, int annee);

    // LE DESTRUCTEUR
    virtual ~Date();

    void afficher() const;
    std::string toString() const;

private:
    int jour;
    int mois;
    int annee;
};

#endif // DATE_H
