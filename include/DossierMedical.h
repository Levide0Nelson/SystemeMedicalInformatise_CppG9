#endif DOSSIERMEDICAL_H
#ifndef DOSSIERMEDICAL_H
#define DOSSIERMEDICAL_H

#include <vector>
#include <string>
#include <iostream>
#include "Antecedent.h"
using namespace std;

class DossierMedical {
private:
    int idDossier;
    string dateCreation;
    bool archive;
    vector<Antecedent> antecedents;

public:
    DossierMedical(int id, string dateC)
        : idDossier(id), dateCreation(dateC), archive(false) {}

    void ajouterAntecedent(const Antecedent& a) {
        antecedents.push_back(a);
    }

    void archiver() {
        archive = true;
    }

    bool estArchive() const {
        return archive;
    }

    void afficher() const {
        cout << "=== DOSSIER MEDICAL ===" << endl;
        cout << "ID dossier : " << idDossier << endl;
        cout << "Date de création : " << dateCreation << endl;
        cout << "Statut : " << (archive ? "ARCHIVÉ" : "ACTIF") << endl;

        cout << "\n--- Antécédents ---" << endl;
        for (const auto& a : antecedents) {
            a.afficher();
            cout << endl;
        }
    }
};

#endif
