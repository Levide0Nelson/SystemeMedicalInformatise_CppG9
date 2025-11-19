/**
 * @file main.cpp
 * @brief Point d'entrée de l'application Medipass
 * @author Membre 6 (Interface & Intégration)
 */

#include <iostream>
#include <limits>
#include <cstdlib>

// Inclusion des headers (Note l'espace pour ProfessionnelSante .h)
#include "include/Patient.h"
#include "include/ProfessionnelSante .h"
#include "include/Consultation.h"
#include "include/Statistiques.h"
#include "include/Administrateur.h"
#include "include/FileUtils.h"

using namespace std;

void nettoyerConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void afficherMenuPrincipal() {
    nettoyerConsole();
    cout << "========================================" << endl;
    cout << "     SYSTEME DE GESTION MEDIPASS        " << endl;
    cout << "========================================" << endl;
    cout << "   1. Gerer les patients" << endl;
    cout << "   2. Gerer les professionnels de sante" << endl;
    cout << "   3. Gerer les consultations" << endl;
    cout << "   4. Voir les statistiques" << endl;
    cout << "   5. Administration" << endl;
    cout << "   9. Quitter" << endl;
    cout << endl;
    cout << "Votre choix : ";
}

int main() {
    int choix = 0;

    // Pour l'instant, on ne déclare que Patient pour tester le menu 1
    Patient gestionPatient;

    // Les autres sont commentés pour éviter les erreurs tant qu'ils sont vides
    // ProfessionnelSante gestionPro;
    // Consultation gestionConsult;
    // Statistiques gestionStats;
    // Administrateur gestionAdmin;

    do {
        afficherMenuPrincipal();
        cin >> choix;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choix = 0;
            continue;
        }

        switch (choix) {
            case 1:
                // Test du bonus CSV
                FileUtils::sauvegarderPatient("Test", "Integration");

                // Appel du menu patient (Il faut modifier Patient.cpp pour que ça marche !)
                // gestionPatient.menuGestionPatient();
                cout << " [OK] Menu Patient detecte. (Fonction a activer)" << endl;
                #ifdef _WIN32
                system("pause");
                #endif
                break;

            case 2:
                cout << "Menu Pro en construction..." << endl;
                #ifdef _WIN32
                system("pause");
                #endif
                break;

            case 9:
                cout << "Au revoir !" << endl;
                break;

            default:
                cout << "Choix non valide." << endl;
                #ifdef _WIN32
                system("pause");
                #endif
                break;
        }
    } while (choix != 9);

    return 0;
}
