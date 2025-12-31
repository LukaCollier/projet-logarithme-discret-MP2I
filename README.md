# Logarithme Discret - Projet Cryptographie

## Description du projet

Ce projet a pour objectif de calculer des logarithmes discrets dans un groupe multiplicatif \( \mathbb{Z}_q \), où \( q = 2^{31} - 1 \) (un nombre premier de Mersenne). Le calcul du logarithme discret est un problème difficile, essentiel en cryptographie. 

Dans ce projet, nous représentons les nombres sous forme binaire à l'aide de chaînes de caractères de 31 bits. L'algorithme de logarithme discret est calculé en base 7 modulo \( q \), en utilisant des techniques comme l'**algorithme naïf** et **l'algorithme Baby Step - Giant Step**.

Le programme implémente plusieurs fonctions pour manipuler des nombres binaires et effectuer des opérations arithmétiques, ainsi que des algorithmes pour calculer le logarithme discret.

## Table des matières

1. [Fonctionnement](#fonctionnement)
2. [Algorithmes Implémentés](#algorithmes-implémentés)
3. [Dépendances](#dépendances)
4. [Instructions de Compilation et d'Exécution](#instructions-de-compilation-et-dexécution)
5. [Exemple d'Exécution](#exemple-dexécution)
6. [Explication du Code](#explication-du-code)
7. [Auteur](#auteur)

## Fonctionnement

### Objectif

Le but du programme est de calculer le logarithme discret de divers nombres dans le groupe \( \mathbb{Z}_q \), avec \( q = 2^{31} - 1 \), en utilisant la base 7. Le programme fournit deux algorithmes principaux pour résoudre ce problème :

1. **Algorithme Naïf** : Il calcule le logarithme discret en vérifiant successivement les puissances de 7 jusqu'à trouver la solution.
2. **Baby Step - Giant Step** : Une approche plus optimisée qui divise l'espace de recherche en deux parties et utilise un tableau pour accélérer la recherche du logarithme discret.

### Types de Logarithmes Calculés

1. **Vérification du logarithme discret de `target0`**.
2. **Calcul du logarithme discret de `target1`** (via l'algorithme naïf).
3. **Calcul du logarithme discret de `target2`** (via l'algorithme Baby Step - Giant Step).

## Algorithmes Implémentés

### 1. **Algorithme Naïf**

L'algorithme naïf consiste à calculer successivement les puissances de 7 (i.e., \( 7^i \)) et à s'arrêter lorsque l'on trouve un \( i \) tel que \( 7^i \equiv h \ (\text{mod} \ q) \). Ce méthode est simple mais inefficace pour de grands nombres.

### 2. **Baby Step - Giant Step**

Cet algorithme divise l'ensemble des puissances de 7 en deux parties égales. Il utilise un tableau pour stocker les puissances de \( 7^k \), et une fois que l'on connaît la cible, on essaie de la "rapprocher" des valeurs stockées dans le tableau en multipliant successivement par 7.

## Dépendances

Le programme est écrit en **C** et utilise les bibliothèques standard suivantes :

- `assert.h` : Pour vérifier les assertions et les préconditions.
- `stdlib.h` : Pour les fonctions standard de gestion de la mémoire.
- `stdbool.h` : Pour gérer les types booléens.
- `stdio.h` : Pour l'affichage à la console.
- `string.h` : Pour manipuler des chaînes de caractères.

Aucune bibliothèque externe n'est requise.

## Instructions de Compilation et d'Exécution

### Compilation

Pour compiler le programme, utilisez le compilateur **gcc** avec la commande suivante :

```bash
gcc -o dlog dlog.c
