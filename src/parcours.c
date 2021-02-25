#include <stdlib.h>
#include <stdio.h>
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"
#define DIST_INF -1


parcours *pc_init(graphe *g, conteneur_sommets *cs, int *prio)
{
  int n = graphe_get_n(g);
  parcours* res = (parcours*) malloc (sizeof(parcours));

  res->conteneur = cs;
  res->arbo = graphe_creer(n, graphe_est_or(g));

  int pos = 0;
  if(prio == NULL) {
    pos = 1;
    res->prio = (int*) malloc (n * sizeof(int));
    for (int i = 0; i < n; i++) {
      res->prio[i] = i;
    }
  }
  else
    res->prio = prio;

  res->prefixe = file_creer(n);
  res->suffixe = file_creer(n);
  res->graphe_a_parcourir = g;
  res->racine_courante = file_creer(n);
  res->peres = (int*) malloc(n * sizeof(int));
  // On initialise les elts de peres et distances à -5 pour les besoins d'autre fonctions
  // Car nous savons qu'aucun sommet ne sera -5.
  for (int i = 0; i < n; i++) {
    res->peres[i] = -5;
  }
  res->distances = (int*) malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    res->distances[i] = -5;
  }
  // Si une des allocation mémoire a échoué, on retourne NULL et on libère toutes les allocation mémoire réussi.
  if((!res) || (!res->arbo) || (!res->prio && pos == 1) || (!res->prefixe) || (!res->suffixe) || (!res->graphe_a_parcourir) || (!res->racine_courante) || (!res->peres) || (!res->distances)) {
    printf("- Erreur: NULL || malloc || calloc || creation -*- in pc_init -\n");
    return NULL;
  }

  return res;
}

void pc_detruire(parcours *p)
{
  if(p != NULL) {
    cs_detruire(p->conteneur);
    if(p->prio)
      free(p->prio);
    file_detruire(p->prefixe);
    file_detruire(p->suffixe);
    file_detruire(p->racine_courante);
    free(p->peres);
    free(p->distances);
    free(p);
  }
}

void pc_detruire2(parcours *p)
{
  if(p != NULL) {
    cs_detruire(p->conteneur);
    if(p->prio)
      free(p->prio);
    file_detruire(p->prefixe);
    file_detruire(p->suffixe);
    file_detruire(p->racine_courante);
    free(p->peres);
    free(p);
  }
}

int pc_choisir_racine(parcours *p)
{
  int racine = p->prio[0];
  if(!(pc_est_visite(p, racine)))
    return racine;
  int i = 1;
  while((pc_est_visite(p, racine)) && (i < graphe_get_n(p->graphe_a_parcourir))) {
    racine = p->prio[i];
    i++;
  }
  return racine;
}

int pc_est_fini(parcours *p)
{
  if(file_taille(p->suffixe) == graphe_get_n(p->graphe_a_parcourir))
    return 1;
  return 0;
}

void pc_marquer_comme_visite(parcours *p, int sommet)
{
  file_enfiler(p->prefixe, sommet);
}

void pc_marquer_comme_visite_depuis(parcours *p, int sommet, int depuis)
{
  /* TODO : à implémenter */  // Non Utilisé Dans le projet !
}

void pc_marquer_comme_explore(parcours *p, int sommet)
{
  file_enfiler(p->suffixe, sommet);
}

int pc_conteneur_est_vide(parcours *p)
{
  return cs_est_vide(p->conteneur);
}

void pc_ajouter_dans_conteneur(parcours *p, int sommet)
{
  cs_ajouter(p->conteneur, sommet);
}

void pc_supprimer_du_conteneur(parcours *p)
{
  cs_supprimer(p->conteneur);
}

int pc_choisir_dans_conteneur(parcours *p)
{
  return cs_choisir(p->conteneur);
}

msuc *pc_prochain_msuc(parcours *p, int sommet)
{
  return msuc_suivant(p->graphe_a_parcourir->tab_sucs[sommet]);
}

int pc_est_visite(parcours *p, int sommet)
{
  for (int i = 0; i < file_taille(p->prefixe); i++) {
    if(sommet == p->prefixe->tab[i])
      return 1;
  }
  return 0;
}

void pc_parcourir_depuis_sommet(parcours *p, int r)
{
  // Ajouter r au conteneur
  pc_ajouter_dans_conteneur(p, r);

  // Ajouter la racine courante
  file_enfiler(p->racine_courante, r);

  // Marquer r comme visité
  pc_marquer_comme_visite(p, r);
  // Tant que le conteneur n'est pas vide
  while(!cs_est_vide(p->conteneur)) {
    // Choisir un sommet v dans le conteneur
    int v = cs_choisir(p->conteneur);
    msuc* suc = p->graphe_a_parcourir->tab_sucs[v];
    msuc * suiv;
    // Voir les successeurs non visité de v et choisir un si présent
    while (suc && pc_est_visite(p, msuc_sommet(suc))) {
      suiv = msuc_suivant(suc);
      suc = suiv;
    }
    // Si v a des successeurs non visité, alors
    if(suc != NULL && !pc_est_visite(p, msuc_sommet(suc))) {
      // Choisir un tel succeseur
      int w = msuc_sommet(suc);

      // Création de l'arboressance
      // Si le graphe etudié est non orienté
      if (!graphe_est_or(p->graphe_a_parcourir)) {
          graphe_ajouter_arete(p->arbo, v, w, msuc_valeur(suc));
      }
      // Sinon
      else {
        graphe_ajouter_arc(p->arbo, v, w, msuc_valeur(suc));
      }

      // Ajouter la racine courante pour le sommet visité.
      file_enfiler(p->racine_courante, r);
      // Marquer w comme visité
      pc_marquer_comme_visite(p, w);
      // Ajouter w au conteneur
      pc_ajouter_dans_conteneur(p, w);
    }
    // Sinon
    else {
      // Marquer v comme exploré
      pc_marquer_comme_explore(p, v);
      // enlever v du conteneur
      pc_supprimer_du_conteneur(p);
    }
    // FinSI
  }
  // FinTantQue
}

void pc_parcourir(parcours *p)
{
  // Initialisation:
  // Le conteneur de sommet est vide.
  while(!cs_est_vide(p->conteneur)) {
    cs_supprimer(p->conteneur);
  }
  // Aucun sommet n'est visité.
  while(!file_est_vide(p->prefixe)) {
    file_defiler(p->prefixe);
  }
  // Aucun sommet n'est exploré.
  while(!file_est_vide(p->suffixe)) {
    file_defiler(p->suffixe);
  }

  int r = 0;
  // Tant que tous les sommets ne sont pas explorés,
  while (!pc_est_fini(p)) {
    // Choisir une racine r parmi les sommet non visités,
    r = pc_choisir_racine(p);

    pc_parcourir_depuis_sommet(p, r);

  }
  // FinTantQue
}

void pc_parcourir_depuis_sommet2(parcours *p, int r, int debut)
{
  // Ajouter r au conteneur
  pc_ajouter_dans_conteneur(p, r);

  // Ajouter la racine courante
  file_enfiler(p->racine_courante, r);

  // Si on change de racine c'est a dire que le graphe n'est pas fortement connexe
  // donc la distance entre le debut et l'autre racine est DIST_INF
  if(r != debut)
    p->distances[r] = DIST_INF;
  else
    p->distances[r] = 0;
  // On ajouter le père de la racine r qui est r a l'indice r.
  p->peres[r] = r;

  // Marquer r comme visité
  pc_marquer_comme_visite(p, r);

  // Tant que le conteneur n'est pas vide
  while(!cs_est_vide(p->conteneur)) {
    // Choisir un sommet v dans le conteneur
    int v = cs_choisir(p->conteneur);

    // Si le sommet v n'a pas de distance et il est dans la racine relié à debut
    // sa distance avec début est la distance de son père avec debut + 1
    if(p->distances[v] == -5 && p->distances[r] != DIST_INF) {
      p->distances[v] = p->distances[p->peres[v]]+1;
    }
    // Si le sommet v appartient à la cfc non relier à debut donc on affecte
    // la valeur DIST_INF a sa distance avec debut
    else if (p->distances[r] == DIST_INF && p->distances[v] == -5) {
      p->distances[v] = DIST_INF;
    }

    msuc* suc = p->graphe_a_parcourir->tab_sucs[v];
    msuc * suiv;
    // Voir les successeurs non visité de v et choisir un si présent
    while (suc && pc_est_visite(p, msuc_sommet(suc))) {
      suiv = msuc_suivant(suc);
      suc = suiv;
    }
    // Si v a des successeurs non visité, alors
    if(suc != NULL && !pc_est_visite(p, msuc_sommet(suc))) {
      // Choisir un tel succeseur
      int w = msuc_sommet(suc);

      // Création de l'arboressance
      // Si le graphe etudié est non orienté
      if (!graphe_est_or(p->graphe_a_parcourir)) {
          graphe_ajouter_arete(p->arbo, v, w, msuc_valeur(suc));
      }
      // Sinon
      else {
        graphe_ajouter_arc(p->arbo, v, w, msuc_valeur(suc));
      }

      // Ajouter la racine courante pour le sommet visité.
      file_enfiler(p->racine_courante, r);
      // Marquer w comme visité
      pc_marquer_comme_visite(p, w);
      // On récupère le père de w qui est v
      p->peres[w] = v;
      // Si le sommet w n'a pas de distance et il est dans la racine relié a debut
      // sa distance avec début est la distance de son père avec debut + 1
      if(p->distances[w] == -5 && p->distances[r] != DIST_INF) {
        p->distances[w] = p->distances[p->peres[w]]+1;
      }
      // Si le sommet w appartient à la cfc non relier à debut donc on affecte
      // la valeur DIST_INF a sa distance avec debut
      else if (p->distances[r] == DIST_INF && p->distances[w] == -5) {
        p->distances[w] = DIST_INF;
      }
      // Ajouter w au conteneur
      pc_ajouter_dans_conteneur(p, w);
    }
    // Sinon
    else {
      // Marquer v comme exploré
      pc_marquer_comme_explore(p, v);
      // enlever v du conteneur
      pc_supprimer_du_conteneur(p);
    }
    // FinSI
  }
  // FinTantQue
}

void pc_parcourir2(parcours *p, int debut)
{
  // Initialisation:
  // Le conteneur de sommet est vide.
  while(!cs_est_vide(p->conteneur)) {
    cs_supprimer(p->conteneur);
  }
  // Aucun sommet n'est visité.
  while(!file_est_vide(p->prefixe)) {
    file_defiler(p->prefixe);
  }
  // Aucun sommet n'est exploré.
  while(!file_est_vide(p->suffixe)) {
    file_defiler(p->suffixe);
  }

  // On commence le parcours par debut.
  int r = debut;
  int cpt = 0;
  // Tant que tous les sommets ne sont pas explorés,
  while (!pc_est_fini(p)) {
    // Choisir une racine r parmi les sommet non visités après un tour de boucle.
    // car le premier tour r est égale à debut.
    if(cpt != 0)
      r = pc_choisir_racine(p);

    pc_parcourir_depuis_sommet2(p, r, debut);

    cpt++;
  }
  // FinTantQue
}

void afficher_tab (int * tab, int taille) {
  for (int i = 0; i < taille; ++i)
    printf("%d ", tab[i]);
  puts("");
}
