# Projet PC2R 2016

Clément Bertrand, Jordi Bertran de Balanda

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

### TODO: 

* Fix la visibilité de GameState.dir etc

## Client - CPP

Trop cool.
