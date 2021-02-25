/**
 * \file parcours.h
 * \brief parcours générique d'un graphe représenté par des listes de
 * successeurs
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */

#ifndef PARCOURS_H
#define PARCOURS_H
#define DIST_INF -1

#include "graphe-4.h"
#include "conteneur_sommets.h"
#include "file.h"
#include "pile.h"

/**
 * \brief Structure parcours contenant des données utiles pendant et à la fin
 * d'un parcours générique
 */
typedef struct parcours {
  conteneur_sommets* conteneur; // le conteneur L
  graphe* arbo; // l'arboressance du parcours
  int* prio; // tableau de priorité pour le choix d'une racine
  file* prefixe;  // ordre de visite         M
  file* suffixe;  // ordre d'exploration     N
  graphe* graphe_a_parcourir;
  file* racine_courante;     /* racine coourante de chaque elt visité
                                NB: c'est dans l'ordre de visite 'M' */
  int* peres; /* pères de chaque sommet NB: c'est dans l'odre 0 ... n */
  int* distances; /* Les distances depuis un certain début
                        NB: c'est dans l'ordre 0 ... n */
} parcours;

/**
 * \brief Alloue de la mémoire pour une structure de parcours générique et
 * l'initialise de façon à pouvoir commencer un parcours sur un graphe, à l'aide
 * d'un conteneur de sommets donné et avec des priorités données pour les
 * racines.
 * \param g adresse du graphe (en lecture) dont on compte (par la suite)
 * faire le parcours
 * \param cs adresse du conteneur de sommets utilisé pour le parcours
 * \param prio tableau de priorités pour le choix des racines pendant le
 * parcours. Si ce paramètre est NULL, la priorité est par défaut 0, 1, 2, ...
 */
parcours *pc_init(graphe *g, conteneur_sommets *cs, int *prio);

/**
 * \brief Libère la mémoire associée à un parcours (ne fait rien si le paramètre
 * est NULL).
 */
void pc_detruire(parcours *p);

/**
 *                ------ fonction rajoutée -------
 *
 * \brief Libère la mémoire associée à un parcours (ne fait rien si le paramètre
 * est NULL).
 *
 *  Utilisé uniquement dans la fonction: "graphe_parcours_largeur2" car elle ne libère
 *  la mèmoire alloué par le parcours pour les distances.
 *  NB: la libération de mémoire pour le tableau p->distances est faites après
 *      l'appel de la fonction "graphe_parcours_largeur2"
 */
void pc_detruire2(parcours *p);

/**
 * \brief Choisit la prochaine racine du parcours en tenant compte des priorités
 * pour les choix des racines dans le parcours.
 */
int pc_choisir_racine(parcours *p);

/**
 * \brief Retourne 1 si le parcours est terminé (tous les sommets sont explorés)
 * et 0 sinon.
 */
int pc_est_fini(parcours *p);

/**
 * \brief Marque le sommet \a sommet comme étant visité.
 */
void pc_marquer_comme_visite(parcours *p, int sommet);

/**
 * \brief Marque le sommet \a sommet comme étant visité lors d'un parcours depuis
 * la racine \a depuis.
 */
void pc_marquer_comme_visite_depuis(parcours *p, int sommet, int depuis);

/**
 * \brief Marque le sommet \a sommet comme étant exploré.
 */
void pc_marquer_comme_explore(parcours *p, int sommet);
/**
 * \brief Etat du conteneur
 * \return 1 si le conteneur est vide, 0 sinon.
 */
int pc_conteneur_est_vide(parcours *p);
/**
 * \brief Ajoute le sommet \a sommet au conteneur de sommets
 */
void pc_ajouter_dans_conteneur(parcours *p, int sommet);
/**
 * \brief Choisit un sommet dans le conteneur de sommets,
 * selon les règles de ce conteneur.
 * \return le sommet choisi.
 */
int pc_choisir_dans_conteneur(parcours *p);
/**
 * \brief Supprime du conteneur le dernier sommet choisi.
 */
void pc_supprimer_du_conteneur(parcours *p);

/**
 * \brief choisit dans la liste de ses successeurs le prochain maillon de
 * successeur du sommet \a sommet.
 *
 * Cette fonction sert à s'assurer qu'on ne parcourt
 * la liste des successeur d'un sommet
 * qu'une et une seule fois.
 */
msuc *pc_prochain_msuc(parcours *p, int sommet);
/**
 * \brief Indique si le sommet \a sommet a déjà été visité
 * \return 1 si oui, 0 sinon.
 */
int pc_est_visite(parcours *p, int sommet);

/***________________Description modifiée___________________________*/
/*
 * \brief Parcourt le graphe en prenant le sommet \a r comme racine du
 * parcours et en s'arrêtant lorsque tous les sommets accessibles depuis \a r
 * sont parcourus.
 *
 * "  La fonction permet notamment de remplir le champ p->racine_courante du Parcours
 *    c-a-d pour chaque sommet nous connaissons sa racine. "
 *
 * Pré-condition : le conteneur de sommets associé au parcours doit être vide à
 * l'appel de cette fonction.
 * Pré-condition : le conteneur de sommets associé au parcours est vide après
 * l'appel de cette fonction.
 */
void pc_parcourir_depuis_sommet(parcours *p, int r);


/** \brief Parcourt entièrement le graphe associé à \a p.
 *
 * Les priorités pour le choix des racines sont données par le tableau \a prio
 * renseigné à l'appel de \a pc_init.
 */
void pc_parcourir(parcours *p);

/***________________Fonctions rajoutées___________________________*/
/*
 * \brief Parcourt le graphe en prenant le sommet \a r comme racine du
 * parcours et en s'arrêtant lorsque tous les sommets accessibles depuis \a r
 * sont parcourus.
 *
 * "  La fonction permet notamment de remplir le champ p->peres du Parcours
 *    c-a-d pour chaque sommet nous connaissons son père. Et le champ p->distances
 *    a partir du sommet debut
 *    Cette fonctions est appelé par la fonction pc_parcourir2 qui elle même
 *    appelé par la fonction "graphe_parcours_largeur2" et celà sert pour
 *    la question 7 (application du parcours en largeur)."
 *
 * Pré-condition : le conteneur de sommets associé au parcours doit être vide à
 * l'appel de cette fonction.
 * Pré-condition : le conteneur de sommets associé au parcours est vide après
 * l'appel de cette fonction.
 *
 * @param p le parcours
 * @param r la racine depuis la quelle parcour tous ces sommets
 * @param debut sert pour calculer les distances, le champs p->distances
 *              contient toutes les distances depuis debut à [0 ... n].
 *
 */
void pc_parcourir_depuis_sommet2(parcours *p, int r, int debut);


/***________________Fonctions rajoutées___________________________*/
/*
 * \brief Parcourt entièrement le graphe associé à \a p.
 *
 * Les priorités pour le choix des racines sont données par le tableau \a prio
 * renseigné à l'appel de \a pc_init mais cela juste après le choix de la
 * prémière racine qui est debut
 *
 * @param p le parcours
 * @param debut la racine d'ou commencer le parcours.
 */
void pc_parcourir2(parcours *p, int debut);


/***________________Fonctions rajoutées___________________________*/
/**
 *  Cette fonction permet l'affichage d'un tableau d'entier
 * @param tab le tableau d'entiers à afficher.
 * @param taille la taille du tableau.
 */
void afficher_tab (int * tab, int taille);

#endif
