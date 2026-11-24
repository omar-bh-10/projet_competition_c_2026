#ifndef MATCH_H
#define MATCH_H

typedef struct Competiteur Competiteur;
typedef struct  Competition Competition ;


typedef struct Match{
    int id;

    Competiteur *joueur1;
    Competiteur *joueur2;

    Competiteur *vainqueur;

    struct Match *gauche;
    struct Match *droite;
    struct Match *parent;

} Match;

Match* creer_match(int id);


void afficher_match(Match *m);


int enregistrer_vainqueur(Competition* c,Match *m, Competiteur *vainqueur);

int match_complet(Match *m);
int match_termine(Match *m);


void detruire_match(Match *m);

#endif
