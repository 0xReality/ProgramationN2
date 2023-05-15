#include "individu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct individu * allouer_init_individu(const char *prenom, const char *nom, const struct date *d_naissance, const char *origine) {
    struct individu *ind = malloc(sizeof(struct individu));
    if (ind == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour l'individu\n");
        return NULL;
    }

    ind->nom = malloc((strlen(nom) + 1) * sizeof(char));
    ind->prenom = malloc((strlen(prenom) + 1) * sizeof(char));
    ind->naissance = malloc(sizeof(struct date));
    ind->origine = malloc((strlen(origine) + 1) * sizeof(char));

    if (ind->nom == NULL || ind->prenom == NULL || ind->naissance == NULL || ind->origine == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour les champs de l'individu\n");
        free(ind->nom);
        free(ind->prenom);
        free(ind->naissance);
        free(ind->origine);
        free(ind);
        return NULL;
    }

    strcpy(ind->nom, nom);
    strcpy(ind->prenom, prenom);
    memcpy(ind->naissance, d_naissance, sizeof(struct date));
    strcpy(ind->origine, origine);

    return ind;
}

void detruire_individu(struct individu **ind) {
    if (*ind == NULL) {
        return;
    }

    free((*ind)->nom);
    free((*ind)->prenom);
    free((*ind)->naissance);
    free((*ind)->origine);
    free(*ind);
    *ind = NULL;
}

void afficher_individu(const struct individu *ind) {
    if (ind == NULL) {
        printf("Individu non valide.\n");
        return;
    }

    printf("Nom: %s\n", ind->nom);
    printf("Prénom: %s\n", ind->prenom);
    printf("Date de naissance: ");
    afficher_date(ind->naissance);
    printf(", Origine: %s\n", ind->origine);
}

int nbre_annees_revolues(const struct individu *ind, const struct date *d) {
    if (ind == NULL || d == NULL) {
        fprintf(stderr, "Erreur : Individu ou date non valide.\n");
        return -1;
    }

    int years = d->annee - ind->naissance->annee;

    if (d->mois < ind->naissance->mois || (d->mois == ind->naissance->mois && d->jour < ind->naissance->jour)) {
        years--;
    }

    return years;
}
    