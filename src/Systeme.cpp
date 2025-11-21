#include "Systeme.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <map> 
using namespace std;

// --- DÉFINITION DES COULEURS (À PARTAGER) ---
#define COULEUR_VERT "\033[32m"
#define COULEUR_ROUGE "\033[31m"
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_RESET "\033[0m"


// --- STRUCTURES COMMUNES (Implémentées par le Chef de Projet/Membres 3/4) ---

}

Systeme::~Systeme() {
    // Le destructeur par défaut gère la mémoire
}

DossierMedical* Systeme::trouverDossier(int idPatient) {
    // Implémentation du Membre 3
    
}

void Systeme::creerUtilisateursInitiaux() {
    // Implémentation du Membre 4
    
    // Implémentation du Membre 3
    
        
        // VOS DONNÉES DE TEST : Une consultation initiale pour vérifier vos statistiques
        dm->ajouterConsultation(Consultation(nextConsultationId++, Date(16, 11, 2025), 101, patientId, CARDIOLOGIE, "Bilan annuel", "Patient en bonne santé."));
    }
}

// --- FONCTIONS DES AUTRES MEMBRES (Placeholders) ---
Utilisateur* Systeme::authentification() { return nullptr; }
void Systeme::creerCompteUtilisateur(Role role) { /* Code Membre 4 */ }
void Systeme::creerDossierPatient() { /* Code Membre 3 */ }
void Systeme::afficherDossierPatient() { /* Code Membre 3 */ }
void Systeme::archiverDossier() { /* Code Membre 3 */ }
void Systeme::ajouterExamen(DossierMedical* dm_ptr) { /* Code Membre 3 */ }
void Systeme::menuPrincipal() { /* Code Membre 6 */ }
void Systeme::menuAdministrateur() { /* Code Membre 6 */ }
void Systeme::menuProfessionnelDeSante() { /* Code Membre 6 */ }
void Systeme::menuPatient() { /* Code Membre 6 */ }




/**
 * Logique : Programmation des Consultations (Obligatoire + Bonus Prescription/Spécialité)
 */
void Systeme::programmerConsultation() { 
    // Vérification de rôle (dépendance Membre 4)
    if (!dynamic_cast<ProfessionnelDeSante*>(utilisateurActuel)) {
        std::cout << COULEUR_ROUGE << "Erreur : Seul un Professionnel de Santé peut programmer une consultation." << COULEUR_RESET << std::endl;
        return;
    }

    int idPatient, j, m, a;
    std::string motif, observations;
    
    std::cout << "\nID du Patient concerné: ";
    if (!(std::cin >> idPatient)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return; }
    
    // Vérification du dossier (dépendance Membre 3)
    DossierMedical* dm = trouverDossier(idPatient);
    if (!dm || dm->isArchive()) { 
        std::cout << COULEUR_ROUGE << "Dossier Patient non trouvé ou archivé." << COULEUR_RESET << std::endl; 
        return; 
    }
    
    // Récupération de la Spécialité 

    ProfessionnelDeSante* psConnecte = static_cast<ProfessionnelDeSante*>(utilisateurActuel);
    
    // Saisie des données
    std::cout << "Date (J M A): "; std::cin >> j >> m >> a;
    std::cout << "Motif: "; std::cin.ignore(); std::getline(std::cin, motif);
    std::cout << "Observations: "; std::getline(std::cin, observations);
    
    // Création de la Consultation (Intègre la Specialite)
    Consultation nouvelleConsultation(nextConsultationId, Date(j, m, a), utilisateurActuel->getId(), idPatient, psConnecte->getSpecialite(), motif, observations);
    
    // Gestion de la Prescription 

    int choixPresc;
    std::cout << "Voulez-vous ajouter une prescription à cette consultation? (1=Oui, 0=Non): "; 
    if (!(std::cin >> choixPresc)) { choixPresc = 0; }
    
    if (choixPresc == 1) {
        std::string instr;
        std::cout << "Instructions de prescription: "; 
        std::cin.ignore(); 
        std::getline(std::cin, instr);
        auto p = std::make_unique<Prescription>(instr);
        
        std::string nomMed, actifMed;
        std::cout << "Nom du Médicament (tapez 'Q' pour finir): "; 
        while (std::getline(std::cin, nomMed) && nomMed != "Q") {
            std::cout << "Principe Actif: "; std::getline(std::cin, actifMed);
            // Utilise la classe Medicament
            p->ajouterMedicament(Medicament(nomMed, actifMed));
            std::cout << "Nom du Médicament suivant (Q pour finir): ";
        }
        
        nouvelleConsultation.setPrescription(std::move(p));
    }
    
    // Enregistrement dans le Dossier Médical (dépendance Membre 3)
    dm->ajouterConsultation(nouvelleConsultation);
    
    std::cout << COULEUR_VERT << "Consultation #" << nextConsultationId << " enregistrée." << COULEUR_RESET << std::endl;
    nextConsultationId++;
}


/**
 * Logique : Affichage des Statistiques (Obligatoire + Bonus Catégorisation)
 */
void Systeme::afficherStatistiques() {
    int nbPatients = 0;
    int nbPS = 0;
    int nbConsultations = 0;
    int nbDossiersArchives = 0;
    
    // Utilisation de std::map pour la Catégorisation (BONUS)
    std::map<Specialite, int> consultationsParSpecialite;
    std::map<int, int> consultationsParPS; 

    // Compteurs globaux (Dépendance Membre 4)
    for (const auto& u : utilisateurs) {
        if (u->getRole() == ROLE_PATIENT) nbPatients++;
        else if (u->getRole() == ROLE_PS) nbPS++;
    }

    // Parcours des Dossiers (Dépendance Membre 3) et des Consultations
    for (const auto& dm : dossiers) {
        if (dm.isArchive()) nbDossiersArchives++;
        for (const auto& c : dm.getConsultations()) {
            nbConsultations++;
            // Agrégation par Spécialité (Catégorisation BONUS)
            consultationsParSpecialite[c.getSpecialite()]++;
            // Agrégation par PS (Statistique de performance BONUS)
            consultationsParPS[c.getIdProfessionnel()]++;
        }
    }
    
    std::cout << COULEUR_JAUNE << "\n--- STATISTIQUES DU SYSTÈME MEDIPASS ---" << COULEUR_RESET << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Patients : " << nbPatients << " | PS : " << nbPS << " | Consultations : " << nbConsultations << std::endl;
    std::cout << "Dossiers Médicaux Archivés : " << nbDossiersArchives << std::endl;
    
    // Répartition par Spécialité 

    std::cout << "\n--- Répartition par Spécialité ---" << std::endl;
    for (const auto& pair : consultationsParSpecialite) {
        std::cout << "  - " << specialiteToString(pair.first) << " : " << pair.second << " consultation(s)" << std::endl;
    }

    // PS le plus actif 
    if (!consultationsParPS.empty()) {
        auto bestPS = std::max_element(consultationsParPS.begin(), consultationsParPS.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

        std::cout << "\n--- PS le plus actif ---" << std::endl;
        std::cout << "  - ID PS : " << bestPS->first << " | Consultations : " << bestPS->second << std::endl;
    }
    std::cout << "========================================" << std::endl;
}

