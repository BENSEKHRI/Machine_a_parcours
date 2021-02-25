#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"
#include "graphe_parcours.h"

int main()
{
	graphe *g, *arbo;
	int *suff;

	g = graphe_creer(10,1);
	graphe_ajouter_arc(g, 0, 8, 1.0);
	graphe_ajouter_arc(g, 0, 6, 1.0);
	graphe_ajouter_arc(g, 0, 5, 1.0);
	graphe_ajouter_arc(g, 0, 1, 1.0);
	graphe_ajouter_arc(g, 1, 8, 1.0);
	graphe_ajouter_arc(g, 1, 2, 1.0);
	graphe_ajouter_arc(g, 2, 9, 1.0);
	graphe_ajouter_arc(g, 2, 7, 1.0);
	graphe_ajouter_arc(g, 2, 6, 1.0);
	graphe_ajouter_arc(g, 2, 4, 1.0);
	graphe_ajouter_arc(g, 2, 2, 1.0);
	graphe_ajouter_arc(g, 2, 1, 1.0);
	graphe_ajouter_arc(g, 2, 0, 1.0);
	graphe_ajouter_arc(g, 3, 8, 1.0);
	graphe_ajouter_arc(g, 3, 3, 1.0);
	graphe_ajouter_arc(g, 4, 8, 1.0);
	graphe_ajouter_arc(g, 4, 5, 1.0);
	graphe_ajouter_arc(g, 4, 4, 1.0);
	graphe_ajouter_arc(g, 5, 9, 1.0);
	graphe_ajouter_arc(g, 5, 7, 1.0);
	graphe_ajouter_arc(g, 5, 6, 1.0);
	graphe_ajouter_arc(g, 5, 5, 1.0);
	graphe_ajouter_arc(g, 5, 2, 1.0);
	graphe_ajouter_arc(g, 5, 1, 1.0);
	graphe_ajouter_arc(g, 6, 6, 1.0);
	graphe_ajouter_arc(g, 6, 4, 1.0);
	graphe_ajouter_arc(g, 6, 0, 1.0);
	graphe_ajouter_arc(g, 7, 9, 1.0);
	graphe_ajouter_arc(g, 7, 6, 1.0);
	graphe_ajouter_arc(g, 7, 1, 1.0);
	graphe_ajouter_arc(g, 8, 8, 1.0);
	graphe_ajouter_arc(g, 8, 6, 1.0);
	graphe_ajouter_arc(g, 8, 5, 1.0);
	graphe_ajouter_arc(g, 8, 1, 1.0);
	graphe_ajouter_arc(g, 9, 6, 1.0);

	/* Graphe */
	printf("   _______________________________________\n");
	printf("  /                                      /\n");
	printf(" /                GRAPHE                /\n");
	printf("/______________________________________/\n");
	graphe_ecrire_dot(g, "../dot/graphe_depart.dot", 0);

	// Affichage du graphe
	graphviz("../dot/graphe_depart.dot");


	/* Parcours en profondeur d'abord */
	printf("   _______________________________________\n");
	printf("  /                                      /\n");
	printf(" /        Parcours en profondeur        /\n");
	printf("/______________________________________/\n");

	graphe_parcours_profondeur(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "../dot/parcours_prof.dot", 0);

	// Affichage de l'arboressance
	graphviz("../dot/parcours_prof.dot");

	// Affichage de l'odre suffixe
	printf("Ordre Suffixe:\n");
	for (int i = 0; i < graphe_get_n(g); i++) {
		printf("%d\t", suff[i]);
	}
	printf("\n");

	// libération de la mémoire
	free(suff);
	graphe_liberer(arbo);


	/* Parcours en largeur d'abord */
	printf("   _______________________________________\n");
	printf("  /                                      /\n");
	printf(" /         Parcours en largeur          /\n");
	printf("/______________________________________/\n");

	graphe_parcours_largeur(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "../dot/parcours_largeur.dot", 0);

	// Affichage de l'arboressance
	graphviz("../dot/parcours_largeur.dot");

	// Affichage de l'odre suffixe
	printf("Ordre Suffixe:\n");
	for (int i = 0; i < graphe_get_n(g); i++) {
		printf("%d\t", suff[i]);
	}
	printf("\n");

	free(suff);
	graphe_liberer(arbo);


	/* Parcours en largeur d'abord */
	printf("   _______________________________________\n");
	printf("  /                                      /\n");
	printf(" / Parcours en largeur && || profondeur /\n");
	printf("/______________________________________/\n");

	/* Parcours utilisant la structure pile_ou_file */
	graphe_parcours_larg_ou_prof(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "../dot/parcours_larg_ou_prof.dot", 0);


	// Affichage de l'arboressance
	graphviz("../dot/parcours_larg_ou_prof.dot");

	// Affichage de l'odre suffixe
	printf("Ordre Suffixe:\n");
	for (int i = 0; i < graphe_get_n(g); i++) {
		printf("%d\t", suff[i]);
	}
	printf("\n");

	free(suff);
	graphe_liberer(arbo);
	graphe_liberer(g);

	return EXIT_SUCCESS;
}
