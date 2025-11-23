#include "../include/Statistiques.h"
#include <iostream>
#include <algorithm> // Pour std::max_element
#include <map>       // Manquait pour les std::map

// --- Imports nécessaires pour que le compilateur connaisse les autres classes ---
#include "../include/Utilisateur.h"
#include "../include/DossierMedical.h"
#include "../include/Consultation.h"
#include "../include/Enumeration.h"

using namespace std;

// Définition des couleurs (au cas où elles manquent)
#ifndef COULEUR_JAUNE
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_RESET "\033[0m"
#endif

// Simulation des rôles (pour éviter l'erreur "not declared")
#ifndef ROLE_PATIENT
#define ROLE_PATIENT 0
#define ROLE_PS 1
#endif

void Statistiques::afficherRapport(
    const std::vector<std::unique_ptr<Utilisateur>>& utilisateurs,
    const std::vector<DossierMedical>& dossiers
) const {
    int nbPatients = 0;
    int nbPS = 0;
    int nbConsultations = 0;
    int nbDossiersArchives = 0;

    // Maps pour la Catégorisation et le décompte
    std::map<Specialite, int> consultationsParSpecialite;
    std::map<int, int> consultationsParPS;

    // 1. Parcours des Utilisateurs
    // NOTE DU MEMBRE 6 : Partie désactivée car Utilisateur.h n'a pas encore getRole()
    // Décommentez ceci quand le Membre 4 aura fini son code.
    /*
    for (const auto& u : utilisateurs) {
        if (u->getRole() == ROLE_PATIENT) nbPatients++;
        else if (u->getRole() == ROLE_PS) nbPS++;
    }
    */
    cout << "[INFO] Stats Utilisateurs en attente (Manque getRole)" << endl;

    // 2. Parcours des Dossiers et des Consultations
    // NOTE DU MEMBRE 6 : Partie désactivée car DossierMedical.h est encore vide
    // Décommentez ceci quand le Membre 3 aura fini son code.
    /*
    for (const auto& dm : dossiers) {
        if (dm.isArchive()) nbDossiersArchives++;

        for (const auto& c : dm.getConsultations()) {
            nbConsultations++;

            // Catégorisation par Spécialité
            consultationsParSpecialite[c.getSpecialite()]++;

            // Comptage par PS
            consultationsParPS[c.getIdProfessionnel()]++;
        }
    }
    */
    cout << "[INFO] Stats Dossiers en attente (Manque getConsultations)" << endl;

    // 3. Affichage du Rapport
    std::cout << COULEUR_JAUNE << "\n--- STATISTIQUES DU SYSTEME MEDIPASS ---" << COULEUR_RESET << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Patients enregistres : " << nbPatients << std::endl;
    std::cout << "Professionnels de Sante : " << nbPS << std::endl;
    std::cout << "Consultations totales : " << nbConsultations << std::endl;
    std::cout << "Dossiers Medicaux Archives : " << nbDossiersArchives << std::endl;

    // Répartition par Spécialité (BONUS)
    std::cout << "\n--- Repartition par Specialite ---" << std::endl;
    if (consultationsParSpecialite.empty()) {
        std::cout << "  (Aucune donnee disponible)" << std::endl;
    } else {
        for (const auto& pair : consultationsParSpecialite) {
            std::cout << "  - " << specialiteToString(pair.first) << " : " << pair.second << " consultation(s)" << std::endl;
        }
    }

    // PS le plus actif (BONUS)
    if (!consultationsParPS.empty()) {
        auto bestPS = std::max_element(consultationsParPS.begin(), consultationsParPS.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

        std::cout << "\n--- PS le plus actif ---" << std::endl;
        std::cout << "  - ID PS : " << bestPS->first << " | Consultations : " << bestPS->second << std::endl;
    }
    std::cout << "========================================" << std::endl;
}
