#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <vector>
#include <memory>
#include <string>
#include <map> 

// Dépendances des structures de données à analyser
#include "Utilisateur.h" 
#include "DossierMedical.h" 
#include "Consultation.h"
#include "Specialite.h"

// Définitions des couleurs (pour l'affichage)
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_RESET "\033[0m"


class Statistiques {
public:
    // Le constructeur est vide car cette classe ne maintient pas d'état.
    Statistiques() = default;

    /**
     * Calcule et affiche les statistiques du système.
     * Reçoit les collections de données par référence constante pour l'efficacité.
     */
    void afficherRapport(
        const std::vector<std::unique_ptr<Utilisateur>>& utilisateurs,
        const std::vector<DossierMedical>& dossiers
    ) const;
};

#endif // STATISTIQUES_H