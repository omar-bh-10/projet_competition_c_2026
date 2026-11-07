#ifndef MATCH_H
#define MATCH_H
#include "competition.h"

typedef struct Match{
    int id;

    Competiteur *joueur1;
    Competiteur *joueur2;

    Competiteur *vainqueur;

    struct Match *gauche;
    struct Match *droite;
} Match;



#endif 
