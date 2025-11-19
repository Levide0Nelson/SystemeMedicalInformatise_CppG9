#include "../include/FileUtils.h"
#include <fstream>
#include <iostream>

using namespace std;

void FileUtils::sauvegarderPatient(string nom, string prenom) {
    // Sauvegarde dans le dossier datas du projet
    ofstream fichier("datas/patients.csv", ios::app);

    if (fichier.is_open()) {
        fichier << nom << ";" << prenom << endl;
        cout << "[SUCCES] Donnee exportee vers datas/patients.csv" << endl;
        fichier.close();
    } else {
        cerr << "[ERREUR] Impossible d'ouvrir datas/patients.csv" << endl;
    }
}
