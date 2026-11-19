#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"
#include "competition.h"

/* Sauvegarde l'etat d'une competition dans un fichier texte.
 * c          : la competition a sauvegarder
 * nomFichier : le nom du fichier a creer (ex : "sauvegarde.txt")
 * Si le fichier existe deja, son contenu est ecra */





void sauvegarder_fichier_competition(Competition* c, const char* nomFichier){
    //pas de competition alors pas de sauvegarde retourne rien
    if(c == NULL){
        return;
    }

    // permet d'ouvrir un fichier et de l'associer a un flux de creer un fichier ou d'écraser et de remplacer par les nouvelles données
    FILE *fichier=fopen(nomFichier, "w");

    //si ouverture du flux == NULL alors on affiche le message d'erreur cest pour afficher des msg d'erreurs.
    if(fichier==NULL){
        fprintf(stderr,"Erreur flux \n");
        return;

    }
    /* ce bloc ecrit toute les informations de la fonction affichage_competition dans me fichier que l'on va sauvegarder.
    il commence de la ligne 27 jusqu'a la ligne 56 */
    fprintf(fichier,"\n La liste des participants : \n");

    
    fprintf(fichier,"Participants: %d %d \n",c->nbParticipants, c->maxParticipants);


    for(int i=0;i<c->nbParticipants;i++){
    fprintf(fichier,"%d : %s\n", i+1, c->participants[i].pseudo);
    }
   

    fprintf(fichier,"Etat: ");

    switch (c->etat)
    {
        case OUVERTE:
            fprintf(fichier,"OUVERTE\n");
            break;

        case FERMEE:
            fprintf(fichier,"FERMEE\n");
            break;

        case TERMINEE:
            fprintf(fichier,"TERMINEE\n");
            break;
    }
    

    // fermer le flux que l'on a ouvert sinon il reste ouvert et il peutn y avoir des erreurs d'ecriture.
    fclose(fichier);
}
