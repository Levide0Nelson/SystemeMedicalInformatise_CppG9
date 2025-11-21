#include "Medicament.h"
#include <iostream>

void Medicament::afficher() const {
    std::cout << "    - " << nomCommercial << " (Actif: " << principeActif << ")" << std::endl;
}