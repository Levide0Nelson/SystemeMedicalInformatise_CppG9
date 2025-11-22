#include "../include/Systeme.h"
#include "../include/ProfessionnelSante.h" // Correction du nom
#include "../include/Patient.h"
#include "../include/Administrateur.h"
#include "../include/Enumeration.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <map>

using namespace std;

// --- DÉFINITION DES COULEURS ---
#ifndef COULEUR_JAUNE
#define COULEUR_VERT "\033[32m"
#define COULEUR_ROUGE "\033[31m"
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_RESET "\033[0m"
#endif

// Constructeur
Systeme::Systeme() {
    nextUserId = 1;
    nextDossierId = 1;
    nextConsultationId = 1;
    nextAntecedentId = 1;
    utilisateurActuel = nullptr;
    creerUtilisateursInitiaux();
}

Systeme::~Systeme() {
    // Le destructeur par défaut gère la mémoire
}

DossierMedical* Systeme::trouverDossier(int idPatient) {
    // Implémentation du Membre 3 (En attente)
    return nullptr;
}

void Systeme::creerUtilisateursInitiaux() {
    // Implémentation du Membre 4 (En attente)
}

// --- FONCTIONS PLACEHOLDERS (En attente des autres membres) ---
Utilisateur* Systeme::authentification() { return nullptr; }
void Systeme::creerCompteUtilisateur(Role role) { }
void Systeme::creerDossierPatient() { }
void Systeme::afficherDossierPatient() { }
void Systeme::archiverDossier() { }
void Systeme::ajouterExamen(DossierMedical* dm_ptr) { }
void Systeme::menuPrincipal() { }
void Systeme::menuAdministrateur() { }
void Systeme::menuProfessionnelDeSante() { }
void Systeme::menuPatient() { }

/**
 * Logique : Programmation des Consultations
 */
void Systeme::programmerConsultation() {
    // NOTE : Code désactivé car la classe ProfessionnelSante n'est pas encore finie par le Membre 4.
    /*
    if (!dynamic_cast<ProfessionnelSante*>(utilisateurActuel)) {
        cout << COULEUR_ROUGE << "Erreur : Seul un Professionnel de Santé peut programmer une consultation." << COULEUR_RESET << endl;
        return;
    }
    */

    int idPatient;
    string motif, observations;

    cout << "\nID du Patient concerne: ";
    if (!(cin >> idPatient)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    cout << "[INFO] Simulation: Consultation en cours de creation..." << endl;

    // NOTE : La suite dépend du Membre 3 (DossierMedical). On met en pause pour que ça compile.
    /*
    DossierMedical* dm = trouverDossier(idPatient);
    if (!dm) {
        cout << COULEUR_ROUGE << "Dossier non trouve." << COULEUR_RESET << endl;
        return;
    }

    // Saisie factice pour l'instant
    int j, m, a;
    cout << "Date (J M A): "; cin >> j >> m >> a;
    // ...
    */

    cout << COULEUR_VERT << "Consultation enregistree (Simulation Interface)." << COULEUR_RESET << endl;
}

/**
 * Logique : Affichage des Statistiques
 */
void Systeme::afficherStatistiques() {
    int nbPatients = 0;
    int nbPS = 0;
    int nbConsultations = 0;
    int nbDossiersArchives = 0;

    // Maps pour la Catégorisation
    map<Specialite, int> consultationsParSpecialite;
    map<int, int> consultationsParPS;

    // NOTE : Boucles commentées car Utilisateur.h et DossierMedical.h sont encore vides.
    // Décommentez ceci quand vos collègues auront fini leurs classes.
    /*
    for (const auto& u : utilisateurs) {
        // if (u->getRole() == Role::PROFESSIONNEL) nbPS++;
    }

    for (const auto& dm : dossiers) {
        // if (dm.isArchive()) nbDossiersArchives++;
        // ...
    }
    */

    cout << COULEUR_JAUNE << "\n--- STATISTIQUES DU SYSTEME MEDIPASS ---" << COULEUR_RESET << endl;
    cout << "========================================" << endl;
    cout << "Patients enregistres : " << nbPatients << endl;
    cout << "Professionnels de Sante : " << nbPS << endl;
    cout << "Consultations totales : " << nbConsultations << endl;
    cout << "Dossiers Medicaux Archives : " << nbDossiersArchives << endl;
    cout << "========================================" << endl;
    cout << "[INFO] En attente des donnees du Backend (Membres 3, 4, 5)..." << endl;
}
