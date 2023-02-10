#include <stdio.h>
#include <stdlib.h>
typedef int iTab;
typedef char cTab;

char colimacon(int n)
{
    int r,c = 'a',ligne = 0, colonne = 0,dr = 0, dc = 1;
    r=(n*n)+n;
    cTab s[r]; //initialisation s[]
    for (int i = 0; i < r; i++) {
        s[i] = ' '; // assigner "espace" a toutes les valeurs de s
    }
    s[r - 1] = '\0'; // assigner la dernière valeur de s le saut de ligne

    // remplir cTab s[] alphabet
    for (int i = 0; i < n*n; i++) 
    {
        s[ligne*(n+1) + colonne] = c;
        if (c == 'z') {
            c = 'A';
        } else if (c == 'Z') {
            c = 'a';
        } else c++;
        

        // On verifie si on doit changer de ligne
        int ligneSuivante = ligne + dr;
        int colonneSuivante = colonne + dc;
        if (ligneSuivante < 0 || ligneSuivante >= n || colonneSuivante < 0 || colonneSuivante >= n || s[ligneSuivante*(n+1) + colonneSuivante] != ' ') {
            int temp = dr;
            dr = dc;
            dc = -temp;
        }
        ligne += dr;
        colonne += dc;
    }

    // ajoute le saut de ligne 
    for (int i = 0; i < n; i++) {
        s[(i+1)*n + i] = '\n';
    }

    printf(" n = %d\n", n);
    printf("%s", s);
}

int main()
{
    //init
    int n;
    printf("Veuillez Entrez votre cote (n < 10): ");
    scanf("%d", &n);
    while (n > 10)
    {
        printf("La valeur n entré est trop grande veuillez entrer une valeur positif < 10 : ");
        scanf("%d", &n);
    }
    
    colimacon(n);
    return 0;
}

