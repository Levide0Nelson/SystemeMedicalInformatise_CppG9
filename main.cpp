#include <iostream>
#include <string>
#include <limits>
#include "include/Systeme.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Juste pour afficher le titre du projet au début
void afficherBienvenue()
{
    #ifdef _WIN32
    SetConsoleOutputCP(65001); // Permet d'avoir les accents corrects sur Windows
    #endif
    cout << "\n";
    cout << "==========================================" << endl;
    cout << "     SYSTEME D'INFORMATION MEDICAL        " << endl;
    cout << "==========================================" << endl;
}

// Cette fonction gère la connexion (Login/Mot de passe)
// On laisse 3 chances à l'utilisateur avant de bloquer
Utilisateur* boucleAuthentification(Systeme& systeme)
{
    string login, password;
    Utilisateur* user = nullptr;
    int tentatives = 0;

    while (!user && tentatives < 3)
    {
        cout << "\n--- Connexion ---\n";
        cout << "Login : ";
        getline(cin, login); // On utilise getline pour permettre les espaces si besoin

        cout << "Mot de passe : ";
        getline(cin, password);

        // On demande au système de vérifier si ça existe
        user = systeme.authentifier(login, password);

        if (!user) {
            cout << "[ERREUR] Identifiants incorrects. Reessayez.\n";
            tentatives++;
        }
    }

    if (!user) cout << "[ECHEC] Trop de tentatives.\n";
    return user;
}

int main() {
    afficherBienvenue();

    // 1. On démarre le système et on charge les fichiers CSV
    Systeme systeme;
    systeme.chargerDonnes();

    bool running = true;
    while (running)
    {
        // Petit menu de démarrage
        cout << "\n1. Se connecter\n";
        cout << "2. Quitter\n";
        cout << "Votre choix : ";

        int choix;
        cin >> choix;

        // Vérification : Si l'utilisateur tape des lettres au lieu de chiffres
        if (cin.fail()) {
             cin.clear(); // On remet cin en marche
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // On vide l'erreur
             choix = 0;
        }
        cin.ignore(); // Important : on vide la mémoire tampon pour que les getline suivants marchent bien

        if (choix == 1) {
            // 2. On lance la connexion
            Utilisateur* user = boucleAuthentification(systeme);

            if (user) {

                cout << "\n[Succes] Bienvenue " << user->getNom() << " !\n";
                // 3. Si c'est bon, on lance le vrai menu principal (celui avec toutes les options)
                systeme.lancerMenu();
            }
        }
        else if (choix == 2) {
            // 4. Si on quitte, on pense à sauvegarder avant
            cout << "\n[Fermeture] Sauvegarde en cours...\n";
            systeme.sauvegarderDonnees();
            cout << "Au revoir !\n";
            running = false;
        }
        else {
            cout << "Choix invalide.\n";
        }
    }
    return 0;
}
