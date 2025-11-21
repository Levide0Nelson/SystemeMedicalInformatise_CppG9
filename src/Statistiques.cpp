#include "Statistiques.h"
#include <iostream>
#include <algorithm> // Pour std::max_element

// L'implémentation de la fonction d'affichage et de calcul
void Statistiques::afficherRapport(
    const std::vector<std::unique_ptr<Utilisateur>>& utilisateurs,
    const std::vector<DossierMedical>& dossiers
) const {
    int nbPatients = 0;
    int nbPS = 0;
    int nbConsultations = 0;
    int nbDossiersArchives = 0;
    
    // Maps pour la Catégorisation et le décompte (Bonus)
    std::map<Specialite, int> consultationsParSpecialite;
    std::map<int, int> consultationsParPS; // Compte par ID du Professionnel de Santé

    // 1. Parcours des Utilisateurs (pour Patients et PS)
    for (const auto& u : utilisateurs) {
        if (u->getRole() == ROLE_PATIENT) nbPatients++;
        else if (u->getRole() == ROLE_PS) nbPS++;
    }

    // 2. Parcours des Dossiers et des Consultations
    for (const auto& dm : dossiers) {
        if (dm.isArchive()) nbDossiersArchives++; // Compteur d'archivage (Bonus Membre 3)
        
        // Itération sur les consultations (Dépendance Membre 5)
        for (const auto& c : dm.getConsultations()) {
            nbConsultations++;
            
            // Catégorisation par Spécialité (BONUS Membre 5)
            consultationsParSpecialite[c.getSpecialite()]++;
            
            // Comptage par PS (Statistique de performance BONUS Membre 5)
            consultationsParPS[c.getIdProfessionnel()]++;
        }
    }
    
    // 3. Affichage du Rapport
    std::cout << COULEUR_JAUNE << "\n--- STATISTIQUES DU SYSTÈME MEDIPASS ---" << COULEUR_RESET << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Patients enregistrés : " << nbPatients << std::endl;
    std::cout << "Professionnels de Santé : " << nbPS << std::endl;
    std::cout << "Consultations totales : " << nbConsultations << std::endl;
    std::cout << "Dossiers Médicaux Archivés : " << nbDossiersArchives << std::endl;
    
    // Répartition par Spécialité (BONUS)
    std::cout << "\n--- Répartition par Spécialité ---" << std::endl;
    for (const auto& pair : consultationsParSpecialite) {
        std::cout << "  - " << specialiteToString(pair.first) << " : " << pair.second << " consultation(s)" << std::endl;
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