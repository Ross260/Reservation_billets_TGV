#ifndef RESERVATION_H
#define RESERVATION_H

#include "Passager.h"
#include "Billet.h"
#include "Train.h"

class Reservation {
private:
    int numeroReservation;
    Passager passager;
    Billet billet;

public:
    Reservation(int numero, const Passager& passager, const Billet& billet);
    void afficherDetailsReservation() const;
    static void recupererArchivesDepuisFichier(const std::string& cheminHistorique);

};

#endif
