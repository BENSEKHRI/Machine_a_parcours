#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe_parcours.h"
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"

void graphviz (char* nom_fichier) {
	char cmd[100] = "dot -Tx11 ";
	strcat(cmd, nom_fichier);
	system(cmd);
}

int graphe_parcours_profondeur(graphe *g, graphe **arbo, int **suff, int *prio)
{
	// Création du parcours
	// Le conteneur qui est une pile pour un DFS
  conteneur_sommets *cs = cs_creer_pile (graphe_get_n(g));
  if(cs == NULL) {
    perror("- Erreur: graphe_parcours_profondeur - creation cs\n");
    return -1;
  }
  parcours *p = pc_init(g, cs, prio);
  if(p == NULL) {
    perror("- Erreur: graphe_parcours_profondeur - creation p\n");
    cs_detruire(cs);
    return -1;
  }

	// Parcours DFS
  pc_parcourir(p);

	int taille = graphe_get_n(g);

  (*arbo) = (p->arbo);
  (*suff) = file_tabint(p->suffixe, &taille);

	pc_detruire(p);
  return 0;
}

int graphe_parcours_profondeur2(graphe *g, graphe **arbo, int **suff, int *prio, int** racine, int** pref)
{
	// Création du parcours
	// Le conteneur qui est une pile pour un DFS
  conteneur_sommets *cs = cs_creer_pile (graphe_get_n(g));
  if(cs == NULL) {
    perror("- Erreur: graphe_parcours_profondeur2 - creation cs\n");
    return -1;
  }
  parcours *p = pc_init(g, cs, prio);
  if(p == NULL) {
    perror("- Erreur: graphe_parcours_profondeur2 - creation p\n");
    cs_detruire(cs);
    return -1;
  }

	// Parcours DFS
  pc_parcourir(p);
	int taille = graphe_get_n(g);

	(*arbo) = (p->arbo);
	(*suff) = file_tabint(p->suffixe, &taille);
	(*racine) = file_tabint(p->racine_courante, &taille);
	(*pref) = file_tabint(p->prefixe, &taille);

	pc_detruire(p);
  return 0;
}

int graphe_parcours_largeur(graphe *g, graphe **arbo, int **suff, int *prio)
{
	// Création du parcours
	// Le conteneur qui est une file pour un BFS
  conteneur_sommets *cs = cs_creer_file (graphe_get_n(g));
  if(cs == NULL) {
    perror("- Erreur: graphe_parcours_largeur - creation cs\n");
    return -1;
  }

  parcours *p = pc_init(g, cs, prio);
  if(p == NULL) {
    perror("- Erreur: graphe_parcours_largeur - creation p\n");
    cs_detruire(cs);
    return -1;
  }

	// Parcours BFS
  pc_parcourir(p);

	int taille = graphe_get_n(g);

  (*arbo) = (p->arbo);
  (*suff) = file_tabint(p->suffixe, &taille);

	pc_detruire(p);
  return 0;
}

int graphe_parcours_largeur2(graphe *g, graphe **arbo, int **suff, int *prio, int** racine, int** pref, int** peres, int** distance_dep, int debut)
{
	// Création du parcours
	// Le conteneur qui est une file pour un BFS
  conteneur_sommets *cs = cs_creer_file (graphe_get_n(g));
  if(cs == NULL) {
    perror("- Erreur: graphe_parcours_largeur2 - creation cs\n");
    return -1;
  }

  parcours *p = pc_init(g, cs, prio);
  if(p == NULL) {
    perror("- Erreur: graphe_parcours_largeur2 - creation p\n");
    cs_detruire(cs);
    return -1;
  }

	// Parcours BFS
  pc_parcourir2(p, debut);

	int taille = graphe_get_n(g);

	(*arbo) = (p->arbo);
	(*suff) = file_tabint(p->suffixe, &taille);
	(*racine) = file_tabint(p->racine_courante, &taille);
	(*pref) = file_tabint(p->prefixe, &taille);
	(*peres) = p->peres;
	(*distance_dep) = p->distances;

	pc_detruire2(p);
  return 0;
}

int graphe_parcours_larg_ou_prof(graphe *g, graphe **arbo, int **suff, int *prio)
{
	// Création du parcours
	// Le conteneur qui est une pile ou une fille (c'est aléatoire) => nouveau parcour
  conteneur_sommets *cs = cs_creer_pile_ou_file (graphe_get_n(g));
  if(cs == NULL) {
    perror("- Erreur: graphe_parcours_larg_ou_prof - creation cs\n");
    return -1;
  }

	// Le parcour qui commence par debut
  parcours *p = pc_init(g, cs, prio);
  if(p == NULL) {
    perror("- Erreur: graphe_parcours_larg_ou_prof - creation p\n");
    cs_detruire(cs);
    return -1;
  }

	// Parcours DFS && BFS (autre)
  pc_parcourir(p);

	int taille = graphe_get_n(g);

	(*arbo) = (p->arbo);
	(*suff) = file_tabint(p->suffixe, &taille);

	pc_detruire(p);
  return 0;
}

void tab_inverser (int* res, int* src, int taille) {
  int j = taille - 1;
  for (int i = 0; i < taille; i++) {
    res[i] = src[j];
    j--;
  }
}

int graphe_ordre_top(graphe *g, int **ordre_top)
{
	int n = graphe_get_n(g);
	graphe* arbo;
	int* suff;

	// On fait un parcours en profondeur
	int test = graphe_parcours_profondeur(g, &arbo, &suff, NULL);
	if (test != 0) {
		printf("- Erreur: graphe_ordre_top - parcour en prof non réussi\n");
		return test;
	}

	int *suffixe_inverse = (int*) malloc(n * sizeof(int));
	if(suffixe_inverse == NULL) {
		printf("- Erreur: graphe_ordre_top - malloc suffixe_inverse\n");
		graphe_liberer(arbo);
		free(suff);
		return -1;
	}
	// On inverse l'ordre suffixe trouvé
	tab_inverser(suffixe_inverse, suff, n);

	// On teste si il y a des arc arrières
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if(graphe_get_multiplicite_arc(g, suffixe_inverse[i], suffixe_inverse[j]) != 0) {
				(*ordre_top) = NULL;
				graphe_liberer(arbo);
				free(suff);
				free(suffixe_inverse);
				return -2;
			}
		}
	}

	(*ordre_top) = suffixe_inverse;

	// Libération de mémoire.
	graphe_liberer(arbo);
	free(suff);
	return 0;
}

void graphe_transpose (graphe* g, graphe* res) {
	msuc* m, *suiv;
	int n = graphe_get_n(g);

	for (int i = 0; i < n; i++) {
		m = g->tab_sucs[i];
		while(m) {
			// On change l'orientation des arcs en ajoutant au graphe res des arc
			// de l'autre cotés pour chaque successeur trouvé
			graphe_ajouter_arc(res, msuc_sommet(m), i, msuc_valeur(m));
			suiv = msuc_suivant(m);
			m = suiv;
		}
	}
}

int graphe_comp_fort_conn(graphe *g, int **reprs_cfc)
{
	int n = graphe_get_n(g), *suff, *suff2;

	graphe *g_transpose = graphe_creer(n, graphe_est_or(g)), *arbo, *arbo2;
	if(g_transpose == NULL) {
		printf("- Erreur: graphe_comp_fort_conn - Création g_transpose\n");
		return -1;
	}

	// On récupère le graphe transposé de g dans g_transpose
	graphe_transpose(g, g_transpose);

	// On fais un parcours en prof sur g_transpose
	int test = graphe_parcours_profondeur(g, &arbo, &suff, NULL);
	if (test != 0) {
		printf("- Erreur: graphe_comp_fort_conn - parcour en prof non réussi\n");
		graphe_liberer(g_transpose);
		return test;
	}

	int *suffixe_inverse = (int*) malloc(n * sizeof(int));
	if(suffixe_inverse == NULL) {
		printf("- Erreur: graphe_comp_fort_conn - malloc suffixe_inverse\n");
		graphe_liberer(g_transpose);
		graphe_liberer(arbo);
		free(suff);
		return -1;
	}

	// On récupère l'ordre suffixe inverse du DFS sur g
	tab_inverser(suffixe_inverse, suff, n);

	int* reprsantant; // la racine courante.
	int* pref;

	// On éffectue un DFS sur g_transpose avec comme prio suffixe_inverse
	test = graphe_parcours_profondeur2(g_transpose, &arbo2, &suff2, suffixe_inverse, &reprsantant, &pref);
	if (test != 0) {
		printf("- Erreur: graphe_comp_fort_conn - parcour en prof2 non réussi\n");
		graphe_liberer(g_transpose);
		return test;
	}

	int* tmp = calloc(n, sizeof(int));
	int j = 0;

	// Organisé les représentant de 0 à n. car dans la variable reprsantant ils
	// sont Organisé dans l'ordre pref. On les organise dans l'ordre 0 à n.
	for (int i = 0; i < n; i++) {
		j =pref[i];
		tmp[j] = reprsantant[i];
	}

	(*reprs_cfc) = tmp;

	// Libération des mémoires allouées
	free(suff);
	free(suff2);
	graphe_liberer(g_transpose);
	graphe_liberer(arbo);
	graphe_liberer(arbo2);
	free(reprsantant);
	free(pref);

  return 0;
}

int *graphe_distances_depuis_sommet(graphe *g, int rac)
{
	graphe* arbo;
	int *suff, *racine, *pref, *peres, *distance_dep;
	int debut = rac;

	int test = graphe_parcours_largeur2(g, &arbo, &suff, NULL, &racine, &pref,  &peres, &distance_dep, debut);
	if (test != 0) {
		printf("- Erreur: graphe_distances_depuis_sommet - parcour en largeur2 non réussi\n");
		return NULL;
	}

	// Affichage de l'arborescence pour vérification des distances.
	graphe_ecrire_dot(arbo, "../dot/graphe_BFS2.dot", 0);
	graphviz("../dot/graphe_BFS2.dot");

	// Libération des mémoires allouées
	graphe_liberer(arbo);
	free(suff);
	free(racine);
	free(pref);

  return distance_dep;
}

int max_tab (int* tab, int taille) {
	int max = 0;
	for (int i = 0; i < taille; i++) {
		// La valeur la plus grande est DIST_INF
		if(tab[i] == DIST_INF)
			return tab[i];
		if(max < tab[i])
			max = tab[i];
	}
	return max;
}

int max_2_elt (int a, int b) {
	// La valeur la plus grande est DIST_INF
	if(a == DIST_INF || b == DIST_INF)
		return a;
	if(a >= b)
		return a;
	else
		return b;
}

int graphe_diametre(graphe *g)
{
	int * distancesUn;
	int n = graphe_get_n(g);
	int max = 0, maxFinal = 0;

	for (int i = 0; i < n; i++) {
		// On Calcule les distances de tous les sommets vers tous les sommets et
		// on garde la plus grande valeur
		distancesUn = graphe_distances_depuis_sommet(g, i);
		if(distancesUn == NULL) {
			printf("- Erreur: allocation memoire.\n");
			return -2;
		}
		max = max_tab(distancesUn, n);
		printf("Tableau des distances à partir du sommet %d :\n", i);
		afficher_tab(distancesUn, n);
		printf("La distance la plus longue vaut: %d.\n\n", max);
		maxFinal = max_2_elt(max, maxFinal);
		free(distancesUn);
	}

	if(maxFinal == DIST_INF) {
		printf("Au moins une des arborescence des parcours en largeur effectues n'est pas fortement connexe !\n");
	}

  return maxFinal;
}
