#ifndef SYSTEME_H
#define SYSTEME_H

#include <vector>
#include <string>
#include "Administrateur.h"
#include "ProfessionnelSante.h" // Nom de fichier corrigé
#include "Patient.h"
#include "DossierMedical.h"
#include "Consultation.h"
#include "Antecedent.h"

// Chemins des fichiers
const std::string FICHIER_ADMINS = "datas/administrateur.csv";
const std::string FICHIER_PROFESSIONNELS = "datas/professionnelSante.csv";

class Systeme
{
    public:
        Systeme();

        // Authentification
        Utilisateur* authentifier(const std::string& username, const std::string& password);

        // Persistance
        void chargerDonnes();
        void sauvegarderDonnees() const;

        // Gestion Utilisateurs
        void ajouterAdministrateur(const Administrateur& admin);
        void ajouterProfessionnel(const ProfessionnelDeSante& pro);

        // Menu Principal (Votre partie)
        void lancerMenu();

        // Utilitaires & Menus internes
        int genererIdPatient();
        void menuGestionUtilisateurs();
        void menuInscriptionPatient();

        //
        void menuArchivageDossiers();

        // Fonctions métier
        void programmerConsultation();
        void afficherStatistiques();
        void afficherDossiersArchives() const;

    private:
        // Stockage centralisé
        std::vector<Administrateur> m_admins;
        std::vector<ProfessionnelDeSante> m_professionnels;
        Utilisateur* m_utilisateurConnecte;

        int m_nextIdPatient;
        int m_nextIdConsultation;
        int m_nextIdAntecedent;

        // Méthodes internes
        void chargerAdmins();
        void chargerProfessionnels();
        void sauvegarderAdmins() const;
        void sauvegarderProfessionnels() const;
};

#endif // SYSTEME_H
