#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50

int Calc=0;
int Compt=0;
unsigned long long bin(unsigned n, unsigned p)
{
    if(p > n) return 0;
    if(p == 0 || p == n) return 1;
    return (bin((n-1), p) + bin((n-1), (p-1)));
}

unsigned long long Cbin(unsigned n, unsigned p)
{
    if(p == 0 || p > n || p == n) return 1;
    return 2*bin(n,p) - 1;
}

unsigned bin_mem2(unsigned n,unsigned p,unsigned bin_tab[N][N])
{
    Calc++;
    if(p > n) return bin_tab [n][p] = 0;
    if(p == 0 || p == n) return bin_tab [n][p] = 1;
    if(bin_tab [n][p] != 0) return bin_tab [n][p];
    return bin_tab [n][p] = (bin_mem2((n-1), p, bin_tab) + bin_mem2((n-1), (p-1), bin_tab));
}


unsigned bin_mem(unsigned n,unsigned p)
{
    unsigned bin_tab [N][N] = {0};
    return bin_mem2(n,p,bin_tab);
}

unsigned bin_ter_2(unsigned n, unsigned p) 
{
    Compt++;
    if (p == 0 || p == n) return 1;
    if (p > n) return 0;
    return (bin_ter_2(n - 1, p - 1)) * n/p;
}


int main(int arg, char *argv[])
{
    system("cls");
    int n,p;
    printf("Entrez Vos votre (n,p) : ");
    scanf("%d,%d", &n,&p);
    time_t start = clock();
    printf("Binomial de bin(%d,%d) = %u",n,p,bin(n, p));
    time_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf(" [nbre d'appel %u] (recrusif naif), temps: %fs\n", Cbin(n, p), elapsed_time);
    time_t start2 = clock();
    printf("Binomial de bin_mem(%d,%d) = %u",n,p,bin_mem(n,p));
    time_t end2 = clock();
    double elapsed_time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf(" [nbre d'appel %u] (recrusif meoisien), temps: %fs\n", Calc, elapsed_time2);
    time_t start3 = clock();
    printf("Binomial de bin_ter(%d,%d) = %u",n,p, bin_ter_2(n,p));
    time_t end3 = clock();
    double elapsed_time3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf(" [nbre d'appel %u] (recrusif terminal), temps: %fs\n", Compt, elapsed_time3);

    return 0;
}