#include "Billet.h"
#include <iostream>
#include <unordered_map>

// Constructeur
Billet::Billet(int numero, const std::string& type, double prix, int train, const std::string& date)
    : numeroBillet(numero), typeClasse(type), prix(prix), numeroTrain(train), dateVoyage(date) {}

// Methode pour afficher les d�tails du billet
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

    };

    std::string cle = villeDepart + "-" + villeArrivee;
    if (distances.find(cle) == distances.end()) {
        cle = villeArrivee + "-" + villeDepart; // V�rifier dans l'autre sens
    }

    double distance = (distances.find(cle) != distances.end()) ? distances[cle] : 0.0;

    if (distance == 0.0) {
        std::cerr << "Erreur : Distance entre " << villeDepart << " et " << villeArrivee << " non d�finie.\n";
        return -1.0; // Indique une erreur
    }

    double prixBase = distance * 0.1; // Exemple : 10 centimes par kilom�tre
    return (typeClasse == "Premi�re classe") ? prixBase * 1.5 : prixBase;
}
