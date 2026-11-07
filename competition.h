#ifndef COMPETITION_H
#define COMPETITION_H
#include "match.h"

#define MAX_PSEUDO 40

typedef enum {
    OUVERTE,
    FERMEE,
    TERMINEE

} Etat_de_competition;

typedef struct Competiteur {
    int id_competiteur;
    char pseudo[MAX_PSEUDO];
} Competiteur;

typedef struct Competition {
    Etat_de_competition etat;

    int nbTours;
    int nbParticipants;
    int maxParticipants;

    Competiteur* participants;

    Match** matchs;
    int nbMatchs;

    Match* racine;

} Competition;


Competition* creer_competition(int nb_de_tours);

void ajouter_competiteur(Competition *c, const char *pseudo);

void afficher_competition(Competition* c);

void fermer_competition(Competition* c);

void sauvegarder_competition(Competition* c, const char *nom_de_Fichier);

void detruire_competition(Competition* c);

int Existance_de_pseudo(Competition *c, char pseudo[]);

void enregistrer_resultat(Competition* c, int id_match, int vainqueur);



#endif