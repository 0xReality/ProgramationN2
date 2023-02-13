// Code par Christophe Tollu
/* Ce programme lit une largeur (une valeur entière paire comprise entre 0 et 40) */
/* entrée au clavier par l'utilisateur puis affiche le patchwork de cette largeur */
#include <stdlib.h>
#include <stdio.h>

#define N 40 /* taille maximale du dessin */

int saisie_entier_pair(int, int);
char motif_carre_NO_SE(int, int, int);
char motif_carre_SO_NE(int, int, int);
char patchwork(int, int, int);

int main()
{
    int ligne;
    int n;
    printf("Entrez la largeur du côté du patchwork :\n");
    n = saisie_entier_pair(0, N);

    /* balayage et affichage de la zone occupée par le patchwork */
    ligne = 0;
    while (ligne < n)
    {
        int colonne = 0;
        while (colonne < n)
        {
            putchar(patchwork(ligne, colonne, n));
            colonne = colonne + 1;
        }
        putchar('\n');
        ligne = ligne + 1;
    }

    return EXIT_SUCCESS;
}

/** Renvoie le caractère qui se trouve à l'intersection de */
/*  - la ligne d'indice le premier paramètre d'entrée */
/*  - la colonne d'indice le deuxième paramètre d'entrée */
/*  dans le carré NO ou SE du patchwork de largeur égale au troisième paramètre d'entrée */
/* SI LES LIGNES ET LES COLONNES SONT INDICÉES À PARTIR DE ZÉRO */
char motif_carre_NO_SE(int ligne, int col, int cote)
{
  if (0 == col || 0 == ligne || cote - 1 == col || cote - 1 == ligne)
    return '*';
  return ' ';
}

/** Renvoie le caractère qui se trouve à l'intersection de */
/*  - la ligne d'indice le premier paramètre d'entrée */
/*  - la colonne d'indice le deuxième paramètre d'entrée */
/*  dans le carré SO ou NE du patchwork de largeur égale au troisième paramètre d'entrée */
/* SI LES LIGNES ET LES COLONNES SONT INDICÉES À PARTIR DE ZÉRO */
char motif_carre_SO_NE(int ligne, int col, int cote)
{
  if ((col + ligne)%2 == 1)
    return '+';
  return 'o';
}

/** Renvoie le caractère qui se trouve à l'intersection de */
/*  - la ligne d'indice le premier paramètre d'entrée */
/*  - la colonne d'indice le deuxième paramètre d'entrée */
/*  dans le patchwork de largeur égale au troisième paramètre d'entrée */
/* SI LES LIGNES ET LES COLONNES SONT INDICÉES À PARTIR DE ZÉRO */
char patchwork(int ligne, int col, int cote)
{
  if (ligne < cote/2 && col < cote/2)
    return motif_carre_NO_SE(ligne, col, cote/2);
  if (ligne >= cote/2 && col >= cote/2)
    return motif_carre_NO_SE(ligne - cote/2, col - cote/2, cote/2);
  if (ligne >= cote/2 && col < cote/2)
    return motif_carre_SO_NE(ligne - cote/2, col, cote/2);
  /* if (ligne < cote/2 && col >= cote/2) */
  return motif_carre_SO_NE(ligne, col - cote/2, cote/2);
}

/* Lit une valeur entière entrée au clavier par l'utilisateur */
/* et renvoie cette valeur si elle est paire et comprise entre vmin et vmax */
/* (Dans le cas contraire, demande à l'utilisateur de recommencer) */
int saisie_entier_pair (int vmin, int vmax) {
  int res, n;
  char c;
  do
  {
    printf("Tapez une valeur entière paire comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax && 0 == res%2)
      return res;
    /* si la lecture d'une valeur entière a échoué... */
    if (0 == n)
    {
      /* ...on "avale" la fin de la chaîne entrée au clavier par l'utilisateur */
      /* avant de lui demander de recommencer */
			do {scanf("%c", &c);}
			while (c != ' ' && c != '\t' && c != '\n');
    }
    printf("Erreur ! Recommencez !");
  }
  while (1);
}
