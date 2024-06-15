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
