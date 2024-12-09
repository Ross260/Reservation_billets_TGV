#ifndef BILLET_H
#define BILLET_H

#include <string>

class Billet {
    private:
        int numeroBillet;              // Numero unique du billet
        std::string typeClasse;        // Type de classe (Premiere ou Deuxieme classe)
        double prix;                   // Prix du billet
        int numeroTrain;               // Numero du train associe
        std::string dateVoyage;        // Date du voyage

    public:
        // Constructeur
        Billet(int numero, const std::string& type, double prix, int train, const std::string& date);

        // Methodes d'affichage et d'acces
        void afficherDetailsBillet() const;
        // Methode statique pour calculer le prix du billet
        static double calculerPrix(const std::string& villeDepart, const std::string& villeArrivee, const std::string& typeClasse);


        int getNumeroBillet() const { return numeroBillet; }
        int getNumeroTrain() const { return numeroTrain; }
        const std::string& getDateVoyage() const { return dateVoyage; }

        // Getters pour typeClasse et prix
        const std::string& getTypeClasse() const { return typeClasse; }
        double getPrix() const { return prix; }

        
        // Operateur d'egalite (pour std::remove)
        bool operator==(const Billet& other) const {
            return numeroBillet == other.numeroBillet;
        }
};

#endif
