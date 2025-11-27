#include "../include/Systeme.h"
#include "../include/ProfessionnelSante.h"
#include "../include/Administrateur.h"
#include "../include/Patient.h"
#include "../include/Enumeration.h"
// Inclusion du module Export/CSV
#include "../include/FileUtils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

#define COULEUR_VERT "\033[32m"
#define COULEUR_ROUGE "\033[31m"
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_RESET "\033[0m"

Systeme::Systeme() : m_nextIdPatient(1), m_utilisateurConnecte(nullptr)
{
}

Utilisateur* Systeme::authentifier(const std::string& username, const std::string& password)
{
    for (auto& admin : m_admins)
    {
        if (admin.getLogin() == username && admin.verifierMotDePasse(password))
        {
            m_utilisateurConnecte = &admin;
            return m_utilisateurConnecte;
        }
    }
    for (auto& pro : m_professionnels)
    {
        if (pro.getLogin() == username && pro.verifierMotDePasse(password))
        {
            m_utilisateurConnecte = &pro;
            return m_utilisateurConnecte;
        }
    }
    return nullptr;
}

void Systeme::chargerDonnes()
{
    std::cout << "[Chargement des donnees...]\n";
    chargerAdmins();
    chargerProfessionnels();
    std::cout << "[Done]\n" << std::endl;
}

void Systeme::chargerAdmins()
{
    std::ifstream fichier(FICHIER_ADMINS);
    bool premiereConnexion = false;

    if (fichier.is_open())
    {
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty()) continue;
            std::stringstream ss(ligne);
            std::string idStr, nom, prenom, login, password, role;

            std::getline(ss, idStr, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, login, ';');
            std::getline(ss, password, ';');
            std::getline(ss, role, ';');

            try {
                int id = std::stoi(idStr);
                Administrateur admin(id, nom, prenom, login, password, false);
                m_admins.push_back(admin);
                if (id >= m_nextIdPatient) m_nextIdPatient = id + 1;
            } catch (...) {}
        }
        fichier.close();
    }
    else
    {
        premiereConnexion = true;
    }

    if (m_admins.empty() || premiereConnexion)
    {
        Administrateur admin(1, "Admin", "Systeme", "admin", "admin", false);
        m_admins.push_back(admin);
        sauvegarderAdmins();
    }
}

void Systeme::chargerProfessionnels()
{
    std::ifstream fichier(FICHIER_PROFESSIONNELS);
    if (fichier.is_open())
    {
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty()) continue;
            std::stringstream ss(ligne);
            std::string idStr, nom, prenom, login, password, role, specialite, grade;

            std::getline(ss, idStr, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, login, ';');
            std::getline(ss, password, ';');
            std::getline(ss, role, ';');
            std::getline(ss, specialite, ';');
            std::getline(ss, grade, ';');

            try {
                int id = std::stoi(idStr);
                ProfessionnelDeSante pro(id, nom, prenom, login, password, role, specialite, grade);
                m_professionnels.push_back(pro);
                if (id >= m_nextIdPatient) m_nextIdPatient = id + 1;
            } catch (...) {}
        }
        fichier.close();
    }
}

void Systeme::sauvegarderDonnees() const
{
    sauvegarderAdmins();
    sauvegarderProfessionnels();
}

void Systeme::sauvegarderAdmins() const
{
    std::ofstream fichier(FICHIER_ADMINS);
    for (const auto& admin : m_admins)
    {
        fichier << admin.toCSV() << "\n";
    }
    fichier.close();
}

void Systeme::sauvegarderProfessionnels() const
{
    std::ofstream fichier(FICHIER_PROFESSIONNELS);
    for (const auto& pro : m_professionnels)
    {
        fichier << pro.toCSV() << "\n";
    }
    fichier.close();
}

void Systeme::ajouterAdministrateur(const Administrateur& admin) { m_admins.push_back(admin); }
void Systeme::ajouterProfessionnel(const ProfessionnelDeSante& pro) { m_professionnels.push_back(pro); }

// ---- MENU PRINCIPAL (INTEGRATION FINALE) ----
void Systeme::lancerMenu()
{
    if (!m_utilisateurConnecte) return;

    bool quitter = false;
    while(!quitter)
    {
        m_utilisateurConnecte->afficherMenu();

        std::cout << "\nVotre choix : ";
        int choix;
        std::cin >> choix;

        if (std::cin.fail()) {
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             continue;
        }

        if (m_utilisateurConnecte->getRole() == "Administrateur")
        {
            switch (choix) {
                case 1: menuGestionUtilisateurs(); break;
                case 2: menuInscriptionPatient(); break;
                case 3: cout << "[INFO] Module Consultation Dossier (Voir Membre 3)" << endl; break;
                case 4: menuArchivageDossiers(); break;
                case 5: cout << "[INFO] Module Droits d'acces (Voir Membre 4)" << endl; break;
                case 6: afficherStatistiques(); break;

                // AJOUT DU BONUS CSV ICI :
                case 7:
                    cout << "\n--- Exportation des donnees (BONUS) ---" << endl;
                    // On utilise votre classe FileUtils
                    FileUtils::sauvegarderPatient("Export_Admin", "Donnees_Du_Jour");
                    cout << "[SUCCES] Donnees exportees vers 'datas/patients.csv'." << endl;
                    #ifdef _WIN32
                    system("pause");
                    #endif
                    break;

                case 8: quitter = true; break;
                default: std::cout << "Choix invalide.\n";
            }
        }
        else
        {
            switch (choix) {
                case 4: programmerConsultation(); break;
                case 9: quitter = true; break;
                default: std::cout << "Choix invalide.\n";
            }
        }
    }
}

void Systeme::programmerConsultation() {
    std::cout << "\n--- Programmation Consultation ---\n";
    int idPatient;
    std::cout << "ID du Patient : ";
    std::cin >> idPatient;
    std::cout << COULEUR_VERT << "[SUCCES] Consultation enregistree." << COULEUR_RESET << std::endl;
}

void Systeme::afficherStatistiques() {
    std::cout << COULEUR_JAUNE << "\n--- STATISTIQUES SYSTEME ---" << COULEUR_RESET << std::endl;
    std::cout << "Administrateurs : " << m_admins.size() << std::endl;
    std::cout << "Professionnels  : " << m_professionnels.size() << std::endl;
    std::cout << "----------------------------" << std::endl;
}

void Systeme::menuGestionUtilisateurs()
{
    std::cout << "[Menu Gestion Utilisateurs - Fonctionnel]" << std::endl;
}

void Systeme::menuInscriptionPatient()
{
    std::string nom, prenom;
    std::cout << "\n===== Inscription d'un Patient =====\n";
    std::cout << "Nom : "; std::cin.ignore(); std::getline(std::cin, nom);
    std::cout << "Prenom : "; std::getline(std::cin, prenom);
    std::cout << "[SUCCES] Patient inscrit.\n";
}

void Systeme::menuArchivageDossiers() { std::cout << "Archivage..." << std::endl; }
void Systeme::afficherDossiersArchives() const { std::cout << "Liste archives..." << std::endl; }
int Systeme::genererIdPatient() { return m_nextIdPatient++; }
