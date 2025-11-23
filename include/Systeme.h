#ifndef SYSTEME_H
#define SYSTEME_H

#include <vector>
<<<<<<< HEAD
#include <string>
#include "Patient.h"
#include "ProfessionnelDeSante.h"
#include "DossierMedical.h"
#include "Administrateur.h"
#include "Consultation.h"
#include "Antecedent.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/** Classe Systeme : Gère l'ensemble des donnnées et opérations du système médical
    Fournit des méthodes pour ajouter, rechercher, modifier et permet de lancer une interfacce console de base
    + Sauvegarde et chargement des données
*/


class Systeme
{
    public:
        //Constructeur par défaut
        Systeme();

        // ----Gestion de l'authentification-----
        Utilisateur* authentifier(const std::string& username, const std::string& password);

        // ----Persistance des données ---
        void chargerDonnes();
        void sauvegarderDonnees() const;

        // ----Gestion des utilisateurs ---
        void ajouterAdministrateur(const Administrateur& admin);
        void ajouterProfessionnel(const ProfessionnelDeSante& pro);
        Administrateur* rechercherAdmin(const std::string& username);
        ProfessionnelDeSante* rechercherPro(const std::string& username);

        // ---Menu principal----
        void lancerMenu();

        // utilitaires internes
        int genererIdPatient();
        int genererIdConsultation();
        int genererIdAntecedent();

        void menuGestionUtilisateurs();
        void menuInscriptionPatient();
=======
#include <memory>
#include <string>

// --- DÃ©pendances des Classes Utilisateurs (Membres 3 & 4) ---
#include "Utilisateur.h"
#include "Patient.h"
#include "ProfessionnelSante.h"
#include "Administrateur.h"
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4

// --- DÃ©pendances des Classes MÃ©dicales (Membres 3 & 5) ---
#include "DossierMedical.h"
#include "Consultation.h"
#include "Prescription.h"
#include "Medicament.h"
#include "Antecedent.h"
#include "Examen.h"

<<<<<<< HEAD
    private:
        // Stockage centralisé
        std::vector<Administrateur> m_admins;
        std::vector<ProfessionnelDeSante> m_professionnels;

        // Identifiant généré auto
        int m_nextIdPatient, m_nextIdConsultation, m_nextIdAntecedent, m_nextIdPrescription;
        // Utilisateur actuellement connecté (pour la gestion des droits d'accès
        Utilisateur* m_utilisateurConnecte;
        // Chemin des fichiers de sauvegarde
        const std::string FICHIER_ADMINS = "datas/administrateurs.csv";
        const std::string FICHIER_PROFESSIONNELS = "datas/professionnels.csv";


        // Méthodes de sauvegarde privées (aide au chargement et à la sauvegarde des données)
        void chargerAdmins();
        void chargerProfessionnels();

        void sauvegarderAdmins() const;
        void sauvegarderProfessionnels() const;

=======
// --- DÃ©pendances Utilitaires (Commun) ---
#include "Date.h"

// #include "Specialite.h" // RetirÃ© car dÃ©jÃ  dans Enumeration.h via les autres fichiers
#include "Enumeration.h"

class Systeme {
private:
    // Attributs de gestion de l'Ã©tat du systÃ¨me
    // M4 : Gestion des utilisateurs (Utilise le polymorphisme grÃ¢ce Ã  unique_ptr)
    std::vector<std::unique_ptr<Utilisateur>> utilisateurs;
    // M3 : Gestion des dossiers (Utilise l'agrÃ©gation)
    std::vector<DossierMedical> dossiers;

    // Compteurs d'ID (Commun)
    int nextUserId;
    int nextDossierId;
    int nextConsultationId;
    int nextAntecedentId;

    // M4 : Utilisateur actuellement connectÃ©
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
    DossierMedical* trouverDossier(int idPatient); // Fonction utilitaire clÃ©
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
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4
};

#endif // SYSTEME_H
