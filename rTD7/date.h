#ifndef DATE_H /* garde d'inclusion */
#define DATE_H

struct date {
	unsigned jour;
	unsigned mois;
	unsigned annee;
};

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* initialise la structure champ par champ et renvoie l'adresse du bloc alloué */
struct date * allouer_init_date(unsigned, unsigned, unsigned);

/** Fonction qui (ré)initialise une date champ par champ */
/** et renvoie l'adresse de la date ainsi créée et initialisée */
void affecter_date(struct date *, unsigned j, unsigned m, unsigned int a);

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date *);

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date *d1, const struct date * d2);

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date **);

/** Fonction qui renvoie le nombre de jours en février de l'année passée en argument */
int nbre_jours_fev (int);

/** Fonction qui renvoie le nombre de jours du mois passé en argument */
/* (selon l'année passée en argument) */
int nbre_jours_mois (int, int);

/** Fonction qui avance la date passée en argument au lendemain */
void lendemain (struct date *);

/** Fonction qui renvoie la date courante */
struct date ce_jour (void);

#endif
