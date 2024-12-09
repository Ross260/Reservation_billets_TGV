#include "Billet.h"
#include <iostream>
#include <unordered_map>

// Constructeur
Billet::Billet(int numero, const std::string& type, double prix, int train, const std::string& date)
    : numeroBillet(numero), typeClasse(type), prix(prix), numeroTrain(train), dateVoyage(date) {}

// Methode pour afficher les details du billet
void Billet::afficherDetailsBillet() const {
    std::cout << "Billet " << numeroBillet << " | Classe : " << typeClasse
              << " | Prix : " << prix << " Euros | Train : " << numeroTrain
              << " | Date : " << dateVoyage << std::endl;
}

// Methode pour calculer le prix d'un billet
double Billet::calculerPrix(const std::string& villeDepart, const std::string& villeArrivee, const std::string& typeClasse) {
    // Simuler les distances entre les villes
    std::unordered_map<std::string, double> distances = {
        {"Paris-Lyon", 500.0},
        {"Lyon-Marseille", 300.0},
        {"Paris-Marseille", 800.0},
        {"Bordeaux-Toulouse", 250.0},
        {"Paris-Bordeaux", 600.0},
        {"Lille-Bordeaux", 1000.0},
        {"Nice-Lyon", 700.0},
        {"Strasbourg-Lille", 400.0},
        {"Nantes-Marseille", 800.0},
        {"Lyon-Nice", 600.0},
        {"Toulouse-Paris", 1200.0}
    };

    std::string cle = villeDepart + "-" + villeArrivee;
    if (distances.find(cle) == distances.end()) {
        cle = villeArrivee + "-" + villeDepart; // V�rifier dans l'autre sens
    }

    double distance = (distances.find(cle) != distances.end()) ? distances[cle] : 0.0;

    if (distance == 0.0) {
        std::cerr << "Erreur : Distance entre " << villeDepart << " et " << villeArrivee << " non definie.\n";
        return -1.0; // Indique une erreur
    }

    double prixBase = distance * 0.1; // Exemple : 10 centimes par kilometre
    return (typeClasse == "Premiere classe") ? prixBase * 1.5 : prixBase;
}
