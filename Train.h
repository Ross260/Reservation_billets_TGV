#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <iostream>

class Train {
    private:
        int numeroTrain;
        std::string villeDepart;
        std::string villeArrivee;
        std::string horaireDepart;
        std::string horaireArrivee;
        int capacite;
        int placesLibres;

    public:
        Train(int numero, const std::string& depart, const std::string& arrivee,
            const std::string& hDepart, const std::string& hArrivee, int capacite);

        bool verifierDisponibilite() const;
        void reserverPlace();
        void annulerReservation();
        void afficherInfosTrain() const;

        // Getter and Setter for train information
        int getNumeroTrain() const { return numeroTrain; }
        const std::string& getVilleDepart() const { return villeDepart; }
        const std::string& getVilleArrivee() const { return villeArrivee; }
        const std::string& getHoraireDepart() const { return horaireDepart; }
        const std::string& getHoraireArrivee() const { return horaireArrivee; }
};

#endif
