<<<<<<< HEAD:include/ProfessionnelSante .h
#ifndef PROFESSIONNELDESANTE_H
#define PROFESSIONNELDESANTE_H

#include "Utilisateur.h"
#include "Patient.h"
#include "../Enumeration.h"
#include <vector>
#include <string>
=======
#ifndef PROFESSIONNELSANTE_H
#define PROFESSIONNELSANTE_H
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4:include/ProfessionnelSante.h

/** Classe ProfessionnelDeSante : Représente un professionnel de santé (médecin, infirmier, pharmacien, etc...)
    Permissions dans le système : Peut consulteer et créer des consultations pour les patients
*/

class ProfessionnelDeSante : public Utilisateur
{
    public:
        // Constructeur
        ProfessionnelDeSante(int idPro, const std::string& nomPro, const std::string& prenomPro,const std::string& loginPro,
                             const std::string& mdpPro,const std::string& role,const std::string& specialite, const std::string& grade);
        // Destructeur (par défaut celui de la classe Utilisateur
        ~ProfessionnelDeSante() = default;

        // Accesseurs
        std::string getSpecialite() const;
        std::string getGrade() const;

        // Mutateurs
        void setSpecialite(const std::string& specialite);
        void setGrade(const std::string& grade);

        /**Méthodes à implémenter*/
        //void consulterPatients(const std::vector<Patient>& patients) const;

        //const Patient* rechercherPatient(const std::vector<Patient> & patients, const std::string& critere) const;
        //void consulterDossierMedical(const DossierMedical& dossier) const;
        //void creerConsultation(DossierMedical& dossier);
        //void modifierAntecedent(DossierMedical& dossier);
        //void afficherAgenda(const std::vector<Consultation>& toutesConsultations) const;
        //void prescrire(DossierMedical& dossier);
        //void genererRapportConsultation(const DossierMedical& dossier) const;

        std::string toCSV() const override;
        void afficherMenu() const override;


    protected:

    private:
        std::string m_specialite;
        std::string m_grade;
        std::vector<bool> m_disponibilite;
};

<<<<<<< HEAD:include/ProfessionnelSante .h
#endif // PROFESSIONNELDESANTE_H
=======
#endif // PROFESSIONNELSANTE_H
>>>>>>> f4ecac3b7190474b50fbcf38405a2c49c4bc29c4:include/ProfessionnelSante.h
