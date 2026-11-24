#include <stdio.h>
#include <stdlib.h>

#include "competition.h"
#include "match.h"
#include "sauvegarde.h"

int main()
{
    Competition *competition = NULL;

    int choix;
    char pseudo[MAX_PSEUDO];
    char fichier[100];
    int nbTours;

    do
    {
        fprintf(stdout, "\n===== GESTION DE COMPETITION =====\n");
        fprintf(stdout, "=================================\n");
        fprintf(stdout, "1. Creer une competition\n");
        fprintf(stdout, "2. Ajouter des competiteurs\n");
        fprintf(stdout, "3. Afficher la competition\n");
        fprintf(stdout, "4. Fermer la competition\n");
        fprintf(stdout, "5. Enregistrer le resultat d'un match\n");
        fprintf(stdout, "6. Sauvegarder la competition\n");
        fprintf(stdout, "0. Quitter\n");
        fprintf(stdout, "Votre choix : ");

        if(scanf("%d", &choix) != 1)
        {
            fprintf(stderr, "Erreur de saisie.\n");

            while(getchar() != '\n');

            continue;
        }

        switch(choix)
        {
            case 1:

                if(competition != NULL)
                {
                    fprintf(stderr,
                            "Une competition existe deja.\n");
                    break;
                }

                printf("Nombre de tours : ");
                scanf("%d", &nbTours);

                competition = creer_competition(nbTours);

                if(competition != NULL)
                {
                    printf("Competition creee avec succes.\n");
                }
                else
                {
                    fprintf(stderr,
                            "Erreur lors de la creation.\n");
                }

                break;

            case 2:

                if(competition == NULL)
                {
                    fprintf(stderr,
                            "Aucune competition creee.\n");
                    break;
                }

                if(competition->etat != OUVERTE)
                {
                    fprintf(stderr,
                            "La competition est deja fermee.\n");
                    break;
                }

                while(competition->nbParticipants <
                      competition->maxParticipants)
                {
                    printf("Pseudo du competiteur %d/%d : ",
                           competition->nbParticipants + 1,
                           competition->maxParticipants);

                    scanf("%39s", pseudo);

                    if(Existance_de_pseudo(
                        competition,
                        pseudo))
                    {
                        fprintf(stderr,
                                "Pseudo deja utilise.\n");
                    }
                    else
                    {
                        ajouter_competiteur(
                            competition,
                            pseudo);

                        printf(
                            "Competiteur ajoute avec succes.\n");
                    }

                    if(competition->etat != OUVERTE)
                    {
                        break;
                    }
                }

                break;

            case 3:

                if(competition == NULL)
                {
                    fprintf(stderr,
                            "Aucune competition a afficher.\n");
                    break;
                }

                afficher_competition(competition);

                break;

            case 4:

                if(competition == NULL)
                {
                    fprintf(stderr,
                            "Aucune competition a fermer.\n");
                    break;
                }

                fermer_competition(competition);

                break;

            case 5:
            {
                int idMatch;
                int choixVainqueur;

                if(competition == NULL)
                {
                    fprintf(stderr,  "Aucune competition creee.\n");
                    break;
                }

                if(competition->etat != FERMEE)
                {
                    fprintf(stderr,"La competition doit etre en etat FERMEE.\n");
                    break;
                }

                printf("Numero du match : ");
                scanf("%d", &idMatch);

                if(idMatch < 1 || idMatch > competition->nbMatchs)
                {
                    fprintf(stderr, "Match inexistant.\n");
                    break;
                }

                Match *m = competition->matchs[idMatch - 1];

                if(!match_complet(m))
                {
                    fprintf(stderr, "Match incomplet.\n");
                    break;
                }

                if(match_termine(m))
                {
                    fprintf(stderr, "Ce match est deja termine.\n");
                    break;
                }

                afficher_match(m);

                printf("\n1. %s\n", m->joueur1->pseudo);

                printf("2. %s\n", m->joueur2->pseudo);

                printf("Choix du vainqueur : ");
                scanf("%d", &choixVainqueur);

                if(choixVainqueur == 1)
                {
                    enregistrer_vainqueur(competition,m, m->joueur1);
                    printf("\n=== ETAT MIS A JOUR ===\n");
                    afficher_competition(competition);
                }
                else if(choixVainqueur == 2)
                {
                    enregistrer_vainqueur(competition, m,m->joueur2);
                    printf("\n=== ETAT MIS A JOUR ===\n");
                    afficher_competition(competition);

                }
                else
                {
                    fprintf(stderr, "Choix invalide.\n");
                }

                break;
            }

            case 6:

                if(competition == NULL)
                {
                    fprintf(stderr, "Aucune competition a sauvegarder.\n");
                    break;
                }

                printf("Nom du fichier : ");
                scanf("%99s", fichier);

                sauvegarder_fichier_competition(competition,fichier);

                break;

            case 0:

                printf("Fin du programme.\n");

                break;

            default:

                fprintf(stderr, "Choix invalide.\n");
        }

    } while(choix != 0);

    if(competition != NULL)
    {
        detruire_competition(competition);
    }

    return EXIT_SUCCESS;
}
