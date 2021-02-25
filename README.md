@author BENSEKHRI 	 Mohand Lounis 	11710457
@author OUMOHAND 	   Lounis			    11606663
@since 11/12/2019


--------------------------------------------------------------------------------
 -- Note importante: --
" Lors du téléchargement du projet si le dossier "dot" n'existe pas veuillez a le créer sous le dossier Machine_a_parcours :) "
--------------------------------------------------------------------------------



----------- Explication sur le contenu du dossier BENSEKHRI_OUMOHAND: ----------
Vous trouverez deux dossiers nommés dot et src ainsi que ce fichier texte
commentaires.txt

 * Le dossier dot: contient après l'exécution des tests de la machine toutes les représentations des
différents graphes au format .dot créées grâce aux fonctions graphe_ecrire_dot et graphiz.

Après compilation et exécution de tous les programmes le dossier "dot" doit
contenir 6 fichiers .dot .
  == Après exécution de ./test-parcours on aura:
-- graphe_depart.dot : qui est la représentation du graphe g.
-- parcours_prof.dot : qui est l'arboréscence d'un parcours en profondeur de g.
-- parcours_largeur.dot : qui est l'arboréscence d'un parcours en largeur de g.
-- parcours_larg_ou_prof.dot : qui est l'arboréscence d'un parcours en profondeur_ou_largeur de g.

  == Après l'exécution de ./test-ordre_top et ./test-cfc
aucun fichier .dot n'est crée.

  == Après l'exécution de ./test-distances on aura:
-- graphe_depart_distance.dot : qui est la représentation du graphe g.
-- graphe_BFS2.dot : qui est l'arboréscence d'un parcours en largeur de g.

  == Après l'exécution de ./test-diametre on aura pas plus de fichiers mais
seulement les deux fichiers graphe_depart_distance.dot et graphe_BFS2.dot seront
mis à jour par rapport au départ du parcours en largeur du graphe fait par le 
test diamètre.


  * Le dossier src: contient tous les fichiers .c et .h ainsi que le makefile et
les test-*.c. Après compilation on devrait avoir en plus de ces fichiers les
fichiers .o et les exécutables.

-- Nous avons procédé à quelques modifications sur les différents tests et cela
pour avoir une illustration des différents graphe et arboréscence pour savoir si
le résultat trouvé est bon ou non donc nous avons rajouté soit les affichages pour
séparer entre les différentes solutions de chaque sous-problème ou bien directement
un affichage des graphe créées et cela grâce à la fonction graphe_ecrire_dot et
graphiz qui créer des fichiers .dot qui sont des représentations des graphes au
format .dot ces fichiers sont créés dans le dossier dot comme déjà expliqué
précédemment (c'est pour cela que si le dossier dot n'existe pas après extraction
on doit le créer pour ne pas avoir de problème d'ouverture (fopen du dossier dot
pour la création des fichiers .dot)).

-- Nous avons rajouté un nouveau test pour le diamètre du graphe qui calcule
et affiche la distance entre chaque sommet du graphe vers tous les autres sommets
du graphe et cela pour les sommets. Ainsi le test-diametre est une version plus
longue du test-distance qui elle calcule seulement la distance entre un sommet
et tous les autres, et donc le test-diametre il permet au final de calculer le
diamètre du graphe. Nous avons modifié le makefile et cela pour qu'il crée un nouvel
exécutable pour tester le diamètre d'un graphe nommé : test-diametre.

-- Nous avons modifié les fichiers pile file et pile_ou_file juste en mettant
la structure dans les .h et non pas dans les .c (juste une préférence, nous
préférons avoir les prototypes et les structures ainsi que les différentes
définitions des variables utilisateurs dans le .h et les définitions des
fonctions dans les .c)
--------------------------------------------------------------------------------



--------------------------- Compilation & Exécution: ---------------------------
La commande de compilation est: make

Les commandes d'exécution des différents tests et leurs différentes sorties après compilation:
./test-parcours
qui exécute le fichier test-parcours et qui permet de créer un graphe orienté
stable, lui ajouter différents arcs et ensuite l'afficher (grâce à graphiz)
ensuite il déroule un DFS (parcours en profondeur), un BFS (parcours en largeur) 
et  un parcour en profondeur et en même temps en largeur (c'est au hasard a chaque 
choix de sommet) sur le graphe et affiche l'arboréscence créé, et l'ordre suffixe.

./test-ordre_top 
permet de savoir si un graphe contient un ordre topologique ou non 
si oui il l'affiche sinon donc le graphe contient un circuit donc, il affiche le
graphe à un circuit.

./test-cfc 
permet de calculer les composantes fortement connexes d'un graphe
et cela en appliquant l'algorithme de KOSARAJU SHARIR.

./test-distances 
permet de calculer les distances entre un sommet et tous les
autres sommets et cela grâce à un BFS sur le graphe en commençant par le sommet
désiré dans cet exemple on a choisi de calculer les distances à partir du
sommet 2. Il affiche le graphe de débat et l'arboréscence du BFS sur le graphe
ainsi que les différentes distances à partir du sommet vers tous les autres sommets.

./test-diametre 
permet de calculer le diamètre d'un graphe et affiche la même
chose que ./test-distance mais cette fois pour tous les sommets et à la fin il
affiche le diamètre du graphe.
--------------------------------------------------------------------------------



-------------------------- Test de fuite de mémoire: ---------------------------
Nous avons fait des tests de fuite de mémoires grâce à la commande
valgrind ./nom_executable sur tous les exécutables et on perd aucune mémoire.
--------------------------------------------------------------------------------



------------------------- Difficultés & points réussis -------------------------
Difficultés:
Nous avons eu des difficultés à implémenter la fonction parcours_depuis_sommet
qui nous a pris pas mal de temps, et dé que la fonction est bien implémentée
et tester, tous le reste été moins difficile.
Ensuite la seconde difficulté que nous avons rencontré est le respect des complexités.


Les points que nous pensons avoir réussis:
On pense avoir réussi tous le sujet, dans les faits de faire un bon DFS, BFS,
trouver l'ordre topologique, la recherche de cfc, le calcule des distance et du diamètre.
La seule complication et que nous pensons ne pas avoir réussi a respecter
les complexités dans quelques fonctions.
--------------------------------------------------------------------------------
