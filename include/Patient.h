#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include "DossierMedical.h"
using namespace std;

class Patient {
private:
    int idPatient;
    string nom;
    string prenom;
    string dateNaissance;
    string contact;
    DossierMedical dossier;

public:
    Patient(int id, string n, string p, string dn, string c)
        : idPatient(id), nom(n), prenom(p),
          dateNaissance(dn), contact(c),
          dossier(id, dn) // Le dossier médical est lié au patient
          {}

    int getId() const { return idPatient; }

    void modifierInfos(string n, string p, string dn, string c) {
        nom = n;
        prenom = p;
        dateNaissance = dn;
        contact = c;
    }

    void ajouterAntecedent(const Antecedent& a) {
        dossier.ajouterAntecedent(a);
    }

    void afficherInfos() const {
        cout << "=== PATIENT ===" << endl;
        cout << "ID : " << idPatient << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prenom : " << prenom << endl;
        cout << "Date de naissance : " << dateNaissance << endl;
        cout << "Contact : " << contact << endl;
    }

    void afficherDossier() const {
        dossier.afficher();
    }
};

#endif

