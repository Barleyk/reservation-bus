#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUS 10
#define MAX_SEATS_PER_BUS 50
#define MAX_NAME_LENGTH 50
#define MAX_CONTACT_LENGTH 15
#define MAX_PASSAGERS 100
#define MAX_RESERVATIONS 500

// Modes de paiement
typedef enum {
    PAIEMENT_MOBILE
} ModePaiement;

// Structure pour représenter un siège
typedef struct {
    int numero;
    int occupe;
} Siege;

// Structure pour représenter un bus
typedef struct {
    int numero;
    char lieuDepart[MAX_NAME_LENGTH];
    char lieuArrivee[MAX_NAME_LENGTH];
    Siege sieges[MAX_SEATS_PER_BUS];
} Bus;

// Structure pour représenter un passager
typedef struct {
    char nom[MAX_NAME_LENGTH];
    char contact[MAX_CONTACT_LENGTH];
    ModePaiement modePaiement;
} Passager;

// Structure pour représenter une réservation
typedef struct {
    Passager passager;
    Bus *bus;
    int numeroSiege;
    float montantAPayer;
} Reservation;

// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("\nMenu Principal :\n");
    printf("1. Afficher les itineraires disponibles\n");
    printf("2. Reserver un billet\n");
    printf("3. Rechercher un passager et ses reservations\n");
    printf("4. Afficher les bus par itineraire\n");
    printf("5. Payer une reservation\n");
    printf("6. Quitter\n");
}

// Fonction pour rechercher un bus par son numéro
Bus *rechercherBus(Bus *flotte, int nombreBus, int numeroBus) {
    for (int i = 0; i < nombreBus; i++) {
        if (flotte[i].numero == numeroBus) {
            return &flotte[i];
        }
    }
    return NULL;
}

// Fonction pour réserver un siège dans un bus
void reserverSiege(Bus *bus, int numeroSiege, Passager *passager) {
    if (numeroSiege >= 1 && numeroSiege <= MAX_SEATS_PER_BUS) {
        if (!bus->sieges[numeroSiege - 1].occupe) {
            bus->sieges[numeroSiege - 1].occupe = 1;
            printf("Siege %d reserve pour %s.\n", numeroSiege, passager->nom);
        } else {
            printf("Le siege %d est deja occupe.\n", numeroSiege);
        }
    } else {
        printf("Le siege %d n'existe pas dans ce bus.\n", numeroSiege);
    }
}

// Fonction pour afficher les itinéraires disponibles
void afficherItineraires(Bus *flotte, int nombreBus) {
    printf("\nItinéraires disponibles :\n");
    for (int i = 0; i < nombreBus; i++) {
        Bus *bus = &flotte[i];
        int siegesDisponibles = 0;
        for (int j = 0; j < MAX_SEATS_PER_BUS; j++) {
            if (!bus->sieges[j].occupe) {
                siegesDisponibles++;
            }
        }
        printf("Bus %d de %s a %s : %d sieges disponibles\n", bus->numero, bus->lieuDepart, bus->lieuArrivee, siegesDisponibles);
    }
}

// Fonction pour réserver un billet
void reserverBillet(Bus *flotte, int nombreBus, Reservation *reservations, int *nombreReservations) {
    int numeroBus, numeroSiege;
    char nomPassager[MAX_NAME_LENGTH];

    printf("\nListe des bus disponibles :\n");
    for (int i = 0; i < nombreBus; i++) {
        printf("Bus %d de %s a %s\n", flotte[i].numero, flotte[i].lieuDepart, flotte[i].lieuArrivee);
    }
    printf("Choisissez un numero de bus : ");
    scanf("%d", &numeroBus);
    
    Bus *bus = rechercherBus(flotte, nombreBus, numeroBus);
    if (bus == NULL) {
        printf("Le bus specifie n'existe pas.\n");
        return;
    }

    printf("Bus %d : Sieges disponibles :\n", bus->numero);
    for (int i = 0; i < MAX_SEATS_PER_BUS; i++) {
        if (!bus->sieges[i].occupe) {
            printf("%d ", bus->sieges[i].numero);
        }
    }
    printf("\nChoisissez un numero de siege : ");
    scanf("%d", &numeroSiege);

    printf("Entrez votre nom : ");
    scanf("%s", nomPassager);

    Passager passager;
    strcpy(passager.nom, nomPassager);
    passager.modePaiement = PAIEMENT_MOBILE;

    reserverSiege(bus, numeroSiege, &passager);

    // Calcul du montant à payer (simulé ici)
    float montantAPayer = 50.0; // Exemple de montant fixe à payer

    // Enregistrer la réservation
    reservations[*nombreReservations].passager = passager;
    reservations[*nombreReservations].bus = bus;
    reservations[*nombreReservations].numeroSiege = numeroSiege;
    reservations[*nombreReservations].montantAPayer = montantAPayer;
    (*nombreReservations)++;
}

// Fonction pour effectuer le paiement d'une réservation
void effectuerPaiement(Reservation *reservations, int nombreReservations) {
    int numeroReservation;
    printf("\nListe des reservations :\n");
    for (int i = 0; i < nombreReservations; i++) {
        printf("%d. Nom du passager : %s, Numero de bus : %d, Siege : %d, Montant a payer : %.2f EUR\n",
               i + 1, reservations[i].passager.nom, reservations[i].bus->numero,
               reservations[i].numeroSiege, reservations[i].montantAPayer);
    }
    printf("Choisissez le numero de reservation a payer : ");
    scanf("%d", &numeroReservation);

    if (numeroReservation < 1 || numeroReservation > nombreReservations) {
        printf("Numero de reservation invalide.\n");
        return;
    }

    printf("Paiement effectue pour la reservation suivante :\n");
    printf("Nom du passager : %s, Numero de bus : %d, Siege : %d, Montant paye : %.2f EUR\n",
           reservations[numeroReservation - 1].passager.nom, reservations[numeroReservation - 1].bus->numero,
           reservations[numeroReservation - 1].numeroSiege, reservations[numeroReservation - 1].montantAPayer);

    // Ici, vous pouvez ajouter une logique de confirmation de paiement réel, par exemple envoyer une confirmation au passager.
}

// Fonction pour rechercher un passager et ses réservations
void rechercherPassagerEtBillet(Reservation *reservations, int nombreReservations, char lieuDepart[], char lieuArrivee[]) {
    char nomRecherche[MAX_NAME_LENGTH];
    printf("\nEntrez le nom du passager : ");
    scanf("%s", nomRecherche);

    printf("Réservations pour le passager '%s' de %s à %s :\n", nomRecherche, lieuDepart, lieuArrivee);
    for (int i = 0; i < nombreReservations; i++) {
        if (strcmp(reservations[i].passager.nom, nomRecherche) == 0 &&
            strcmp(reservations[i].bus->lieuDepart, lieuDepart) == 0 &&
            strcmp(reservations[i].bus->lieuArrivee, lieuArrivee) == 0) {
            printf("Nom du passager : %s, Siege : %d, Numero de bus : %d, Montant a payer : %.2f EUR\n", 
                    reservations[i].passager.nom, 
                    reservations[i].numeroSiege, 
                    reservations[i].bus->numero,
                    reservations[i].montantAPayer);
        }
    }
}

// Fonction pour afficher les bus par itineraire
void afficherBusParItineraire(Bus *flotte, int nombreBus, char lieuDepart[], char lieuArrivee[]) {
    int busTrouves = 0;

    printf("\nBus disponibles de %s à %s :\n", lieuDepart, lieuArrivee);
    for (int i = 0; i < nombreBus; i++) {
        Bus *bus = &flotte[i];
        if (strcmp(bus->lieuDepart, lieuDepart) == 0 && strcmp(bus->lieuArrivee, lieuArrivee) == 0) {
            printf("Bus %d : %d sièges disponibles\n", bus->numero, MAX_SEATS_PER_BUS);
            busTrouves = 1;
        }
    }

    if (!busTrouves) {
        printf("Aucun bus trouvé pour l'itinéraire spécifié.\n");
    }
}

// Fonction principale
int main() {
    Bus flotte[MAX_BUS];
    Reservation reservations[MAX_RESERVATIONS];
    int nombreReservations = 0;

    for (int i = 0; i < MAX_BUS; i++) {
        flotte[i].numero = i + 1;
        sprintf(flotte[i].lieuDepart, "Ville%d", i + 1); // Remplacez Ville par le lieu de départ réel
        sprintf(flotte[i].lieuArrivee, "Destination%d", i + 1); // Remplacez Destination par le lieu d'arrivée réel
        for (int j = 0; j < MAX_SEATS_PER_BUS; j++) {
            flotte[i].sieges[j].numero = j + 1;
            flotte[i].sieges[j].occupe = 0;
        }
    }

    int choix;
    do {
        afficherMenu();
        printf("\nChoix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                afficherItineraires(flotte, MAX_BUS);
                break;
            case 2:
                reserverBillet(flotte, MAX_BUS, reservations, &nombreReservations);
                break;
            case 3: {
                char lieuDepart[MAX_NAME_LENGTH];
                char lieuArrivee[MAX_NAME_LENGTH];
                printf("\nEntrez le lieu de depart : ");
                scanf("%s", lieuDepart);
                printf("Entrez le lieu d'arrivee : ");
                scanf("%s", lieuArrivee);
                rechercherPassagerEtBillet(reservations, nombreReservations, lieuDepart, lieuArrivee);
                break;
            }
            case 4: {
                char lieuDepart[MAX_NAME_LENGTH];
                char lieuArrivee[MAX_NAME_LENGTH];
                printf("\nEntrez le lieu de depart : ");
                scanf("%s", lieuDepart);
                printf("Entrez le lieu d'arrivee : ");
                scanf("%s", lieuArrivee);
                afficherBusParItineraire(flotte, MAX_BUS, lieuDepart, lieuArrivee);
                break;
            }
            case 5:
                effectuerPaiement(reservations, nombreReservations);
                break;
            case 6:
                printf("Quitter application.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 6);

    return 0;
}
