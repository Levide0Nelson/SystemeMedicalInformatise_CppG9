#ifndef ENUMERATION_H_INCLUDED
#define ENUMERATION_H_INCLUDED

/** Fichier Enumeration : Enumère les Roles, Spécialités, types d'antécédent et les
    statuts possibles des consultations. Permettra une meilleure gestion des cas.
    Peut être modifié si vous le voulez.
*/

// Enumération pour les rôles utilisateurs du système

enum class Role
{
    PROFESSIONNEL,
    ADMINISTRATEUR
};

// Enumération des spécialités médicales possibles

enum class Specialite
{
    CARDIOLOGIE,
    DERMATOLOGIE,
    PNEUMOLOGIE,
    ORTHOPEDIE,
    OPHTAMOLOGIE,
    MEDECINE_GENERALE,
    PSYCHIATRIE,
    PEDIATRIE
};

// Enumeration pour les types d'antécédents médicaux à prendre en compte

enum class TypeAntecedent
{
    MALADIE_CHRONIQUE,
    ALLERGIE,
    INTERVENTION_CHIRURGICALE,
    TRAITEMENT_ANTERIEUR
};

// Enumération pour le statut des consultations
enum class StatutConsultation
{
    PROGRAMMEE,  // Consultation planifiée
    EN_COURS,   // Consultation en déroulement
    COMPLETEE,  // Consultation déroulée et documentée
    ANNULEE
};


#include <string>

// Fonction utilitaire pour convertir la spécialité en texte
inline std::string specialiteToString(Specialite s) {
    switch(s) {
        case Specialite::CARDIOLOGIE: return "Cardiologie";
        case Specialite::DERMATOLOGIE: return "Dermatologie";
        case Specialite::PNEUMOLOGIE: return "Pneumologie";
        case Specialite::ORTHOPEDIE: return "Orthopedie";
        case Specialite::OPHTAMOLOGIE: return "Ophtalmologie";
        case Specialite::MEDECINE_GENERALE: return "Medecine Generale";
        case Specialite::PSYCHIATRIE: return "Psychiatrie";
        case Specialite::PEDIATRIE: return "Pediatrie";
        default: return "Inconnu";
    }
}

#endif // ENUMERATION_H_INCLUDED
