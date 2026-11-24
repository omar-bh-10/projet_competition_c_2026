#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sauvegarde.h"
#include "competition.h"

void sauvegarder_fichier_competition(Competition *c,
                                     const char *nomFichier)
{
    if(c == NULL)
    {
        fprintf(stderr,
                "Erreur : aucune competition a sauvegarder.\n");
        return;
    }

    FILE *fichier = fopen(nomFichier, "w");

    if(fichier == NULL)
    {
        fprintf(stderr,
                "Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier,
            "=====================================\n");
    fprintf(fichier,
            "          COMPETITION\n");
    fprintf(fichier,
            "=====================================\n");

    fprintf(fichier,
            "Participants : %d/%d\n",
            c->nbParticipants,
            c->maxParticipants);

    fprintf(fichier,
            "Nombre de tours : %d\n",
            c->nbTours);

    fprintf(fichier,
            "Etat : ");

    switch(c->etat)
    {
        case OUVERTE:
            fprintf(fichier, "OUVERTE\n");
            break;

        case FERMEE:
            fprintf(fichier, "FERMEE\n");
            break;

        case TERMINEE:
            fprintf(fichier, "TERMINEE\n");
            break;
    }

    fprintf(fichier,
            "\n===== PARTICIPANTS =====\n");

    if(c->nbParticipants == 0)
    {
        fprintf(fichier,
                "Aucun participant enregistre.\n");
    }
    else
    {
        for(int i = 0; i < c->nbParticipants; i++)
        {
            fprintf(fichier,
                    "[%d] %s\n",
                    c->participants[i].id_competiteur,
                    c->participants[i].pseudo);
        }
    }

    fprintf(fichier,
            "\n===== MATCHS =====\n");

    for(int i = 0; i < c->nbMatchs; i++)
    {
        Match *m = c->matchs[i];

        fprintf(fichier,
                "\n---------------------------------\n");

        if(m == c->racine)
        {
            fprintf(fichier,
                    "FINALE (MATCH %d)\n",
                    m->id);
        }
        else if(m->parent == c->racine)
        {
            fprintf(fichier,
                    "DEMI-FINALE (MATCH %d)\n",
                    m->id);
        }
        else
        {
            fprintf(fichier,
                    "MATCH %d\n",
                    m->id);
        }

        fprintf(fichier,
                "---------------------------------\n");

        fprintf(fichier,
                "Joueur 1 : ");

        if(m->joueur1 != NULL)
        {
            fprintf(fichier,
                    "%s\n",
                    m->joueur1->pseudo);
        }
        else
        {
            fprintf(fichier,
                    "EN ATTENTE\n");
        }

        fprintf(fichier,
                "Joueur 2 : ");

        if(m->joueur2 != NULL)
        {
            fprintf(fichier,
                    "%s\n",
                    m->joueur2->pseudo);
        }
        else
        {
            fprintf(fichier,
                    "EN ATTENTE\n");
        }

        fprintf(fichier, "Vainqueur : ");

        if(m->vainqueur != NULL)
        {
            fprintf(fichier,"%s\n",m->vainqueur->pseudo);
        }
        else
        {
            fprintf(fichier,"AUCUN\n");
        }
    }

    if(c->etat == TERMINEE && c->racine != NULL &&c->racine->vainqueur != NULL)
    {
        fprintf(fichier,"\n=====================================\n");
        fprintf(fichier,"CHAMPION DE LA COMPETITION : %s\n",c->racine->vainqueur->pseudo);
        fprintf(fichier,"=====================================\n");
    }

    fclose(fichier);

    printf("Sauvegarde effectuee avec succes dans le fichier %s\n",nomFichier);
}