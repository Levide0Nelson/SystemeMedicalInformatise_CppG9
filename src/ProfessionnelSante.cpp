#include "ProfessionnelSante.h"
<<<<<<< HEAD:src/ProfessionnelSante .cpp
#include "Utilisateur.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
=======
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4:src/ProfessionnelSante.cpp

ProfessionnelSante::ProfessionnelSante(int idPro, const std::string& nomPro, const std::string& prenomPro,const std::string& loginPro,
                             const std::string& mdpPro,const std::string& role,const std::string& specialite, const std::string& grade) :
                                 Utilisateur(idPro,nomPro,prenomPro,loginPro,mdpPro, role), m_specialite(specialite), m_grade(grade), m_disponibilite(24, true)
{

}


        // Accesseurs
std::string ProfessionnelSante::getSpecialite() const
{
    return m_specialite;
}
std::string ProfessionnelSante::getGrade() const
{
    return m_grade;
}

        // Mutateurs
void ProfessionnelSante::setSpecialite(const std::string& specialite)
{
    m_specialite = specialite;
}
void ProfessionnelSante::setGrade(const std::string& grade)
{
    m_grade = grade;
}

std::string ProfessionnelSante::toCSV() const
{
    return std::to_string(m_idCompteUser) + ";" + m_nomUser + ";" + m_prenomUser + ";" + m_loginUser + ";" + m_motDePasseUser + ";" + m_roleUser + ";" + m_specialite + ";" + m_grade ;
}
void ProfessionnelSante::afficherMenu() const
{
    std::cout << "\n===== Menu Professionnel de Santé (" << m_specialite << ") =====\n";
    std::cout << "1. Consulter la liste des patients\n";
    std::cout << "2. Rechercher un patient\n";
    std::cout << "3. Consulter un dossier médical\n";
    std::cout << "4. Créer une consultation\n";
    std::cout << "5. Ajouter/modifier un antécédent\n";
    std::cout << "6. Mon agenda (consultations à venir)\n";
    std::cout << "7. Prescrire un examen ou médicament\n";
    std::cout << "8. Générer un rapport de consultation\n";
    std::cout << "9. Déconnexion\n";
}

