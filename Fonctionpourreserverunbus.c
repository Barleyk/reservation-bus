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
