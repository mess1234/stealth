# Mode d'emploi

Pour démarrer le jeu, il faut lancer la commande `make`, puis lancer l'executable `bin/stealth`.

Lorsque le jeu est lancé, vous pouvez commencer à jouer.

Votre but : récupérer les reliques et revenir au début sans se faire repérer.

Pour deplacer le personnage on propose les touches Z, Q, S, D ou bien les flèches directionnelles du clavier.

En ce qui concerne les compétences, `SHIFT` permet de déplacer le personnage plus vite et `ESPACE` permet de le rendre invisible.

A vous de jouer.


# Documentation technique

## Modules

| Nom             | Role
| --------------- | ----
| main            | Initialiser les différents objets, boucle principale du jeu
| backend         | Simplifier le code des autres modules
| collision       | Gérer les collision entre le joueur et les murs
| detect          | Vérifier si un guarde peut voir le joueur
| frontend        | Affichage graphique
| game_controller | Modifier l'état du jeu
| guard           | Définir les guardes
| player          | Définir le joueur
| room            | Génération du terrain
| score           | Enregistrer le score après une partie
| vector          | Gérer des vecteurs en 2D

## Structures de données

| Nom       | Définie dans  | Représente                    | Type
| --------- | ------------- | ----------------------------- | ----
| Room      | room          | la salle (terrain du jeu)     | struct
| Cell      | room          | une case de la salle          | enum
| Guard     | guard         | un garde                      | struct
| Player    | player        | le joueur                     | struct
| Direction | backend       | une direction de mouvement    | enum
| Vector    | vector        | un vecteur en 2D              | struct
| InputData | frontend      | une entrée de l'utilisateur   | struct
| Game_score | score        | une entrée dans le tableau des scores | struct

## Bugs

- Le mode panique n'est pas implémenté
- Après avoir gagné, on peut enregistrer plusieurs fois le même score 
