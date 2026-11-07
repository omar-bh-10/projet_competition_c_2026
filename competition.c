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
    c->participants = malloc(c->nbParticipants * sizeof(Competiteur));

    /* Initialisation pour les matchs*/
    c->matchs = NULL;
    c->nbMatchs = 0;
    c->racine = NULL;

    return c;
}


void afficher_competition(Competition* c){
    printf("********** COMPETITION ***********");
    printf("Participants: %d %d \n",c->nbParticipants, c->maxParticipants);

    printf("Etat: ");

    switch (c->etat)
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

    printf("\n La liste des participants : \n");

    for(int i=0;i<c->nbParticipants;i++){
        printf("%d : %s\n", i+1, c->participants[i].pseudo);
    }

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

    printf("Competiteur ajoute avec succes! \n");
    
    /* si nous avons atteint la nb max de participants on ferme l'ajout à la competition*/
    if(c->nbParticipants == c->maxParticipants){
        c->etat = FERMEE;
        printf("Competition automatiquement fermee! \n");
    }

}

void fermer_competition(Competition* c){

    if(c == NULL){
        return;
    }

    if(c->etat == OUVERTE){

        c->etat = FERMEE;
        printf("Competition fermee! \n");
    }
    else{
        printf("Impossible de modifier cet etat! \n");
    }
}


void sauvegarder_competition(Competition* c, const char *nom_de_Fichier){
    
}

void detruire_competition(Competition* c){
    if(c== NULL){
        return;
    }

    /* liberation du tableau des participants*/
    free(c->participants);

    /* liberation du tableau des matchs*/
    if(c->matchs != NULL){
        free(c->matchs);
    }

    /* liberation de la strucutre principale*/
    free(c);

    printf("Memoire liberee! \n");

}


int Existance_de_pseudo(Competition* c, char pseudo[]){

    for(int i=0; i< c->nbParticipants; i++){

        if(strcmp(c->participants[i].pseudo, pseudo) == 0){

            return 1;
        }
    }

    return 0;
}
