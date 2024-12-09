#include "Train.h"

Train::Train(int numero, const std::string& depart, const std::string& arrivee,
             const std::string& hDepart, const std::string& hArrivee, int capacite)
    : numeroTrain(numero), villeDepart(depart), villeArrivee(arrivee),
      horaireDepart(hDepart), horaireArrivee(hArrivee), capacite(capacite), placesLibres(capacite) {}

bool Train::verifierDisponibilite() const {
    return placesLibres > 0;
}

void Train::reserverPlace() {
    if (placesLibres > 0) {
        placesLibres--;
    } else {
        std::cerr << "Erreur : aucune place disponible pour le train " << numeroTrain << " !\n";
    }
}

void Train::annulerReservation() {
    if (placesLibres < capacite) {
        placesLibres++;
    } else {
        std::cerr << "Erreur : toutes les places sont deja disponibles pour le train " << numeroTrain << " !\n";
    }
}

void Train::afficherInfosTrain() const {
    std::cout << "Train " << numeroTrain
              << " | " << villeDepart << " -> " << villeArrivee
              << " | Depart : " << horaireDepart
              << " | Arrivee : " << horaireArrivee
              << " | Places libres : " << placesLibres << " / " << capacite << "\n";
}
