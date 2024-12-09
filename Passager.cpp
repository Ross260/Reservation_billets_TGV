#include "Passager.h"
#include <iostream>
#include <algorithm> // Pour std::remove
#include <fstream>

Passager::Passager(const std::string& nom, const std::string& prenom, int id)
    : nom(nom), prenom(prenom), identifiant(id) {}

void Passager::ajouterReservation(const Billet& billet) {
    reservations.push_back(billet);
}

void Passager::supprimerReservation(const Billet& billet) {
    auto it = std::remove(reservations.begin(), reservations.end(), billet);
    if (it != reservations.end()) {
        reservations.erase(it, reservations.end());
        std::cout << "Reservation supprimee.\n";
    } else {
        std::cout << "Reservation non trouvee.\n";
    }
}

void Passager::ajouterHistorique(const Billet& billet) {
    historiqueReservations.push_back(billet);
}

void Passager::afficherReservations() const {
    if (reservations.empty()) {
        std::cout << "Aucune reservation.\n";
        return;
    }

    for (const auto& billet : reservations) {
        billet.afficherDetailsBillet();
    }
}

void Passager::afficherHistorique() const {
    if (historiqueReservations.empty()) {
        std::cout << "Aucun billet dans l'historique.\n";
        return;
    }

    for (const auto& billet : historiqueReservations) {
        billet.afficherDetailsBillet();
    }
}

void Passager::afficherHistoriqueDepuisFichier(const std::string& cheminHistorique) const {
    std::ifstream fichier(cheminHistorique);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier d'historique.\n";
        return;
    }

    std::string ligne;
    bool trouve = false;

    std::cout << "Historique des billets pour " << nom << " " << prenom << " (ID: " << identifiant << "):\n";
    while (std::getline(fichier, ligne)) {
        // V�rifier si la ligne contient le nom et pr�nom du passager
        if (ligne.find(nom + " " + prenom) != std::string::npos) {
            std::cout << ligne << "\n";
            trouve = true;
        }
    }

    if (!trouve) {
        std::cout << "Aucun billet trouve dans l'historique pour ce passager.\n";
    }

    fichier.close();
}
