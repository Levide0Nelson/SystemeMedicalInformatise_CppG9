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

#endif // ENUMERATION_H_INCLUDED
