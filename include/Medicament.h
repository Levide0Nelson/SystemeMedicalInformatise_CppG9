#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <string>

class Medicament {
private:
    std::string nomCommercial; // Ex: Doliprane
    std::string principeActif; // Ex: Paracétamol
public:
    Medicament(const std::string& nom, const std::string& actif) : nomCommercial(nom), principeActif(actif) {}
    void afficher() const;
    std::string getNomCommercial() const { return nomCommercial; } // Pour statistiques futures
};
#endif // MEDICAMENT_H

    