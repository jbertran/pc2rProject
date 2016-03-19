# Projet PC2R 2016

Clément Bertrand, Jordi Bertran de Balanda

## Dépendances

* Serveur: ocamlc
* Client: g++, Qt.

## Serveur - OCAML

### GameState.ml

#### Description

Représentation de l'état du jeu. Fournit une boîte noire pour interrroger l'état du jeu et faire quelques opérations dessus.

#### Format de fichier de configuration

Le fichier de configuration est du type:

```
16 16 # Nombre de lignes, nombre de colonnes
2 2 H # Position et direction d'un mur
2 2 G
2 6 B
-1 -1 # Fin de fichier
```

#### Utilisation

__Nécessaire__ avant d'utiliser GameState pour une partie:

```ocaml
init_state filepath
```

## Client - C++

Compilation:

```sh
make
```

### Classes

* __Client__ : gestion de la connexion au serveur - handshake de début, envoi/réception, terminaison.
* __Repr__: gestion de la représentation du plateau
* __Session__: gestion du jeu une fois le client connecté, avec les différentes phases et les écoutes des messages qui concernent le client dans chaque phase. Réaction aux commandes dans commands.cpp, boucle de jeu dans session.cpp.
	* Possède un client, une repr

### Structures

* __Coldir__: bête association couleur/direction
* __Coords__: points 2D.

### Énumérations

* __Incoming__: la liste des commandes que le client peut recevoir du serveur. Toutes traitées dans session.
* __Status__: OK ou KO, pour ne pas avoir à utiliser des booléens ou des ints.
* __Phase__: les 4 phases possibles dans la boucle de jeu du client.

### Outils

* Helpers pour la conversion string -> enum pour couleur et direction
* Helpers pour le parsing des messages serveur - fonction split selon un caractère, fonction de récupération des arguments et de la commande étant donné le message entier reçu par le client en string

## TODO

* Better hostname support in client.cpp
* Meilleur format de fichier d'entrée pour le serveur
* GUI
* Test everything
