# Objectives

===========================================

## Table of Contents

-----------------

* [1\. Objectif](#1-objectif)
  * [1.1. Présentation](#11-présentation)
  * [1.2. Interface](#12-interface)
* [2\. Niveau de rendu attendu](#2-niveau-de-rendu-attendu)
  * [2.1. Niveau 1 : Base (8 pts)](#2-niveau-de-rendu-attendu)
    * [2.1.1. Saisie et Affichage](#21-niveau-1--base-8-pts)
    * [2.1.2. Prise, Pions, Obstacles](#212-prise-pions-obstacles)
  * [2.2. Niveau 2 : Détection de l'échec (+3pts)](#22-niveau-2--détection-de-léchec-3pts)
  * [2.3. Niveau 3 : roques, prise en passant, promotion (+3pts)](#23-niveau-3--roques-prise-en-passant-promotion-3pts)
  * [2.4. Niveau 4 : Mat et Pat (+4pts)](#24-niveau-4--mat-et-pat-4pts)
* [3\. Contraintes](#3-contraintes)
  * [3.1. Position finale](#31-position-finale)
  * [3.2. Résultat de la partie](#32-résultat-de-la-partie)
  * [3.3. Lecture sur entrée standard](#33-lecture-sur-entrée-standard)
  * [3.4. Tests](#34-tests)
* [4\. Modélisation](#4-modélisation)
  * [4.1. La classe Square](#41-la-classe-square)
  * [4.2. La classe Piece et ses sous-classes](#42-la-classe-piece-et-ses-sous-classes)
  * [4.3. La classe Echiquier](#43-la-classe-echiquier)
  * [4.4. La classe Jeu](#44-la-classe-jeu)

## 1 Objectif

-----------------

Proposer une interface simple, en mode texte, permettant de représenter des mouvements de pièces d'échecs.

Cet exercice a pour objet de démontrer les notions suivantes:

* héritage
* polymorphisme
* méthodes virtuelles

### 1.1 Présentation

On souhaite pouvoir accomplir les actions telles que présentées dans le programme principal suivant. Ce programme propose comme seule interface à l'utilisateur la saisie d'un mouvement en notation algébrique, comme par exemple _b1c3_ qui désigne le mouvement de la pièce initialement située sur la case _b1_ (c-a-d en colonne _b_, rangée _1_) vers la case _c3_.

```cpp
# include "jeu.h"

# include <iostream>

using namespace std;

//\--------------------------------------------------------------
int main() {
    Jeu monjeu;  // initialise le jeu
    string mouvement;
    bool stop(false);
    monjeu.affiche();
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> mouvement;
        if (mouvement != "/quit") {
            // découper case origine et destination
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            monjeu.deplace("Partie 1", orig, dest);
            monjeu.affiche();
        }
        else stop=true;
    } while (!stop);
}
```

### 1.2 Interface

On peut imaginer une interface en mode texte comme la suivante. Cet affichage sera celui produit par l'affichage de l'échiquier.

```sh
    a     b     c     d     e     f     g     h    
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 | ♖  |  ♘  | ♗  |  ♕ | ♔  |  ♗  | ♘  | ♖  |
 +-----+-----+-----+-----+-----+-----+-----+-----+
Coup (eg. a1a8) ? b1c3

-> déplacement de ♘  b1c3

     a     b     c     d     e     f     g     h    
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     | ♘  |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 |     |     |     |     |     |     |     |     |
 +-----+-----+-----+-----+-----+-----+-----+-----+
 | ♖  |     | ♗  |  ♕ | ♔   |  ♗ |  ♘  | ♖  |
 +-----+-----+-----+-----+-----+-----+-----+-----+
Coup (eg. a1a8) ?
```

## 2 Niveau de rendu attendu

-----------------

Selon le temps consacré, vous pouvez raffiner les fonctionnalités de cette interface jusqu'à un niveau pleinement fonctionnel (ce qui n'est pas si simple). Voici différents niveaux de fonctionnalités que vous pouvez atteindre.

Un barême indicatif est donné pour chaque niveau: c'est le nombre de points **maximum** sous l'hypothèse que le code est de bonne qualité et implémente correctement les fonctionnalités du niveau. Après le niveau _Base_, chaque niveau de fonctionnalité est presque indépendant mais suivre cet ordre est conseillé.

### 2.1 Niveau 1 : Base (8 pts)

#### 2.1.1 Saisie et Affichage

* un affichage de l'échiquier et des pièces
* que l'utilisateur peut saisir un coup ordinaire (pas les roques)
* que le programme gère l'alternance des coups blanc/noir
* le programme se termine soit par `/quit`, `/resign`, soit `/draw`.
* le programme affiche sur **la dernière ligne** de la sortie standard, une chaine de caractère qui représente l'état de l'échiquier ainsi que le résultat (voir section [3](#3-contraintes)).

L'interface vérifie les contraintes suivantes pour un déplacement :

* vérifier que les coordonnées saisies sont dans l'échiquier,
* vérifier la légalité géométrique du mouvement de la pièce manipulée : en diagonale pour le fou, en ligne ou en colonne pour la tour, en ligne ou en colonne ou en diagonale pour la dame, et le pion avance de 1 ou 2 cases (contraintes supplémentaires dans un niveau ultérieur).
* vérifier que la case d'origine contient bien une pièce.

Quand l'une de ces contraintes n'est pas respectée, l'échiquier devra resté inchangé, un message d'erreur pertinent affiché, et la demande de coup réitérée.

#### 2.1.2 Prise, Pions, Obstacles

* Dans un déplacement, si la case de destination est occupée par une pièce de couleur opposée, c'est une prise, mais est un mouvement illégal si la case est occupée par une pièce de même couleur.
* Le mouvement des pions est conforme aux règles suivantes : il peut avancer de 2 cases à son premier coup, 1 case autrement, et prendre en diagonale vers l'avant.
* On vérifie la légalité des déplacements en vérifiant en plus qu'une pièce ne passe pas au-dessus d'une autre (concerne Tour, Dame, Fou).

### 2.2 Niveau 2 : Détection de l'échec (+3pts)

* Après un mouvement, on signale dans l'affichage qu'un roi est en échec le cas échéant. On vérifie aussi qu'un mouvement ne met pas le roi en échec.

### 2.3 Niveau 3 : roques, prise en passant, promotion (+3pts)

Ce niveau demande d'implémenter des mouvements particuliers de pièces :

* la prise en passant du pion.
* le mouvement du roque, petit roque noté O-O, et grand roque noté O-O-O. On pourra se contenter de vérifier uniquement que le roi et la tour impliquée n'ont jamais bougé, sans vérifier qu'une des cases du roque est sous la menace d'une pièce adverse.
* la promotion du pion arrivé sur la rangée 8 pour les blancs, 1 pour les noirs. On pose alors la question en mode texte, en quelle pièce doit être promu le pion. L'utilisateur tape un caractère parmi `{Q,R,B,N}` pour respectivement promouvoir en Reine, Tour, Fou, Cavalier.

### 2.4 Niveau 4 : Mat et Pat (+4pts)

* On détecte l'échec et mat et on arrête la partie.
* On détecte le pat et on arrête la partie. On vérifiera en priorité qu'aucune pièce du joueur à qui c'est le tour ne peut bouger légalement. Pour être complet, on peut implémenter la règle des 3 positions répétées successivement, et les 50 coups joués sans prise (ce dernier cas étant vraiment rare).

À ces 18 points seront ajoutés 2 points pour la documentation et les commentaires du code. Commenter les interfaces est indispensable pour documenter automatiquement les classes et les membres publics des classes. Commenter l'implémentation est également recommandé dès qu'une partie du code demande une réflexion pour en comprendre l'idée.

## 3 Contraintes

-----------------

* Votre programme doit lire les coups entrés sur l'entrée standard unix.
* Les coups seront notés en notation algébrique comme indiqué au début (par exemple `a2a4` pour faire avancer le pion blanc gauche de 2 cases). Voici un exemple d'extrait de code qui permet de vérifier la validité d'une entrée pour un mouvement standard et le petit roque.

```cpp
#include <regex>

bool saisie\_correcte(string const & cmd) {
regex mouvmtpattern("\[a-h\]\[1-8\]\[a-h\]\[1-8\]");
    return regex\_match(cmd,mouvmtpattern);

}

bool saisie\_correcte\_petitroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex\_match(cmd,mouvmtpattern);
}
```

* Dans un objectif de test, votre programme terminera en affichant sur `stdout` sur la **dernière** ligne une chaine de caractères composée de 2 informations:

    1. la position finale du jeu sous une forme canonique
    2. le résultat de la partie

    Ces 2 chaines sont séparées par un espace. Par exemple, la sortie sera:

    ```txt
    wR,wN,wB,wQ,,wR,wK,,wP,wP,wP,wP,,wP,wP,wP,,,,,,wN,,,,,wB,,wP,,,,,,bB,,bP,,,,,,,,,bN,,,bP,bP,bP,bP,,bP,bP,bP,bR,bN,bB,bQ,bK,,,bR, ?-?
    ```

* Vous devrez tester la validité de vos sorties en utilisant le script de test et les parties livrées pour tests (voir section _Tests_).

### 3.1 Position finale

La position finale du jeu sous une forme canonique est une chaine de caractères sans espace obtenue de le façon suivante : on affiche le contenu de chaque case en parcourant l'échiquer dans l'ordre (a1,b1, …, h1, a2, b2, …, h2, …, a8, …, h8). Le contenu dela case est codifié par les lettres suivantes :

* un caractère `w` ou `b` pour la couleur, respectivement blanche ou noire,
* un caractère pour la pièce: Q pour Reine (Queen), K pour Roi (King), B pour fou (Bishop), N pour cavalier (kNight), R pour Tour (Rook), et P pour pion (Pawn).
* on n'affiche rien si la case est vide, et chaque case est séparée par une virgule (aucun espace).

Voici un exemple de fonction qui peut implémenter cela utilise la classe `Square` conseillée mais peut être adapté facilement. Cette fonction appelle une fonction `pgn_piece_name()` chargée de rendre le symbole utilisé dans la notation PGN.

```cpp
string Echiquier::canonical\_position() const {
    string output;
    for (size\_t row(1); row<=8; row++){
        for (char col('a');col<='h';col++) {
            Square square(col+to\_string(row));
            if (!est\_case\_vide(square))
                // get pieces with theit PGN names,
                // true -> with P for pawns, true -> w/b for colors.
                output += pgn\_piece\_name(get\_piece(square)->to\_string(),true,true);
            output += ",";
        }
    }
    return output;
}
```

La fonction `pgn_piece_name()` est la suivante. Elle pourrait être simplifiée mais cette version admet des paramètres qui permettent plus de flexibilité : afficher les pions (oui ou non), faire précéder la pièce de sa couleur (oui ou non).

```cpp
string Echiquier::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {
    string psymb;
    if      (name=="\u2656") psymb="R";  // Rook W
    else if (name=="\u2658") psymb="N";  // Knight W
    else if (name=="\u2657") psymb="B";  // Bishop W
    else if (name=="\u2655") psymb="Q";  // Queen W
    else if (name=="\u2654") psymb="K";  // King W
    else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) { // one of the white piece has been found
        if (view\_color)
            return "w"+psymb;
        else
            return psymb;
    }
    if      (name=="\u265C") psymb= "R";  // Rook B
    else if (name=="\u265E") psymb= "N";  // Knight B
    else if (name=="\u265D") psymb= "B";  // Bishop B
    else if (name=="\u265B") psymb= "Q";  // Queen B
    else if (name=="\u265A") psymb= "K";  // King B
    else if (name.rfind("\u265F",0)==0 && view\_pawn) psymb= "P"; // Pawn B
    if (psymb.size()>0) { // one of the black piece has been found
        if (view\_color)
            return "b"+psymb;
        else
            return psymb;
    }
    else return "";
}
```

### 3.2 Résultat de la partie

* Le résultat de la partie est une chaine parmi : `1-0`, `0-1`, `1/2-1/2` et `?-?` pour signifier respectivement : victoire des blancs, victoire des noirs, nulle, partie interrompue.
* Une victoire des blancs se produit quand les blancs matent les noirs, ou les noirs saissent `/resign`. Une victoire des noirs se produit quand les noirs matent les blancs, ou les blancs saissent `/resign`. La nulle se produit quand il y a pat, ou qu'un des joueurs saisit `/draw`. La commande `/quit` provoque une partie interrompue.
* Pour la plupart des tests, un `/quit` apparait avant que la partie ne se termine par un résultat définitif, et donc `?,?` sera le résultat final le plus commun.

### 3.3 Lecture sur entrée standard

Le fait de lire sur l'entrée standard facilite les tests. Vous pouvez avoir un fichier contenant des coups, par exemple le fichier suivant `partie.txt`

```txt
e2e4
e7e5
g1f3
b8c6
d1d2
d2d3
g8f6
c1g5
f8e7
/quit
```

que vous pouvez jouer par la commande suivante, en supposant que votre exécutable s'appelle `echecs` :

```sh
cat partie.txt | ./echecs
```

Dans les parties, tests, des commentaires sont insérés sur certaines lignes, précédés par un `#` en début de ligne. Pour jouer une telle partie, il suffit de se débarasser des lignes de commentaires :

```sh
grep -v "^#" partie.txt | ./echecs
```

### 3.4 Tests

* Avant de rendre votre projet, vérifiez que vous passez les tests avec le script `test-level.sh` et les parties de références livrées. Les noms de fichier de parties commencent par un numéro qui correspond aux catégories de niveau.
* Le script teste 3 choses de la manière suivante : il extrait la dernière ligne de ce que votre programme sort sur la sortie standard, et isole

    1. la position finale sous forme canonique
    2. le résultat de la partie

    et compare ces chaines avec les résulats attendus (dits de référence) qui sont sur la dernière ligne des parties tests.

    1. il examine l'exit code de votre binaire. Si votre programme fait un segfault, le script devrait signaler que l'exit code n'est pas 0 (situation anormale).

* Les projets rendus seront testés de cette manière.

## 4 Modélisation

-----------------

Voici une description d'une conception possible. Toute autre conception peut être envisagée. Cependant, les explications suivantes sont inter-depéndantes, c-a-d qu'une classe proposée dépend souvent d'une autre, et attention à ne pas prendre une partie seulement des propositions sans comprendre comment elles s'articulent avec le reste.

### 4.1 La classe Square

* Pour manipuler les coordonnées, il peut être intéressant d'avoir une classe représentant une **case** de l'échiquier (la classe ne s'appelle pas **case** car c'est un mot clé de C/C++). Cette classe n'est pas essentielle mais simplifie le nombre de paramètres à chaque fois qu'on appelle des fonctions manipulant des coordonnées (ligne,colonne).
* Etant donné la notation algébrique proposée à l'utilisateur, cette classe peut permettre des conversions entre coordonnées en notation algébrique et indices de tableau. Par exemple un constructeur `Square("a1")` pourra avantageusement convertir la notation _a1_ en ligne=0 et colonne=0. On pourra aussi y ajouter des méthodes facilitant l'affichage, par exemple `to_string()` renvoyant "a1" pour une coordonnées (0,0).

### 4.2 La classe Piece et ses sous-classes

* Cette classe est abstraite. En effet, les seules entités réellement manipulées seront les Tour, Cavaliers, Roi, … . Toutes ses méthodes ne seront pas forcément abstraites. Par exemple, une méthode utile pourrait être `affiche()` affichant le nom de la pièce.
* Avec cette classe `Piece` viennent donc autant de sous-classes que de variantes de pièce, avec leur implémentation propre à leur comportement. Par exemple, on pourrait avoir une méthode: `est_mouvement_legal(case_origine,case_destination)` qui indiquera si ce mouvement de pièce est légal : en diagonale pour un fou, en ligne droite pour une tour, …
* Il est suggéré de mémoriser comme attribut de pièce, entre autres:
  * son nom (pour lequel on peut utiliser l'UTF-8 : le caractère \\u2656 affichera ♖), et éventuellement un identifiant unique.
  * sa couleur
  * sa position
* Des méthodes accesseurs viennent naturellement pour exploiter ses informations: `get_pos()` pour récupérer la position courante de la pièce, `get_couleur()`, `to_string()` pour afficher le nom de la pièce,…

### 4.3 La classe Echiquier

* Cette classe représente le stockage des pièces créées. On peut proposer un stockage dans un tableau 8x8 dont chaque case pointe vers une pièce allouée en mémoire.

    Piece \* echiquier\[8\]\[8\];
    // ou alternative probablement plus facile pour le passage de paramètres:
    Piece \*\*\* echiquier;

La mise en oeuvre de méthodes polymorphes sur les pièces de l'échiquier nécessite de stocker des pointeurs. On peut stocker dans ce tableau tout type de pièce héritant de `Piece`, comme par exemple l'adresse que renverrait un `new Tour(...)` (en supposant la classe `Tour` définie comme sous-classe de `Piece`). Quand une case est vide, on peut stocker le pointeur nul (`nullptr`).

* Un objet de la classe `Echiquier` devrait être le seul autorisé à faire les manipulations sur le tableau `echiquier` . Par exemple, le déplacement _a1b2_, impliquant les cases `echiquier[0][0]` (origine) et `echiquier[1][1]` (destination) donnera en fin de compte lieu à copier le pointeur se trouvant en `echiquier[0][0]`, en `echiquier[1][1]`, puis à mettre `nullptr` en `echiquier[0][0]` qui devient case libre après le déplacement. Pour cela, on pourra penser aux méthodes publiques:
  * `deplace( ...)`
  * `pose_piece(...)` permettant de placer les pièces au départ.
* Le **constructeur** devrait initialiser l'echiquier à la position de départ. Pour cela, on peut confier à ce constructeur les rôles de :
  * créer l'échiquier comme un tableau 8x8 capable de stocker des pointeurs vers des pièces
  * créer les instances des différentes pièces du jeu (qui ne seront de toute façon créés qu'une fois si on n'implémente la promotion du pion).

L'exemple ci-dessous montre ce que pourrait être l'initialisation.

En approche immédiate, on pourrait créer les pièces par allocation dynamique et stocker le pointeur retourné par cette création dans le tableau, c'est-à-dire par exemple:

```cpp
echiquier[0][0] = new Tour (Blanc, "\u2656 ", Square(0,0));
```

Cependant, l'exemple de constructeur ci-dessous ajoute une structure qui permet d'obtenir la liste des pièces d'un joueur. Cela vous sera problement utile pour tester l'échec par exemple, car on doit vérifier qu'aucune pièce d'une couleur ne pourrait prendre le roi adverse.

Donc dans l'exemple ci-dessous, on a comme attribut un tableau de deux vecteurs (un vecteur pour chaque couleur) `std::vector<Piece *> pieces[2]`, qui va recevoir le pointeur vers chaque pièce crée par allocation dynamique.

On fait ensuite l'affectation de chaque pointeur vers les pièces créées en parcourant ces vecteurs, en appelant une méthode `pose_piece()` qui va affecter ces pointeurs à la bonne case `echiquier[i][j]` à l'aide de la position intiale déclarée.

```cpp
typedef enum {Blanc=0, Noir=1} couleur_t;

// constructeur
Echiquier::Echiquier ()
{
    alloc_mem_echiquier();
    // allocation des pieces
    // Constructeur (Couleur, nom\_affiché, id, case)
    pieces[Blanc] = {
        new Tour    (Blanc,"\u2656",  0, Square(0,0)),
        new Cavalier(Blanc,"\u2658",  1, Square(0,1)),
        new Fou     (Blanc,"\u2657",  2, Square(0,2)),
        new Dame    (Blanc,"\u2655",  3, Square(0,3)),
        new Roi     (Blanc,"\u2654",  4, Square(0,4)),
        new Fou     (Blanc,"\u2657",  5, Square(0,5)),
        new Cavalier(Blanc,"\u2658",  6, Square(0,6)),
        new Tour    (Blanc,"\u2656",  7, Square(0,7))
    };
    pieces[Noir] = {
        new Tour    (Noir, "\u265C",  8, Square(7,0)),
        new Cavalier(Noir, "\u265E",  9, Square(7,1)),
        new Fou     (Noir, "\u265D", 10, Square(7,2)),
        new Dame    (Noir, "\u265B", 11, Square(7,3)),
        new Roi     (Noir, "\u265A", 12, Square(7,4)),
        new Fou     (Noir, "\u265D", 13, Square(7,5)),
        new Cavalier(Noir, "\u265E", 14, Square(7,6)),
        new Tour    (Noir, "\u265C", 15, Square(7,7))
    };
    // alloc pawns
    for (size_t i=0;i<8;i++) {
        pieces[Blanc].push_back(new Pion(Blanc, "\u2659" + string(1,i), 16+i, Square(1,i)));
        pieces[Noir].push_back(new Pion(Noir,   "\u265F" + string(1,i), 24+i, Square(6,i)));
    }
    // Pose des pieces en position initiale sur l'echiquier
    for (auto p : pieces\[Blanc\])
        pose_piece(p, p->get_pos());
    for (auto p : pieces\[Noir\])
        pose_piece(p, p->get_pos());
}
```

* Enfin, la classe doit permettre de visualiser l'échiquier (le plus important pour l'utilisateur). L'affichage montré en exemple est produit par l'extrait de code suivant:

```cpp
void Echiquier::affiche () const {
    string space5 = string(5,' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    "<< endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL-1);i>=0;i--) {
        cout << i+1 << " "; // numérotation ligne dans affichage
        for (int j(0);j<NBCOL;j++) {
            cout << "|" ;
            if (echiquier\[i\]\[j\]) { 
                cout << "\\u0020\\u0020";  //U+0020 est un esapce utf-8 taille police
                echiquier\[i\]\[j\]-> affiche();
                cout << "\\u0020" << " ";
            }
            else 
                cout << space5;  // 2 ascii spaces
        }
        cout << "|\\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}
```

### 4.4 La classe Jeu

On propose d'instancier un objet de classe `Jeu` pour interagir avec l'utilisateur.

* Cet objet possède un attribut **échiquier** (un objet de classe `Echiquier`).
* La classe `Jeu` propose essentiellement 2 méthodes publiques

  * la gestion d'un coup : saisie du coup, puis toute la "machinerie" que ça implique derrière.
  * afficher l'échiquier (pour que l'utilisateur se rende compte de la nouvelle position)

Ainsi, l'interaction avec un programme principal pourrait se résumer à :

```cpp
int main() {
    Jeu monjeu;

    // boucle de jeu, s'arrete a la fin de la partie
    bool stop(false);
    do {
        monjeu.affiche();
        stop = monjeu.coup();
    } while (!stop);
}
```

* La méthode la plus compliquée de cette classe Jeu sera la gestion du déplacement suite à la saisie d'un coup. Si on appelle cette méthode `deplace`, elle devra avoir comme paramètre la position d'origine de la pièce et sa position d'arrivée, et la couleur du joueur.

    La méthode `deplace` travaillera sur son attribut echiquier en passant cet echiquier aux méthodes publiques de la classe Echiquier pour qu'elles le modifient selon ses instructions.

Author: Stéphane Genaud

Created: 2023-03-09 Jeu 16:26

[Emacs](http://www.gnu.org/software/emacs/) 25.3.50.1 ([Org](http://orgmode.org/) mode 8.2.10)
