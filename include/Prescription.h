#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include <vector>
#include <string>
#include <memory>
#include "Medicament.h"

class Prescription {
private:
    std::vector<Medicament> medicaments; // Agrégation de Medicament
    std::string instructions; // Posologie
public:
    Prescription(const std::string& instr) : instructions(instr) {}
    void ajouterMedicament(const Medicament& m) { medicaments.push_back(m); }
    void afficher() const;
    // Ajout d'une fonction utilitaire pour les statistiques
    int getNombreMedicaments() const { return medicaments.size(); }
};
#endif // PRESCRIPTION_H