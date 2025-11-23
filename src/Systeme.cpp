<<<<<<< HEAD
#include "Systeme.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

Systeme::Systeme() : m_nextIdPatient(1),/* m_nextIdConsultation(1), m_nextIdAntecedent(1),*/ m_utilisateurConnecte(nullptr)
{

}

// ----Gestion de l'authentification-----
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

        // ----Persistance des donnÈes ---
void Systeme::chargerDonnes()
{
    std::cout << "[Chargement des donnÈes des administrateurs ...]\n";
    chargerAdmins();
    std::cout << "[Chargement des donnÈes des professionnels de santÈ...]\n";
    chargerProfessionnels();
    std::cout << "[SUCCES DU CHARGEMENT] Toutes les donnÈes ont ÈtÈ chargÈes.\n" << std::endl;
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
            if (ligne.empty())
                continue;
            std::stringstream ss(ligne);
            std::string idStr, nom, prenom, login, password, role;

            std::getline(ss, idStr, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, login, ';');
            std::getline(ss, password, ';');
            std::getline(ss, role, ';');

            int id = std::stoi(idStr);
            Administrateur admin(id,nom,prenom,login, password, false);
            m_admins.push_back(admin);

            // Mise ‡ jour du prochain ID
            if (id >= m_nextIdPatient)
                m_nextIdPatient = id +1;
        }
        fichier.close();
        std::cout << "[OK] " << m_admins.size() << " administrateur(s) chargÈ(s).\n";
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier admins.csv non trouvÈ. CrÈation nouvelle base de sauvegarde.\n" << std::endl;
        premiereConnexion = true;
    }

    if (m_admins.empty() || premiereConnexion)
    {
        std::cout << "[INFO] CrÈation du premier administrateur systËme requis.\n";
        std::string nom, prenom, login, password;
        std::cout << "Nom : ";
        std::getline(std::cin, nom);
        std::cout << "PrÈnom : ";
        std::getline(std::cin, prenom);
        std::cout << "Login/Username : ";
        std::getline(std::cin, login);
        std::cout << "Password : ";
        std::getline(std::cin, password);

        Administrateur admin(m_nextIdPatient++, nom, prenom, login, password);
        m_admins.push_back(admin);
        std::cout << "[SUCCES] Premier administrateur crÈÈ.\n";
        std::cout << "Bienvenu sur le systËme.\n";

        // Sauvegarde automatique :
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
            if (ligne.empty())
                continue;
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

            int id = std::stoi(idStr);
            ProfessionnelSante pro(id, nom, prenom, login, password, role, specialite, grade);
            m_professionnels.push_back(pro);

            if (id >= m_nextIdPatient)
                m_nextIdPatient = id +1;
        }
        fichier.close();
        std::cout << "[OK] " << m_professionnels.size() << " professionnel(s) de santÈ chargÈ(s).\n";
    }
    else
        std::cout << "[ATTENTION !] Fichier professionnels.csv non trouvÈ.\n" << std::endl;
}


void Systeme::sauvegarderDonnees() const
{
    std::cout << "[Sauvegarde des donnÈes...]\n";
    sauvegarderAdmins();
    sauvegarderProfessionnels();
    std::cout << "[SUCCES] Toutes les donnÈes ont ÈtÈ sauvegardÈes.\n";
}

void Systeme::sauvegarderAdmins() const
{
    std::ofstream fichier(FICHIER_ADMINS);
    for (const auto& admin : m_admins)
    {
        fichier << admin.toCSV() << "\n";
    }
    fichier.close();
    std::cout << "[OK] Admins sauvegardÈs.\n" << std::endl;
}
void Systeme::sauvegarderProfessionnels() const
{
    std::ofstream fichier(FICHIER_PROFESSIONNELS);
    for (const auto& pro : m_professionnels)
    {
        fichier << pro.toCSV() << "\n";
    }
    fichier.close();
    std::cout << "[OK] Professionnels de santÈ sauvegardÈs.\n" << std::endl;
}


        // ----Gestion des utilisateurs ---
void Systeme::ajouterAdministrateur(const Administrateur& admin)
{
    m_admins.push_back(admin);
}
void Systeme::ajouterProfessionnel(const ProfessionnelSante& pro)
{
    m_professionnels.push_back(pro);
}
Administrateur* Systeme::rechercherAdmin(const std::string& username)
{
    for (auto& admin : m_admins)
        if (admin.getLogin() == username)
            return &admin;
    return nullptr;
}
ProfessionnelSante* Systeme::rechercherPro(const std::string& username)
{
    for (auto& pro : m_professionnels)
        if (pro.getLogin() == username)
            return &pro;
    return nullptr;
}



        // ----Affichage des stats
void Systeme::afficherStatistiques() const
{
    //std::cout << "Nombre de patients : " << m_patients.size() << std::endl;
    std::cout << "Nombre de professionnels : " << m_professionnels.size() << std::endl;
    std::cout << "Nombre d'administrateurs : " << m_admins.size() << std::endl;
    int nbConsult = 0, nbAnt = 0;

    /*for (const auto& dossier : m_dossiers)
    {
        nbConsult += dossier.getConsultations().size();
        nbAnt += dossier.getAntecedents().size();
    }
    std::cout << "Nombre total de consultations : " << nbConsult << std::endl;
    std::cout << "Nombre total d'antÈcÈdents : " << nbAnt << std::endl;*/
}

        // ---Menu principal----
void Systeme::lancerMenu()
{
    if (!m_utilisateurConnecte)
    {
        std::cout << "Aucun utilisateur authentifiÈ. Veuillez vous connecter.\n";
        return;
    }

    bool quitter = false;

    while(!quitter)
    {
        m_utilisateurConnecte -> afficherMenu();
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] EntrÈe invalide, veuillez entrer un chiffre." << std::endl;
            continue;
        }
        std::cin.ignore();

        // Dispatcing des fonctions mÈtiers selon le rÙle/menu
        if (m_utilisateurConnecte -> getRole() == "Administrateur")
        {
            switch (choix)
            {
                case 1 :
                    menuGestionUtilisateurs();
                    break;
                case 2 : // Inscription patient
                    menuInscriptionPatient();
                    break;
                case 3:
                    //menuConsultationDossier();
                    break;
                case 4 :
                    //menuArchivageDossiers();
                    break;
                case 5 :
                    afficherDossiersArchives();
                    break;
                case 6 :
                    afficherStatistiques();
                    break;
                case 8 :
                    quitter = true;
                    std::cout << "DÈconnexion administrateur...\n";
                    break;
                default:
                    std::cout << "[ERREUR] Choix invalide.\n";
                    break;
            }
        }
        else
        {
            switch (choix)
            {
                case 1 :
                    //afficherTousPatients();
                case 2 :
                    //menuRechercherPatient();
                    break;
                case 3 :
                    //menuConsultationDossier();
                    break;
                case 4:
                    //menuCreerConsultation();
                    break;
                case 5:
                    //menuAjouterAntecedent();
                    break;
                case 7 :
                    //menuAjouterPrescriptions();
                    break;
                case 9 :
                    quitter = true;
                    std::cout << "DÈconnexion professionnel...\n";
                    break;
                default :
                    std::cout << "[ERREUR] Choix invalide.\n";
                    break;
            }
        }
    }
}

        // utilitaires internes
int Systeme::genererIdPatient()
{
    return m_nextIdPatient++;
}
int Systeme::genererIdConsultation()
{
    return m_nextIdConsultation++;
}
int Systeme::genererIdAntecedent()
{
    m_nextIdAntecedent++;
}

    // Menu administrateur
void Systeme::menuGestionUtilisateurs()
{
    bool sortir = false;

    while (!sortir)
    {
        std::cout << "\n==== Gestion des Utilisateurs ====\n";
        std::cout << "1. CrÈer un administrateur\n";
        std::cout << "2. CrÈer un professionnel de santÈ\n";
        std::cout << "3. Lister tous les utilisateurs\n";
        std::cout << "4. Retour au menu principal\n";
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;
        std::cin.ignore();

        switch (choix)
        {
            case 1 :
            {
                std::string nom, prenom, login, password;
                std::cout << "Nom du nouvel Administrateur : ";
                std::getline(std::cin, nom);
                std::cout << "PrÈnom du nouvel Administatrateur : ";
                std::getline(std::cin, prenom);
                std::cout << "Username/Login : ";
                std::getline(std::cin, login);
                std::cout << "Password : ";
                std::getline(std::cin, password);

                Administrateur admin(genererIdPatient(), nom, prenom, login, password, false);
                ajouterAdministrateur(admin);
                std::cout << "[SUCCES] Nouvel Administrateur crÈÈ.\n";
                sauvegarderAdmins();
                break;
            }

            case 2:
                {
                    std::string nom, prenom, login, password, role, specialite, grade;
                    std::cout << "Nom : ";
                    std::getline(std::cin, nom);
                    std::cout << "PrÈnom : ";
                    std::getline(std::cin, prenom);
                    std::cout << "Username : ";
                    std::getline(std::cin, login);
                    std::cout << "Password : ";
                    std::getline(std::cin, password);
                    std::cout << "RÙle (medecin/infirmier/pharmacien) : "; std::getline(std::cin, role);
                    std::cout << "SpÈcialitÈ : ";
                    std::getline(std::cin, specialite);
                    std::cout << "Grade : ";
                    std::getline(std::cin, grade);

                    ProfessionnelSante pro(genererIdPatient(), nom, prenom, login, password, role, specialite, grade);
                    ajouterProfessionnel(pro);
                    std::cout << "[SUCCES] Nouveau Professionnel crÈÈ.\n";
                    sauvegarderProfessionnels();
                    break;
                }
            case 3:
                {
                    std::cout << "\n\t---- Administrateur ----\n";
                    for (const auto& admin : m_admins)
                    {
                        std::cout << "ID : " << admin.getIdUser() << " | " << admin.getNom() << " " << admin.getPrenom() << " ("
                                  << admin.getLogin() << ")\n";
                    }

                    std::cout << "\n\t---- Professionnel de SantÈ ----\n";
                    for (const auto& pro : m_professionnels)
                    {
                        std::cout << "ID : " << pro.getIdUser() << " | " << pro.getNom() << " " << pro.getPrenom() << " | RÙle : "
                                  << pro.getRole() << " | SpÈcialitÈ : " << pro.getSpecialite() << "\n";
                    }
                    break;
                }
            case 4 :
                {
                    sortir = true;
                    break;
                }
            default :
                std::cout << "[ERREUR] Choix invalide.\n";
        }
    }
}
// Menu administrateur : Inscription d'un patient
void Systeme::menuInscriptionPatient()
{
    std::string nom, prenom, dateNaissance, genre, adresse, telephone, email;
    std::cout << "\n===== Inscription d'un Patient =====\n";
    std::cout << "Nom : ";
    std::getline(std::cin, nom);
    std::cout << "PrÈnom : ";
    std::getline(std::cin, prenom);
    std::cout << "Date de naissance (YYYY-MM-DD) : ";
    std::getline(std::cin, dateNaissance);
    std::cout << "Genre (M/F/A) : ";
    std::getline(std::cin, genre);
    std::cout << "Adresse : ";
    std::getline(std::cin, adresse);
    std::cout << "TÈlÈphone : ";
    std::getline(std::cin, telephone);
    std::cout << "Email : ";
    std::getline(std::cin, email);

    int idPatient = m_nextIdPatient++;

    Patient patient(idPatient, nom, prenom, dateNaissance, genre, adresse, telephone, email);
    creerPatient(patient);
    std::cout << "[SUCCES] Patient inscrit.\n ID du nouveau patient: " << idPatient << "\n";
}


void Systeme::menuArchivageDossiers()
{
    std::cout << "\n===== Archivage d'un dossier patient =====\n";
    int idPatient;
    std::cout << "Entrer l'ID du patient ‡ archiver : ";
    std::cin >> idPatient;
    std::cin.ignore();
    DossierMedical* dossier = rechercherDossier(idPatient);

    if (!dossier)
    {
        std::cout << "[ERREUR] Dossier non trouvÈ !\n";
        return;
    }
    if (dossier -> estArchive())
    {
        std::cout << "[INFO] Ce dossier est dÈj‡ archivÈ.\n";
        return;
    }
    dossier->setArchive(true);
    std::cout << "[SUCCES] Dossier du patient #" << idPatient << " archivÈ.\n";
}

void Systeme::afficherDossiersArchives() const
{
    std::cout << "\n===== Dossiers archivÈs =====\n";
    for (const auto& dossier : m_dossiers)
    {
        if (dossier.estArchive())
        {
            std::cout << "Patient #" << dossier.getIdPatient() << "\n";
            dossier.afficherResumeDossier();
            std::cout << "--------------------------\n" << std::endl;
        }
    }
=======
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

// --- D√âFINITION DES COULEURS ---
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
    // Le destructeur par d√©faut g√®re la m√©moire
}

DossierMedical* Systeme::trouverDossier(int idPatient) {
    // Impl√©mentation du Membre 3 (En attente)
    return nullptr;
}

void Systeme::creerUtilisateursInitiaux() {
    // Impl√©mentation du Membre 4 (En attente)
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
    // NOTE : Code d√©sactiv√© car la classe ProfessionnelSante n'est pas encore finie par le Membre 4.
    /*
    if (!dynamic_cast<ProfessionnelSante*>(utilisateurActuel)) {
        cout << COULEUR_ROUGE << "Erreur : Seul un Professionnel de Sant√© peut programmer une consultation." << COULEUR_RESET << endl;
        return;
    }
    */

    int idPatient;
    string motif, observations;

    cout << "\nID du Patient concerne: ";
    if (!(cin >> idPatient)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    cout << "[INFO] Simulation: Consultation en cours de creation..." << endl;

    // NOTE : La suite d√©pend du Membre 3 (DossierMedical). On met en pause pour que √ßa compile.
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

    // Maps pour la Cat√©gorisation
    map<Specialite, int> consultationsParSpecialite;
    map<int, int> consultationsParPS;

    // NOTE : Boucles comment√©es car Utilisateur.h et DossierMedical.h sont encore vides.
    // D√©commentez ceci quand vos coll√®gues auront fini leurs classes.
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
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4
}
