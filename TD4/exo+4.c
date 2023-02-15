#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256

struct matrice
{
    int l;
    int c;
    int mat[N][N];
};

int random(int min, int max)
{
    return min + rand() % (max+1 - min);
}

int saisie_entier(int vmin, int vmax) 
{
    int res, n;
    char c;
    do
    {
        printf("Tapez une valeur entiere paire comprise entre %d et %d : ", vmin, vmax);
        n = scanf("%d", &res);
        if (1 == n && res >= vmin && res <= vmax)
            return res;
        if (0 == n)
        {
            do {scanf("%c", &c);}
            while (c != ' ' && c != '\t' && c != '\n');
        }
        printf("Erreur ! Recommencez !\n");
    }
    while (1);
}

void init_alea_mat(struct matrice * am)
{
    srand(time(NULL));
    for(int i=0;i<am->l;i++)
    {
        for(int j=0;j<am->c;j++)
        {
            am->mat[i][j] = random(10,99);
        }
    }
}

int affichage_mat(struct matrice * am)
{
    int i,j,affi=0;
    printf("+");
    for(affi=0;affi<= am->l;affi++)
    {
        printf("--");
    }
    printf("--");
    printf("+\n");
    for(i=0;i<am->l;i++)
    {
        printf("|");
        for(j=0;j<am->c;j++)
        {
            printf(" %d", am->mat[i][j]);
        }
        printf(" |");
        printf("\n");
    }
    printf("+");
    for(affi=0;affi<= am->l;affi++)
    {
        printf("--");
    }
    printf("--");
    printf("+");
    printf("\n");
    return 0;
}

void transpose_mat(struct matrice *am, struct matrice *at)
{
    at->l = am->c;
    at->c = am->l;
    for (int i = 0; i < am->l; i++)
    {
        for (int j = 0; j < am->c; j++)
        {
            at->mat[j][i] = am->mat[i][j];
        }
    }
}

int main()
{
    system("cls");
    struct matrice mat, mat_transpose;
    mat.c = saisie_entier(0, 9);
    mat.l = saisie_entier(0, 9);

    init_alea_mat(&mat);
    printf("Matrice originale :\n");
    affichage_mat(&mat);

    transpose_mat(&mat, &mat_transpose);
    printf("Matrice transposee :\n");
    affichage_mat(&mat_transpose);

    return 0;
}
