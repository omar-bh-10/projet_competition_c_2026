# Projet de Gestion de Compétition Sportive

## Description

Ce projet est une application développée en langage **C** permettant la gestion d'une compétition sportive. Elle offre des fonctionnalités pour créer et organiser des compétitions, gérer les matchs, afficher les informations relatives à la compétition et sauvegarder les données dans des fichiers.

Ce projet a été réalisé dans le cadre d'un travail universitaire portant sur les structures de données, l'algorithmique et la programmation modulaire en langage C.

---

## Fonctionnalités

- Création et gestion d'une compétition.
- Ajout et gestion des matchs.
- Affichage des informations de la compétition.
- Sauvegarde des données dans des fichiers.
- Chargement des données sauvegardées.
- Interface en ligne de commande.
- Organisation du projet en modules indépendants.

---

## Structure du projet

projet_competition_c_2026/
│
├── main.c
├── competition.c
├── competition.h
├── match.c
├── match.h
├── sauvegarde.c
├── sauvegarde.h
├── Makefile
└── README.md

## Compilation

Le projet est compilé à l'aide du Makefile fourni.

### Compiler le projet

```bash
make

### Nettoyer les fichiers générés

```bash
make clean
```

---

## Technologies utilisées

- Langage C
- GCC (GNU Compiler Collection)
- Gestion de fichiers
- Programmation modulaire
- Structures de données

---

## Répartition des contributions

| Membre | Contributions |
|---------|--------------|
| **Mohamed Omar BEN HAMMOUDA** | Développement de `competition.h`, `competition.c` , `main.c` et `Makefile` |
| **Ihab Alrashiiny** | Développement de `match.h` et `match.c` |
| **Marco Ferri** | Développement de `sauvegarde.h` et `sauvegarde.c` |

---

## Auteurs

Ce projet a été conçu et développé par :

- **Mohamed Omar BEN HAMMOUDA**
- **Ihab Al rachini**
- **Marc-Aurèle Ferri**

dans le cadre d'un projet de programmation en langage C axé sur la gestion de compétitions sportives, la résolution de problèmes algorithmiques et l'application des bonnes pratiques de développement logiciel.

---

## Fichiers ignorés par Git

Le fichier `.gitignore` contient :

```gitignore
# Exécutable
programme.exe

# Fichiers objets
*.o
```

---

## Licence

Projet réalisé à des fins pédagogiques et académiques.








