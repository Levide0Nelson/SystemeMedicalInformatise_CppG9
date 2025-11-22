#include "Consultation.h"
#include <iostream>

void Consultation::afficher() const {
    std::cout << "\n--- Consultation #" << idConsultation << " ---" << std::endl;
    std::cout << "Date: ";
    date.afficher();
    std::cout << " | Spécialité: " << specialiteToString(specialite) << std::endl;
    std::cout << "Motif: " << motif << std::endl;
    std::cout << "Observations: " << observations << std::endl;

    // Affichage conditionnel de la prescription (Polymorphisme avec unique_ptr)
    if (prescription) {
        prescription->afficher();
    }
}
