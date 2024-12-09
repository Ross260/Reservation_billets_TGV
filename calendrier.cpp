#include "Calendrier.h"

void Calendrier::ajouterHoraire(const std::string& date, const Train& train) {
    horaireTrain[date].push_back(train);
}

void Calendrier::afficherCalendrier(const std::string& dateDebut, const std::string& dateFin) {
    std::cout << "Calendrier des trains entre " << dateDebut << " et " << dateFin << " :\n";
    for (const auto& [date, trains] : horaireTrain) {
    if (date >= dateDebut && date <= dateFin) {
        std::cout << "Date : " << date << "\n";
        for (const auto& train : trains) {
            train.afficherInfosTrain();
        }
    }
}

}

void Calendrier::rechercherTrainsParDate(const std::string& date, const std::string& depart, const std::string& arrivee) {
    if (horaireTrain.find(date) != horaireTrain.end()) {
        for (const auto& train : horaireTrain[date]) {
            if (train.getVilleDepart() == depart && train.getVilleArrivee() == arrivee) {
                train.afficherInfosTrain();
            }
        }
    } else {
        std::cout << "Aucun train disponible pour la date " << date << ".\n";
    }
}

std::vector<Train> Calendrier::obtenirHoraires(const std::string& date) const {
    auto it = horaireTrain.find(date);
    if (it != horaireTrain.end()) {
        return it->second;
    }
    return {}; // Return an empty vector if no trains are found for the date
}
