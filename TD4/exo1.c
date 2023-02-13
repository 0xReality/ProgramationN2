#include <stdio.h>
#include <stdlib.h>
typedef int item;


int saisie_entier(int vmin, int vmax) 
{
  int res, n;
  char c;
  do
  {
    printf("Tapez une valeur entière paire comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    if (0 == n)
    {
			do {scanf("%c", &c);}
			while (c != ' ' && c != '\t' && c != '\n');
    }
    printf("Erreur ! Recommencez !");
  }
  while (1);
}

int init_alea_tab(item *tab, int taille)
{
    int seed = 2732;
    srand(seed); 
    for (int i = 0; i < taille; i++) {
        tab[i] = rand();
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}

int pos_min_tab(item *tab, int n)
{
    int min = tab[0];
    for (int i = 1; i < n; i++) {
        if (tab[i] < min) min = tab[i];
    }
    printf("\nle minimum du tableau est : %d\n", min);
    return 0;
}

int pos_max_tab(item *tab, int n)
{
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (tab[i] > max) max = tab[i];
    }
    printf("\nle maximum du tableau est : %d\n", max);
    return 0;
}

int max_difference(int *tab, int n) {
  int i, j;
  int max_diff = 0;
  for (i = 0; i < n; i++)
  {
    for (j = i + 1; j < n; j++) 
    {
      int diff = tab[j] - tab[i];
      if (diff > max_diff) max_diff = diff;
    }
   }
  printf("\n%d", max_diff);
}


int main()
{
  int i, n = saisie_entier(0, 20);
  item tab[n];
  i = init_alea_tab(tab, n);
  printf("%d", pos_min_tab(tab, n));
  printf("%d", pos_max_tab(tab, n));
  printf("%d", max_difference(tab, n));

  return 0;
}


