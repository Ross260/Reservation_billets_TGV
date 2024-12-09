#include "Reservation.h"
#include <iostream>
#include <fstream>
Reservation::Reservation(int numero, const Passager& passager, const Billet& billet)
    : numeroReservation(numero), passager(passager), billet(billet) {}

void Reservation::afficherDetailsReservation() const {
    std::cout << "Reservation " << numeroReservation << " :" << std::endl;
    passager.afficherReservations();
    billet.afficherDetailsBillet();
}
void Reservation::recupererArchivesDepuisFichier(const std::string& cheminHistorique) {
    std::ifstream fichier(cheminHistorique);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier d'historique.\n";
        return;
    }

    std::string ligne;
    std::cout << "Archives des billets :\n";
    while (std::getline(fichier, ligne)) {
        std::cout << ligne << "\n";
    }

    fichier.close();
}
