#ifndef SYSTEME_H
#define SYSTEME_H

#include <vector>
#include <memory>
#include <string>

// --- Dépendances des Classes Utilisateurs (Membres 3 & 4) ---
#include "Utilisateur.h" 
#include "Patient.h" 
#include "ProfessionnelDeSante.h" 
#include "Administrateur.h" 

// --- Dépendances des Classes Médicales (Membres 3 & 5) ---
#include "DossierMedical.h" 
#include "Consultation.h"  
#include "Prescription.h"  
#include "Medicament.h"    
#include "Antecedent.h" 
#include "Examen.h" 

// --- Dépendances Utilitaires (Commun) ---
#include "Date.h" 
#include "Specialite.h" 

class Systeme {
private:
    // Attributs de gestion de l'état du système
    // M4 : Gestion des utilisateurs (Utilise le polymorphisme grâce à unique_ptr)
    std::vector<std::unique_ptr<Utilisateur>> utilisateurs; 
    // M3 : Gestion des dossiers (Utilise l'agrégation)
    std::vector<DossierMedical> dossiers; 
    
    // Compteurs d'ID (Commun)
    int nextUserId;
    int nextDossierId;
    int nextConsultationId;
    int nextAntecedentId;
    
    // M4 : Utilisateur actuellement connecté
    Utilisateur* utilisateurActuel;

    // Fonctions d'initialisation et utilitaires internes
    void creerUtilisateursInitiaux();
    
public:
    // Constructeur et Destructeur
    Systeme();
    ~Systeme();

    // --- Fonctions d'Authentification et Utilitaires (Membre 4) ---
    Utilisateur* authentification();
    void creerCompteUtilisateur(Role role);
    
    // --- Fonctions de Gestion des Dossiers (Membre 3) ---
    DossierMedical* trouverDossier(int idPatient); // Fonction utilitaire clé
    void creerDossierPatient();
    void afficherDossierPatient();
    void archiverDossier(); // BONUS Archivage
    void ajouterExamen(DossierMedical* dm_ptr); // BONUS Examen
    
    
    
    
    // 1. Programmation de la consultation 

    void programmerConsultation();
    
    // 2. Affichage des statistiques 

    void afficherStatistiques();
    
    
    // --- Fonctions de Menus (Membre 6) ---
    void menuPrincipal();
    void menuAdministrateur();
    void menuProfessionnelDeSante();
    void menuPatient();
};

#endif // SYSTEME_H