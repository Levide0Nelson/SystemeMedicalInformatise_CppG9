#include "../include/ProfessionnelSante.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

ProfessionnelDeSante::ProfessionnelDeSante(int idPro, const std::string& nomPro, const std::string& prenomPro, const std::string& loginPro,
                                           const std::string& mdpPro, const std::string& role, const std::string& specialite, const std::string& grade)
    : Utilisateur(idPro, nomPro, prenomPro, loginPro, mdpPro, role),
      m_specialite(specialite), m_grade(grade), m_disponibilite(24, true)
{
}

// Accesseurs
std::string ProfessionnelDeSante::getSpecialite() const { return m_specialite; }
std::string ProfessionnelDeSante::getGrade() const { return m_grade; }

// Mutateurs
void ProfessionnelDeSante::setSpecialite(const std::string& specialite) { m_specialite = specialite; }
void ProfessionnelDeSante::setGrade(const std::string& grade) { m_grade = grade; }

// Export CSV
std::string ProfessionnelDeSante::toCSV() const
{
    return std::to_string(m_idCompteUser) + ";" + m_nomUser + ";" + m_prenomUser + ";" + m_loginUser + ";" + m_motDePasseUser + ";" + m_roleUser + ";" + m_specialite + ";" + m_grade;
}

// Menu Spécifique
void ProfessionnelDeSante::afficherMenu() const
{
    std::cout << "\n===== Menu Professionnel de Sante (" << m_specialite << ") =====\n";
    std::cout << "1. Consulter la liste des patients\n";
    std::cout << "2. Rechercher un patient\n";
    std::cout << "3. Consulter un dossier medical\n";
    std::cout << "4. Creer une consultation\n";
    std::cout << "9. Deconnexion\n";
}
