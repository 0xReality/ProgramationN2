#include "date.h"
#include <stdio.h> /* pour printf, perror */
#include <stdlib.h> /* pour EXIT_FAILURE, exit, malloc, free */
#include <time.h> /* pour time_t, struct tm, time et localtime */

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* initialise la structure champ par champ et renvoie l'adresse du bloc alloué */
struct date * allouer_init_date(unsigned j, unsigned m, unsigned a) {
	struct date * res = malloc(sizeof(struct date));
	if (res == NULL) {
		perror("Échec allocation date");
		exit(EXIT_FAILURE);
	}
	res->jour = j;
	res->mois = m;
	res->annee = a;
	return res;
}

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date * d) {
	printf("%u/%u/%u", d->jour, d->mois, d->annee);
}

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date * d1, const struct date * d2) {
	if(d1->annee < d2->annee)
		return -1;
	if (d1->annee > d2->annee)
		return 1;
	if (d1->mois < d2->mois)
		return -1;
	if (d1->mois > d2->mois)
		return 1;
	if (d1->jour < d2->jour)
		return -1;
	if (d1->jour > d2->jour)
		return 1;
	return 0;
}

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date ** d) {
	free(*d);
	*d = NULL;
}

/** Fonction qui renvoie le nombre de jours en février de l'année passée en argument */
int nbre_jours_fev (int annee) {
  if (annee%400 == 0 || (annee%4 == 0 && annee%100 > 0))
    return 29;
  return 28;
}

/** Fonction qui renvoie le nombre de jours du mois passé en argument */
/* (selon l'année passée en argument) */
int nbre_jours_mois (int mois, int annee) {
  if (mois == 4 || mois == 6 || mois == 9 || mois == 11)
    return 30;
  if (mois == 2)
    return nbre_jours_fev(annee);
  return 31;
}

/** Fonction qui avance la date passée en argument au lendemain */
void lendemain (struct date *d) {
  if (++d->jour > nbre_jours_mois(d->mois, d->annee)) {
		d->jour = 1;
		if (++d->mois > 12) {
			d->mois = 1;
			++d->annee;
		}
	}
}

/** Fonction qui renvoie la date courante */
struct date ce_jour (void) {
  struct date res;
  time_t maintenant;
  struct tm *local;

  time(&maintenant);
  local = localtime(&maintenant);
  res.jour = (unsigned) local->tm_mday;
  res.mois = (unsigned) local->tm_mon + 1;
  res.annee = (unsigned) local->tm_year + 1900;
  return res;
}