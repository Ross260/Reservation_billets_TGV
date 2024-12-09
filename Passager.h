#ifndef PASSAGER_H
#define PASSAGER_H

#include <string>
#include <vector>
#include "Billet.h"

class Passager {
    private:
        std::string nom;
        std::string prenom;
        int identifiant;
        std::vector<Billet> reservations; // Reservations actuelles   
        std::vector<Billet> historiqueReservations; // Historique des billets

    public:
        // Constructeur
        Passager(const std::string& nom, const std::string& prenom, int id);

        // Getters
        const std::string& getNom() const { return nom; }
        const std::string& getPrenom() const { return prenom; }
        int getIdentifiant() const { return identifiant; }
        const std::vector<Billet>& getReservations() const { return reservations; }
        const std::vector<Billet>& getHistorique() const { return historiqueReservations; }

        // Methodes
        void ajouterReservation(const Billet& billet);
        void supprimerReservation(const Billet& billet);
        void ajouterHistorique(const Billet& billet);
        void afficherReservations() const;
        void afficherHistorique() const;
        void afficherHistoriqueDepuisFichier(const std::string& cheminHistorique) const;

};

#endif
