#include "Prescription.h"
#include <iostream>

void Prescription::afficher() const {
    std::cout << "\n    --- PRESCRIPTION ---" << std::endl;
    std::cout << "    Instructions: " << instructions << std::endl;
    std::cout << "    Médicaments Prescrits:" << std::endl;
    if (medicaments.empty()) {
        std::cout << "    (Aucun médicament spécifié)" << std::endl;
    }
    for (const auto& m : medicaments) { m.afficher(); }
}