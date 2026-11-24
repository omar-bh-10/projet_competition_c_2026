#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "competition.h"

/*
 * Sauvegarde une compétition dans un fichier texte.
 * c : compétition à sauvegarder
 * nomFichier  : nom du fichier de sauvegarde
 */
void sauvegarder_fichier_competition(Competition *c,const char *nomFichier);

#endif