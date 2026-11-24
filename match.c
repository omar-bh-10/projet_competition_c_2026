#include <stdio.h>
#include <stdlib.h>

#include "match.h"
#include "competition.h"

Match* creer_match(int id)
{
    Match *m = malloc(sizeof(Match));

    if(m == NULL)
    {
        return NULL;
    }

    m->id = id;

    m->joueur1 = NULL;
    m->joueur2 = NULL;
    m->vainqueur = NULL;

    m->gauche = NULL;
    m->droite = NULL;
    m->parent = NULL;

    return m;
}

int match_complet(Match *m)
{
    if(m == NULL)
    {
        return 0;
    }

    return (m->joueur1 != NULL && m->joueur2 != NULL);
}

int match_termine(Match *m)
{
    if(m == NULL)
    {
        return 0;
    }

    return (m->vainqueur != NULL);
}

int enregistrer_vainqueur(Competition *c,Match *m,Competiteur *vainqueur)
{
    if(c == NULL || m == NULL || vainqueur == NULL)
    {
        return 0;
    }

    /* Les deux joueurs doivent être connus */
    if(!match_complet(m))
    {
        printf("Match incomplet.\n");
        return 0;
    }

    /* Match déjà terminé */
    if(match_termine(m))
    {
        printf("Le vainqueur est deja defini.\n");
        return 0;
    }

    /* Le vainqueur doit être un des participants */
    if(vainqueur != m->joueur1 && vainqueur != m->joueur2)
    {
        printf("Ce joueur ne participe pas a ce match.\n");
        return 0;
    }

    m->vainqueur = vainqueur;

    /* Propagation automatique dans l'arbre */
    if(m->parent != NULL)
    {
        if(m->parent->gauche == m)
        {
            m->parent->joueur1 = vainqueur;
            printf("Le vainqueur %s est qualifie pour le match %d\n",vainqueur->pseudo,m->parent->id);
        }
        else if(m->parent->droite == m)
        {
            m->parent->joueur2 = vainqueur;
            printf("Le vainqueur %s est qualifie pour le match %d\n",vainqueur->pseudo,m->parent->id);
        }
    }

    printf("Vainqueur du match %d : %s\n", m->id,vainqueur->pseudo);

    /* Si c'est la finale */
    if(m == c->racine)
    {
        c->etat = TERMINEE;

        printf("\n=================================\n");
        printf("COMPETITION TERMINEE\n");
        printf("Champion : %s\n", vainqueur->pseudo);
        printf("=================================\n");
    }

    return 1;
}

void afficher_match(Match *m)
{
    if(m == NULL)
    {
        return;
    }

    printf("\n=================================\n");

    if(m->parent == NULL)
    {
        printf("       FINALE (MATCH %d)\n", m->id);
    }
    else
    {
        printf("       MATCH %d\n", m->id);
    }

    printf("=================================\n");

    printf("Joueur 1 : ");

    if(m->joueur1 != NULL)
    {
        printf("%s\n", m->joueur1->pseudo);
    }
    else
    {
        printf("EN ATTENTE DU VAINQUEUR\n");
    }

    printf("Joueur 2 : ");

    if(m->joueur2 != NULL)
    {
        printf("%s\n", m->joueur2->pseudo);
    }
    else
    {
        printf("EN ATTENTE DU VAINQUEUR\n");
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


void detruire_match(Match *m)
{
    if(m == NULL)
    {
        return;
    }

    free(m);
}