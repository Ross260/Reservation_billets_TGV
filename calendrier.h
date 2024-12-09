#ifndef CALENDRIER_H
#define CALENDRIER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Train.h"

class Calendrier {
private:
    std::map<std::string, std::vector<Train>> horaireTrain;

public:
    void ajouterHoraire(const std::string& date, const Train& train);
    void afficherCalendrier(const std::string& dateDebut, const std::string& dateFin);
    void rechercherTrainsParDate(const std::string& date, const std::string& depart, const std::string& arrivee);
    std::vector<Train> obtenirHoraires(const std::string& date) const; // New Method
};

#endif
