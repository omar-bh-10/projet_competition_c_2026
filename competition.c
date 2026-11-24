#include <stdio.h>
#include "competition.h"
#include <stdlib.h>
#include <string.h>

Competition* creer_competition(int nb_de_tours){

    /* L'allocation memoire pour la structure competition*/
    Competition *c = malloc(sizeof(Competition));

    /* verification de l'allocation*/
    if(c == NULL){
        return NULL;
    }

    /* commence la competition en mode ouverte*/
    c->etat = OUVERTE;

    /*enregistrer le nb de tours */
    c->nbTours = nb_de_tours;
    
    /* calculer le nombre maximale de participants pour un tournoi à élimination directe :  nb participants = 2^(nb tours) */
    c->maxParticipants = 1;
    for(int i=0;i<nb_de_tours;i++){
        c->maxParticipants *= 2;
    }

    /* 0 participant enregistre au depart */
    c->nbParticipants = 0;

    /* Allocation du tableau des compétiteurs*/
    c->participants = malloc(c->maxParticipants * sizeof(Competiteur));

    if(c->participants == NULL){
        free(c);
        return NULL;
    }

    /* Initialisation pour les matchs*/
    c->matchs = NULL;
    c->nbMatchs = 0;
    c->racine = NULL;

    c->nbMatchs = c->maxParticipants - 1;
    c->matchs = malloc(sizeof(Match*) * c->nbMatchs);

    if(c->matchs == NULL){
        free(c->participants);
        free(c);
        return NULL;
    }

    /* Creation des matchs*/

    for(int i=0; i<c->nbMatchs;i++){
        c->matchs[i] = creer_match(i+1);

        if(c->matchs[i] == NULL){
            return NULL;

        }

    }

    /* Construction de l'arbre */
    for(int i=0; i<c->nbMatchs;i++){
        int gauche = 2*i + 1;
        int droite = 2*i + 2 ;

        if(gauche < c->nbMatchs){
            c->matchs[i]->gauche = c->matchs[gauche];
            c->matchs[gauche]->parent = c->matchs[i];
        }

        if(droite < c->nbMatchs){
            c->matchs[i]->droite = c->matchs[droite];
            c->matchs[droite]->parent = c->matchs[i];
        }  
    }

    /* La finale */
    c->racine = c->matchs[0];

    return c;
}

int Existance_de_pseudo(Competition *c, char pseudo[])
{
    if(c == NULL)
    {
        return 0;
    }

    for(int i = 0; i < c->nbParticipants; i++)
    {
        if(strcmp(c->participants[i].pseudo, pseudo) == 0)
        {
            return 1;
        }
    }

    return 0;
}


void afficher_competition(Competition *c)
{
    if(c == NULL)
    {
        fprintf(stderr,
                "Erreur : aucune competition a afficher.\n");
        return;
    }

    printf("\n");
    printf("=====================================\n");
    printf("          COMPETITION\n");
    printf("=====================================\n");

    printf("Nombre de participants : %d/%d\n",
           c->nbParticipants,
           c->maxParticipants);

    printf("Nombre de tours : %d\n",
           c->nbTours);

    printf("Etat : ");

    switch(c->etat)
    {
        case OUVERTE:
            printf("OUVERTE\n");
            break;

        case FERMEE:
            printf("FERMEE\n");
            break;

        case TERMINEE:
            printf("TERMINEE\n");
            break;
    }

    printf("\n===== PARTICIPANTS =====\n");

    if(c->nbParticipants == 0)
    {
        printf("Aucun participant enregistre.\n");
    }
    else
    {
        for(int i = 0; i < c->nbParticipants; i++)
        {
            printf("[%d] %s\n",
                   c->participants[i].id_competiteur,
                   c->participants[i].pseudo);
        }
    }

    printf("\n===== MATCHS =====\n");

    for(int i = 0; i < c->nbMatchs; i++)
    {
        Match *m = c->matchs[i];

        printf("\n---------------------------------\n");

        if(m == c->racine)
        {
            printf("FINALE (Match %d)\n", m->id);
        }
        else
        {
            printf("Match %d\n", m->id);
        }

        printf("---------------------------------\n");

        printf("Joueur 1 : ");
        if(m->joueur1 != NULL)
        {
            printf("%s\n", m->joueur1->pseudo);
        }
        else
        {
            printf("EN ATTENTE\n");
        }

        printf("Joueur 2 : ");
        if(m->joueur2 != NULL)
        {
            printf("%s\n", m->joueur2->pseudo);
        }
        else
        {
            printf("EN ATTENTE\n");
        }

        printf("Vainqueur : ");
        if(m->vainqueur != NULL)
        {
            printf("%s\n", m->vainqueur->pseudo);
        }
        else
        {
            printf("AUCUN\n");
        }
    }

    if(c->etat == TERMINEE &&
       c->racine != NULL &&
       c->racine->vainqueur != NULL)
    {
        printf("\n=====================================\n");
        printf("CHAMPION DE LA COMPETITION : %s\n",
               c->racine->vainqueur->pseudo);
        printf("=====================================\n");
    }

    printf("\n=====================================\n");
}

void ajouter_competiteur(Competition *c, const char *pseudo){

    if(c == NULL){
        return;
    }

    /* tu peux pas inscrire tant que la competition n'est pas OUVERTE*/
    if(c->etat != OUVERTE){
        printf("La competition est fermee. \n");
        return;
    }

    /* verifie que la capacite maximale n'est pas atteinte */
    if(c->nbParticipants >= c->maxParticipants){
        printf("Nombre maximal de participants atteint. \n");
        return;

    }

    /*verification de l'unicite de pseudo*/
    if(Existance_de_pseudo(c, (char*)pseudo)){
        printf("Ce pseudo existe deja! \n");
        return;
    }

    Competiteur nouveau;

    /*donner à la competiteur un identifiant unique*/
    nouveau.id_competiteur = c->nbParticipants + 1 ;

    /*copie du pseudo dans la structure*/
    strcpy(nouveau.pseudo, pseudo);

    /*Ajout dans le tableau de participants*/
    c->participants[c->nbParticipants] = nouveau;

    c->nbParticipants++;

    
    /* si nous avons atteint la nb max de participants on ferme l'ajout à la competition*/
    if(c->nbParticipants == c->maxParticipants){
        fermer_competition(c);
    }

}

void fermer_competition(Competition *c)
{
    if (c == NULL)
    {
        fprintf(stderr, "Erreur : competition inexistante.\n");
        return;
    }

    if (c->etat == FERMEE)
    {
        printf("La competition est deja fermee.\n");
        return;
    }

    if (c->etat == TERMINEE)
    {
        printf("La competition est terminee.\n");
        return;
    }

    c->etat = FERMEE;
    creer_matchs_premier_tour(c);
    printf("Competition fermee avec succes !\n");
}

void creer_matchs_premier_tour(Competition *c)
{
    if(c == NULL)
    {
        return;
    }

    int indiceParticipant = 0;

    /* Les feuilles commencent à nbMatchs/2 */
    for(int i = c->nbMatchs / 2; i < c->nbMatchs;i++)
    {
        Match *m = c->matchs[i];

        if(indiceParticipant < c->nbParticipants)
        {
            m->joueur1 = &c->participants[indiceParticipant++];
        }

        if(indiceParticipant < c->nbParticipants)
        {
            m->joueur2 = &c->participants[indiceParticipant++];
        }
    }
}


void detruire_competition(Competition *c)
{
    if(c == NULL)
    {
        return;
    }

    /* Liberation des matchs */
    if(c->matchs != NULL)
    {
        for(int i = 0; i < c->nbMatchs; i++)
        {
            if(c->matchs[i] != NULL)
            {
                detruire_match(c->matchs[i]);
            }
        }

        free(c->matchs);
        c->matchs = NULL;
    }

    /* Liberation du tableau des participants */
    if(c->participants != NULL)
    {
        free(c->participants);
        c->participants = NULL;
    }

    c->racine = NULL;
    c->nbMatchs = 0;
    c->nbParticipants = 0;
    c->maxParticipants = 0;

    /* Liberation de la competition */
    free(c);

    printf("Memoire liberee avec succes !\n");
}