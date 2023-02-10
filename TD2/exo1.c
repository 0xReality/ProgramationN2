#include <stdio.h>
#include <math.h>
#include <time.h>

unsigned int Global=0; 
unsigned int Global2=0;
unsigned int Global3=0;
unsigned int Global4=0;

int puiss(double x, unsigned n)
{
    int i,res=x;
    for(i=1;i<n;i++) 
    {
        res=res*x;
    }
    printf("%d", res);
}

double puiss_rec(double x, unsigned n)
{
  if(n == 0) return 1;
  else{
    Global2+=1;
    return x*puiss_rec(x, (n-1));
  }
}   

double puiss_rap(double x, unsigned n) 
{
  if (n == 0) return 1;
  if (n % 2 == 0) {
    double y = puiss_rap(x, n/2);
    Global +=1; 
    printf("La valeur vaut:");
    return y * y;
  } else {
    double y = puiss_rap(x, (n-1)/2);
    Global +=1;
    printf("La valeur vaut: ");
    return x * y * y;
  }
}

double aux(double x, unsigned n, double res) 
{
  if (n == 1){
    Global3+=1;
    return res * x;
  }else{
    Global3+=1;
    return aux(x, n-1, res * x);
  }

}

double puiss_ter(double x, unsigned n) {
  double res = 1.0;
  if (n == 0) return res;
  return aux(x, n, res);
}

double puiss_rap_ter_aux(double x, unsigned n, double res) 
{
    if (n == 0) 
    {
      Global4+=1;
      return res;
    }
    if (n % 2 == 0) 
    {
      Global4+=1;
      return puiss_rap_ter_aux(x * x, n / 2, res);
    }
      Global4+=1;
    return puiss_rap_ter_aux(x * x, (n-1) / 2, res * x);
}

double puiss_rap_ter(double x, unsigned n) {
    return puiss_rap_ter_aux(x, n, 1);
}

int main()
{  
  double x;
  int n;
  printf("Veuillez Entrer la valeur de x et n (format x,n): ");
  scanf("%lf,%d", &x,&n);

  // Calcul le temp passé sur puiss_rap
  clock_t start = clock();
  printf("%lf", puiss_rap(x, n));  
  clock_t end = clock();
  double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("\nTemp passe sur puiss_rap: %f\n", elapsed_time);
  //Calcule puiss_rec et son temp passé
  clock_t start2 = clock();
  printf("%lf", puiss_rec(x, n));  
  clock_t end2 = clock();
  double elapsed_time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
  printf("\nTemp passe sur puiss_rec: %f\n", elapsed_time2);

  //calcule la diff entre recusive et rapide
  if(elapsed_time2 > elapsed_time)
  {
    double diff = elapsed_time2 - elapsed_time;
    printf("\nDifference en seconde: %f\n", diff);
    printf("puiss_rec etais le plus rapide !\n");
  }else{
    double diff = elapsed_time - elapsed_time2;
    printf("\nDifference en seconde: %f\n", diff);
    printf("puiss_rap etais le plus rapide !\n");
  }

  printf("il y a eu %d recrusivite sur puiss_rap, et ", Global);
  printf("il y a eu %d recrusivite sur puiss_rap, et ", Global2);
  printf("il y a eu %d recrusivite sur puiss_ter\n", Global3);
  printf("il y a eu %d recrusivite sur puiss_rap_ter\n", Global4);

  clock_t start3 = clock();
  printf("%lf", puiss_ter(x,n));
  clock_t end3 = clock();
  double elapsed_time3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
  printf("\nTemp passe sur puiss_ter: %f\n", elapsed_time3);

  clock_t start4 = clock();
  printf("%lf", puiss_rap_ter(x,n));
  clock_t end4 = clock();
  double elapsed_time4 = (double)(end4 - start4) / CLOCKS_PER_SEC;
  printf("\nTemp passe sur puiss_rap_ter: %f\n", elapsed_time4);

  return 0;
}
