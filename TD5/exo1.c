#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct uef {
    unsigned coefficient;
    float note;
};

struct releve_BF_N2_info {
    unsigned long identifiant;
    struct uef algebre;
    struct uef programmation;
    struct uef logique;
};

typedef struct releve_BF_N2_info * lien;

int random(int min, int max)
{
    return min + rand() % (max+1 - min);
}


void initialiser_tab_releves(lien * t, int taille) {
    int i;
    srand(time(NULL)); // srand should be called only once
    for (i = 0; i <= taille; ++i) {
        /* réservation d'espace mémoire pour les relevés référencés dans le tableau */
        t[i] = malloc(sizeof(struct releve_BF_N2_info));
        /* initialisation pseudo-aléatoire des champs des relevés */
        t[i]->identifiant = (121 + rand() % 2) * 100000 + rand() % 18000;
        t[i]->algebre.note = random(6,20);
        t[i]->programmation.note = random(6,20);
        t[i]->logique.note = random(6,20);
    }
}

void affiche_releve(lien * t, int taille) 
{
    int i;
    for(i=1;i <= taille; i++)
    {
        printf("\n%d.Releve de Note de %lu\n",i, t[i]->identifiant);
        printf("Note de Algebre: %f/20\n", t[i]->algebre.note);
        printf("Note de Programmation: %f/20\n", t[i]->programmation.note);
        printf("Note de Logique: %f/20\n", t[i]->logique.note);
    }
}

int main() {
    struct releve_BF_N2_info * releve;
    int taille = 10;

    /* allocation de mémoire pour le tableau de relevés */
    releve = malloc(taille * sizeof(struct releve_BF_N2_info));
    initialiser_tab_releves(&releve, taille); // don't use & before releve
    affiche_releve(&releve, taille);
    return 0;
}
