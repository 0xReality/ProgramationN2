#include <stdio.h>
#include <stdlib.h>
#include "individu.h"
#include "date.h"
#include <string.h>
#define TAILLE_MAX 1000

struct laureat_Turing
{
    struct individu *laureat;
    unsigned annee_prix;
};

/** Fonction qui alloue de l'espace sur le tas pour une chaîne de n caractères */
/** et renvoie l'adresse du bloc, de taille n+1, alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
char *allouer_chaine(int n)
{
    char *str = malloc((n + 1) * sizeof(char));
    if (str == NULL)
    {
        perror("Échec allocation chaine de caractères (struct individu ou ville)");
        exit(EXIT_FAILURE);
    }
    return str;
}

/** Fonction qui alloue de l'espace sur le tas pour un lauréat */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR allouer_tab_laureat */
struct laureat_Turing *allouer_laureat(void)
{
    struct laureat_Turing *lt = malloc(sizeof(struct laureat_Turing));
    if (lt == NULL)
    {
        perror("Échec allocation lauréat");
        exit(EXIT_FAILURE);
    }
    return lt;
}

/** Fonction qui alloue l'espace mémoire sur le tas */
/* pour un tableau de n adresses de lauréats */
/* (et pour n structures laureat_Turing) */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
struct laureat_Turing **allouer_tab_laureat(int n)
{
    int i;
    struct laureat_Turing **t = malloc(sizeof(struct laureat_Turing *) * n);
    if (t == NULL)
    {
        perror("Échec allocation tableau");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; ++i)
        t[i] = allouer_laureat();
    return t;
}

/** Fonction qui libère tout l'espace mémoire occupé sur le tas */
/* par le lauréat Turing pointé par lt */
void detruire_laureat(struct laureat_Turing **lt)
{
    detruire_individu(&(*lt)->laureat);
    free(*lt);
    *lt = NULL;
}

/** Fonction qui affiche le titre, le prénom et le nom du laureat, (la date et la ville de création) de l'ltéra lt */
void afficher_laureat(const struct laureat_Turing *lt)
{
    afficher_individu((lt)->laureat);
    printf("[lauréat %u]\n", (lt)->annee_prix);
}


/** Fonction qui initialise un tableau de lauréats Turing */
/* avec les lauréats stockés dans le fichier de nom n_fich */
/* et renvoie l'adresse du tableau ainsi initialisé */
/** N.B. L'entier pointé par le 2e paramètre d'entrée */
/* prend la valeur du nombre de lauréats référencés dans le tableau initialisé */
struct laureat_Turing **init_tab(char *n_fich, int *taille)
{
    int i;
    FILE *f;
    struct laureat_Turing **tab_res;
    struct date *tmp_date = allouer_init_date(0, 0, 0);
    char *tmp_prenom, *tmp_nom, *tmp_origine;
    /** Ouverture du fichier de nom n_fich en lecture */
    if ((f = fopen(n_fich, "r")) == NULL)
    {
        fprintf(stderr, "fichier %s introuvable \n", n_fich);
        exit(EXIT_FAILURE);
    }
    fscanf(f, "%d\n", taille);
    /* et stockage de son contenu dans le tableau tab_res */
    tab_res = allouer_tab_laureat(*taille);
    /* N.B. On suppose que les noms, prénoms et pays d'origine */
    /* des lauréats Turing du fichier laureats_Turing.txt */
    /* ont au plus TAILLE_MAX caractères */
    tmp_prenom = allouer_chaine(TAILLE_MAX);
    tmp_nom = allouer_chaine(TAILLE_MAX);
    tmp_origine = allouer_chaine(TAILLE_MAX);
    /* Récupération des lauréats stockés dans le fichier */
    for (i = 0; i < *taille; i++)
    {
        /* Lecture des nom et prénom du lauréat et de l'année du prix */
        if (fscanf(f, "%s %s [%u] ", tmp_prenom, tmp_nom, &tab_res[i]->annee_prix) != 3)
        {
            perror("Échec lecture fichier");
            exit(EXIT_FAILURE);
        }
        /* Lecture de la date et du pays de naissance */
        if (fscanf(f, "né le %u/%u/%u %s \n", &tmp_date->jour, &tmp_date->mois, &tmp_date->annee, tmp_origine) != 4)
        {
            perror("Échec lecture fichier");
            exit(EXIT_FAILURE);
        }
        tab_res[i]->laureat = allouer_init_individu(tmp_prenom, tmp_nom, tmp_date, tmp_origine);
    }
    /* Nettoyage : libération de la mémoire auxiliaire allouée sur la tas */
    detruire_date(&tmp_date);
    free(tmp_prenom);
    free(tmp_nom);
    free(tmp_origine);
    /* Fermeture du fichier */
    fclose(f);
    return tab_res;
}

void echanger_elements(struct laureat_Turing **tab, int index1, int index2) {
    struct laureat_Turing *temp = tab[index1];
    tab[index1] = tab[index2];
    tab[index2] = temp;
}

int main()
{

    int taille = 23;
    struct laureat_Turing **tab = init_tab("laureats_Turing.txt", &taille);
    int i=0;

    int premiere_position_non_us = 0;
    for (i = 0; i < taille; i++) {
        if (strcmp(tab[i]->laureat->origine, "États-Unis") != 0) {
            echanger_elements(tab, i, premiere_position_non_us);
            premiere_position_non_us++;
        }
    }

    for (i = 0; i < taille; i++) {
        struct date *date = malloc(sizeof(struct date));
        date->annee = tab[i]->annee_prix;
        date->mois = 3;
        date->jour = 15;
        afficher_laureat(tab[i]);

        /*if(nbre_annees_revolues(tab[i]->laureat, date) < 45){
            afficher_laureat(tab[i]);
        }*/
    }

    detruire_laureat(tab);


    return 0;
}