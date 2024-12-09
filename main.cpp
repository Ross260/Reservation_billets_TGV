#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Train.h"
#include "Billet.h"
#include "Passager.h"
#include "Calendrier.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Recherche une reservation
const Billet* rechercherReservation(const std::vector<Passager>& passagers, int numeroBillet) {
    for (const auto& passager : passagers) {
        for (const auto& billet : passager.getReservations()) {
            if (billet.getNumeroBillet() == numeroBillet) {
                return &billet;
            }
        }
    }
    return nullptr;
}

// Lire les trains depuis un fichier texte
std::vector<Train> lireTrainsDepuisFichier(const std::string& cheminFichier) {
    std::vector<Train> trains;
    std::ifstream fichier(cheminFichier);

    if (!fichier) {
        std::cerr << RED << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << RESET << "\n";
        return trains;
    }

    int numero;
    std::string villeDepart, villeArrivee, horaireDepart, horaireArrivee;
    int capacite;

    while (fichier >> numero >> villeDepart >> villeArrivee >> horaireDepart >> horaireArrivee >> capacite) {
        trains.emplace_back(numero, villeDepart, villeArrivee, horaireDepart, horaireArrivee, capacite);
    }

    fichier.close();
    return trains;
}

// Enregistrer une reservation dans un fichier
void enregistrerReservationDansFichier(const Billet& billet, const std::string& cheminFichier) {
    std::ofstream fichier(cheminFichier, std::ios::app);

    if (!fichier) {
        std::cerr << RED << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << RESET << "\n";
        return;
    }

    fichier << billet.getNumeroBillet() << " "
            << billet.getTypeClasse() << " "
            << billet.getPrix() << " "
            << billet.getNumeroTrain() << " "
            << billet.getDateVoyage() << "\n";

    fichier.close();
}

// Enregistrer les informations des passagers dans un fichier
void enregistrerPassagersDansFichier(const std::vector<Passager>& passagers, const std::string& cheminFichier) {
    std::ofstream fichier(cheminFichier);

    if (!fichier) {
        std::cerr << RED << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << RESET << "\n";
        return;
    }

    for (const auto& passager : passagers) {
        fichier << passager.getNom() << " " << passager.getPrenom() << " " << passager.getIdentifiant() << "\n";
        for (const auto& billet : passager.getReservations()) {
            fichier << "  Billet: " << billet.getNumeroBillet() << ", "
                    << billet.getTypeClasse() << ", "
                    << billet.getPrix() << "�, "
                    << "Train " << billet.getNumeroTrain() << ", "
                    << billet.getDateVoyage() << "\n";
        }
    }

    fichier.close();
}

// Enregistrer un billet (reserve ou annule) dans l'historique
void enregistrerHistorique(const Billet& billet, const std::string& cheminFichier, bool estAnnule = false) {
    std::ofstream fichier(cheminFichier, std::ios::app); // Append mode
    if (!fichier) {
        std::cerr << RED << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << RESET << "\n";
        return;
    }

    fichier << billet.getNumeroBillet() << " "
            << billet.getTypeClasse() << " "
            << billet.getPrix() << " "
            << billet.getNumeroTrain() << " "
            << billet.getDateVoyage() << " "
            << (estAnnule ? "Annule" : "Reserve") << "\n";

    fichier.close();
}

// Afficher les reservations des passagers
void afficherReservations(const std::vector<Passager>& passagers, int idUtilisateur) {
    auto it = std::find_if(passagers.begin(), passagers.end(), [&](const Passager& passager) {
        return passager.getIdentifiant() == idUtilisateur;
    });

    if (it == passagers.end()) {
        std::cout << RED << "Aucune reservation trouvee pour l'utilisateur ID " << idUtilisateur << ".\n" << RESET;
        return;
    }

    const auto& passager = *it;
    std::cout << YELLOW << "\nReservations pour " << passager.getNom() << " " << passager.getPrenom()
              << " (ID: " << passager.getIdentifiant() << "):\n" << RESET;
    const auto& reservations = passager.getReservations();

    if (reservations.empty()) {
        std::cout << "  Aucune reservation.\n";
    } else {
        for (const auto& billet : reservations) {
            billet.afficherDetailsBillet();
        }
    }
}


// Afficher le calendrier des trains
void afficherCalendrier(const Calendrier& calendrier) {
    std::cout << "Entrez la date pour voir les trains disponibles (YYYY-MM-DD) : ";
    std::string date;
    std::cin >> date;

    auto trains = calendrier.obtenirHoraires(date);
    if (trains.empty()) {
        std::cout << RED << "Aucun train disponible pour cette date.\n" << RESET;
    } else {
        std::cout << GREEN << "Trains disponibles pour " << date << " :\n" << RESET;
        for (const auto& train : trains) {
            train.afficherInfosTrain();
        }
    }
}

// Afficher l'historique des tickets pour un utilisateur sp�cifique

void afficherHistoriqueUtilisateur(const std::string& cheminFichier, int idUtilisateur) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) {
        std::cout << RED << "Erreur : Impossible de lire le fichier d'historique.\n" << RESET;
        return;
    }

    std::string ligne;
    bool trouve = false;
    std::cout << GREEN << "Historique des tickets pour l'utilisateur ID " << idUtilisateur << " :\n" << RESET;

    while (std::getline(fichier, ligne)) {
        // Verifier si la ligne contient l'ID utilisateur (ID : 'idUtilisateur')
        if (ligne.find("ID:" + std::to_string(idUtilisateur)) != std::string::npos) {
            std::cout << ligne << "\n";
            trouve = true;
        }
    }

    if (!trouve) {
        std::cout << RED << "Aucun ticket correspondant trouve pour cet utilisateur.\n" << RESET;
    }

    fichier.close();
}

void filtrerHistoriqueTickets(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) {
        std::cout << RED << "Erreur : Impossible de lire le fichier d'historique.\n" << RESET;
        return;
    }

    std::cout << "Filtrer par :\n1. Numero de train\n2. Date\nVotre choix : ";
    int choix;
    std::cin >> choix;

    std::string critere;
    if (choix == 1) {
        std::cout << "Entrez le numero du train : ";
    } else if (choix == 2) {
        std::cout << "Entrez la date (YYYY-MM-DD) : ";
    } else {
        std::cout << RED << "Choix invalide.\n" << RESET;
        return;
    }
    std::cin >> critere;

    std::string ligne;
    bool trouve = false;
    while (std::getline(fichier, ligne)) {
        if (ligne.find(critere) != std::string::npos) {
            std::cout << ligne << "\n";
            trouve = true;
        }
    }

    if (!trouve) {
        std::cout << RED << "Aucun ticket correspondant trouve.\n" << RESET;
    }

    fichier.close();
}



int main() {
    // Charger les trains depuis le fichier trains.txt
    std::vector<Train> trains = lireTrainsDepuisFichier("trains.txt");
    if (trains.empty()) {
        std::cerr << RED << "Aucun train charge. Verifiez le fichier trains.txt." << RESET << "\n";
        return 1;
    }

    Calendrier calendrier;
    for (const auto& train : trains) {
        calendrier.ajouterHoraire("2024-11-28", train);
        calendrier.ajouterHoraire("2024-11-29", train);
    }

    std::vector<Passager> passagers;

    while (true) {
        std::cout << YELLOW << "\n*************** RESERVATION DE BILLET DE TGV *************\n\n" << RESET;
        std::cout << GREEN << "* 1. Reserver un billet\t\t\t\t\t *\n" << RESET;
        std::cout << RED << "* 2. Annuler une reservation\t\t\t\t *\n" << RESET;
        std::cout << BLUE << "* 3. Afficher mes reservations\t\t\t\t *\n" << RESET;
        std::cout << "* 4. Afficher le calendrier des trains\t\t\t *\n";
        std::cout << "* 5. Afficher l'historique des tickets\t\t\t *\n";
        std::cout << "* 6. Filtrer l'historique des tickets\t\t\t *\n";
        std::cout << "* 7. Quitter  \t\t\t\t\t\t *\n";
        std::cout << YELLOW << "\n********************************************************** \n\n" << RESET;
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;

        if (choix == 1) { // Reserver un billet
            std::cout << "Trains disponibles : \n";
            for (const auto& train : trains) {
                train.afficherInfosTrain();
            }

            int choixTrain;
            std::cout << "Entrez le numero du train que vous souhaitez reserver : ";
            std::cin >> choixTrain;

            Train* trainSelectionne = nullptr;
            for (auto& train : trains) {
                if (train.getNumeroTrain() == choixTrain) {
                    trainSelectionne = &train;
                    break;
                }
            }

            if (!trainSelectionne) {
                std::cout << RED << "Train non trouve !" << RESET << "\n";
                continue;
            }

            if (!trainSelectionne->verifierDisponibilite()) {
                std::cout << RED << "Desole, ce train est complet." << RESET << "\n";
                continue;
            }

            std::string villeDepart = trainSelectionne->getVilleDepart();
            std::string villeArrivee = trainSelectionne->getVilleArrivee();

            std::cout << "Choisissez la classe :\n";
            std::cout << "1. Premiere classe\n";
            std::cout << "2. Deuxieme classe\n";
            std::cout << "Votre choix : ";
            int choixClasse;
            std::cin >> choixClasse;

            std::string classe = (choixClasse == 1) ? "Premiere classe" : "Deuxieme classe";

            // Calculer le prix dynamiquement
            double prix = Billet::calculerPrix(villeDepart, villeArrivee, classe);
            if (prix < 0) {
                std::cout << RED << "Erreur lors du calcul du prix.\n" << RESET;
                continue;
            }

            std::string nom, prenom;
            int idPassager;
            std::cout << "Entrez votre nom : ";
            std::cin >> nom;
            std::cout << "Entrez votre prenom : ";
            std::cin >> prenom;
            std::cout << "Entrez votre identifiant (numerique) : ";
            std::cin >> idPassager;

            auto it = std::find_if(passagers.begin(), passagers.end(), [&](const Passager& passager) {
                return passager.getNom() == nom && passager.getPrenom() == prenom && passager.getIdentifiant() == idPassager;
            });

            Passager* passager = nullptr;
            if (it != passagers.end()) {
                passager = &(*it);
            } else {
                passagers.emplace_back(nom, prenom, idPassager);
                passager = &passagers.back();
            }

            // Creer le billet
            Billet billet(1000 + idPassager, classe, prix, trainSelectionne->getNumeroTrain(), "2024-11-28");

            trainSelectionne->reserverPlace();
            passager->ajouterReservation(billet);

            // Enregistrer la reservation dans les fichiers
            enregistrerReservationDansFichier(billet, "reservations.txt");
            enregistrerHistorique(billet, "historique.txt");
            enregistrerPassagersDansFichier(passagers, "passagers.txt");

            std::cout << GREEN << "\nVotre reservation est confirmee :" << RESET << "\n";
            billet.afficherDetailsBillet();
            trainSelectionne->afficherInfosTrain();
        } else if (choix == 2) { // Annuler une reservation
            int numeroBillet;
            std::cout << "Entrez le numero de votre billet a annuler : ";
            std::cin >> numeroBillet;

            auto it = std::find_if(passagers.begin(), passagers.end(), [&](Passager& passager) {
                return rechercherReservation({passager}, numeroBillet) != nullptr;
            });

            if (it != passagers.end()) {
                const Billet* billet = rechercherReservation({*it}, numeroBillet);
                if (billet) {
                    it->supprimerReservation(*billet);

                    auto trainIt = std::find_if(trains.begin(), trains.end(), [&](Train& train) {
                        return train.getNumeroTrain() == billet->getNumeroTrain();
                    });

                    if (trainIt != trains.end()) {
                        trainIt->annulerReservation();
                    }

                    // Enregistrer l'annulation dans l'historique
                    enregistrerHistorique(*billet, "historique.txt", true);

                    std::cout << GREEN << "Raservation annulee avec succes.\n" << RESET;

                    // Enregistrer les passagers apres l'annulation
                    enregistrerPassagersDansFichier(passagers, "passagers.txt");
                }
            } else {
                std::cout << RED << "Reservation non trouvee.\n" << RESET;
            }
        } else if (choix == 3) { // Afficher mes reservations
    int idUtilisateur;
    std::cout << "Entrez votre identifiant (numerique) : ";
    std::cin >> idUtilisateur;

    afficherReservations(passagers, idUtilisateur);


        } else if (choix == 4) { // Afficher le calendrier des trains
            afficherCalendrier(calendrier);
        } else if (choix == 5) { // Afficher l'historique des tickets
            int idUtilisateur;
            std::cout << "Entrez votre identifiant (numerique) : ";
            std::cin >> idUtilisateur;
            afficherHistoriqueUtilisateur("historique.txt", idUtilisateur);
           } else if (choix == 6) {
               int idUtilisateur;
               std::cout << "Entrez votre identifiant (numerique) : ";
               std::cin >> idUtilisateur;
            filtrerHistoriqueTickets("historique.txt");
        } else if (choix == 7) { // Quitter
            enregistrerPassagersDansFichier(passagers, "passagers.txt");
            std::cout << GREEN << "Au revoir !" << RESET << "\n";
            break;
        } else {
            std::cout << RED << "Choix invalide.\n" << RESET;
        }
    }

    return 0;
}
