#ifndef MENU_H
#define MENU_H

#include "Systeme.h"

struct Sys
{
    Systeme systeme;
};

class Menu
{
    public:
        Menu();
        void afficherMenuAdministrateur();
        void ajouterNouveauProfessionnel();
        void afouterNouvelAdministrateur();
        void supprimerAdmin();
        void supprimerPro();


    protected:

    private:
};

#endif // MENU_H
