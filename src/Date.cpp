#include "../include/Date.h"
#include <iostream>
#include <string>

using namespace std;

// Constructeur par défaut (Initialise à une date fixe pour éviter les bugs)
Date::Date() {
    jour = 1;
    mois = 1;
    annee = 2025;
}

// Constructeur avec paramètres (Celui utilisé par les Consultations)
Date::Date(int j, int m, int a) : jour(j), mois(m), annee(a) {
}

// Destructeur
Date::~Date() {
    // Rien à nettoyer pour l'instant
}

// Affiche la date au format JJ/MM/AAAA
void Date::afficher() const {
    cout << jour << "/" << mois << "/" << annee;
}

// Retourne la date en texte (utile pour les logs ou l'interface)
string Date::toString() const {
    return to_string(jour) + "/" + to_string(mois) + "/" + to_string(annee);
}
