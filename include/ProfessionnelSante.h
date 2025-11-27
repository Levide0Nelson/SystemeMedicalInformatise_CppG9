#ifndef PROFESSIONNELSANTE_H
#define PROFESSIONNELSANTE_H

#include "Utilisateur.h"
#include <string>
#include <vector>

class ProfessionnelDeSante : public Utilisateur
{
    public:
        // Constructeur
        ProfessionnelDeSante(int idPro, const std::string& nomPro, const std::string& prenomPro, const std::string& loginPro,
                             const std::string& mdpPro, const std::string& role, const std::string& specialite, const std::string& grade);

        ~ProfessionnelDeSante() = default;

        // Accesseurs
        std::string getSpecialite() const;
        std::string getGrade() const;

        // Mutateurs
        void setSpecialite(const std::string& specialite);
        void setGrade(const std::string& grade);

        // Méthodes d'export
        std::string toCSV() const override;
        void afficherMenu() const override;

    private:
        std::string m_specialite;
        std::string m_grade;
        std::vector<bool> m_disponibilite;
};

#endif // PROFESSIONNELSANTE_H
