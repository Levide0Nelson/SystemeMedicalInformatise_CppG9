#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include <memory> // Pour std::unique_ptr
#include "Date.h"
#include "Specialite.h"
#include "Prescription.h"

class Consultation {
private:
    int idConsultation;
    Date date;
    int idProfessionnel;
    int idPatient;
    Specialite specialite; // BONUS : Catégorisation par spécialité
    std::string motif;
    std::string observations;
    std::unique_ptr<Prescription> prescription; // BONUS : Gestion des prescriptions

public:
    // Constructeur complet
    Consultation(int id, const Date& d, int idPS, int idPat, Specialite s, const std::string& m, const std::string& obs)
        : idConsultation(id), date(d), idProfessionnel(idPS), idPatient(idPat), specialite(s), motif(m), observations(obs), prescription(nullptr) {}
    
    // Setter pour ajouter la prescription APRÈS la création de la consultation
    void setPrescription(std::unique_ptr<Prescription> p) { prescription = std::move(p); }
    
    // Getters essentiels pour les Statistiques (votre autre responsabilité)
    Date getDate() const { return date; }
    Specialite getSpecialite() const { return specialite; }
    int getIdProfessionnel() const { return idProfessionnel; }
    
    void afficher() const;
};

#endif // CONSULTATION_H