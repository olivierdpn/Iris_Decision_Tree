#ifndef DONNEES_H
#define DONNEES_H
#include "vector.h"

//----------------------------------------------------------
// Structures :
//----------------------------------------------------------

typedef struct
{
    unsigned int nb_colonnes;
    unsigned int nb_lignes;
    double** matrice;
} matrice_donnees;

typedef struct
{
    double inf;
    double sup;
}precision;

typedef struct
{
    int X;
    int inf_sup; // définit le caractère ">" ou "<="
    double mediane;
    precision * divPre; // tableau des précisions inferieures et supérieures
}critere_de_division;

typedef struct _noeud
{
    int y;
    matrice_donnees * matrice;
    vector * index;
    struct _noeud * fils_gauche;
    struct _noeud * fils_droit;
    struct _noeud * parent;
    critere_de_division * diviseur;
    double precision_y;
}noeud;


//----------------------------------------------------------
// Signatures traitement données :
//----------------------------------------------------------

matrice_donnees* charger_donnnees(const char* nom_fichier);
/* Permet de récupérer les données et les ajouter dans la matrice */
matrice_donnees* liberer_donnees(matrice_donnees * data);
/* Libère les données de la matrice */

//----------------------------------------------------------
// Signatures fonctionnalités 
//----------------------------------------------------------

int hauteur_de_arbre(noeud const * parent);
/* renvoi la hauteur d'un arbre, fonction récursive */
bool est_feuille(noeud const * element);
/* renvoi vrai si c'est une feuille, faux sinon, fonction récursive */
int nombre_feuilles(noeud const * parent);
/* renvoi le nombre de feuille d'un arbre, utilise bool est_feuille(), fonction récursive */
double predire_recu(noeud * racine, double long_sepale, double larg_sepale, double long_petale, double larg_petale, double pre);
/* Fonction récursive permettant de parcourir l'arbre de décision déjà crée, en fonction des valeurs entrées en paramètres, renvoi la prédiction du groupe feuille dans lequel l'algo termine */

//----------------------------------------------------------
// Signatures création automatique arbre 
//----------------------------------------------------------

noeud * racine_arbre(int Y);
/* Créer le premier noeud racine uniquement */
noeud * create_noeud_suivant(noeud *parent);
/* Permet d'initialiser l'ensemble des noeuds sauf le noeud racine */
vector * tableau_index(noeud * courant, int Xi);
/* Permet en fonction d'une colonne Xi, de récupérer les valeurs de la matrice de données et retourne un vecteur avec les valeurs de la matrice souhaitée */
void ordonner_tableau(double * tableau, int taille);
/* fonction qui permet de trier un tableau passé en paramètre par ordre croissant, ne renvoie rien*/
void afficher_tab(double tableau[],int taille);
/* créer le premier noeud racine uniquement */
double max_tableau(double * tableau, int taille);
/* Retourne la valeur max d'un tableau donné en paramètre */
int pos_max(double * tableau,int taille);
/* Retourne la position max d'un tableau passé en paramètre */
double mediane(noeud * courant,int Xi);
/* Renvoi la médiane CORRIGEE d'un tableau passé en paramètre */
precision * deter_precision(noeud * courant);
/* Renvoi un tableau de précision de dimension matrice.nbr_colonne-1, chaque "case" contient 2 "sous-cases" qui loge respectivement la valeur de la precision inf et sup associé à la colonne par ordre croissant */
critere_de_division * meilleur_diviseur(noeud * courant);
/* Définit dans un premier temps quelle colonne contient le maximum en parcourant de la colonne 1 à 4. (supérieur strict). Puis crée un critère de division qu'il renvoie en actualisant toutes les données possibles dedans : médiane, colonne Xi, tableau de précision. (il ne manque plus que le caractère ((inf ou égal) ou (sup strict) */
double precision_Y(noeud * courant);
/* Renvoi la valeur de la précision en Y pour lequel l'arbre a été crée pour la population présente dans le noeud. */
void divise(noeud * parent, critere_de_division * div);
/* Fonction qui permet de créer de noeud : un fils droit et un fils gauche, puis définit pour chaque noeud son nouveau vecteur contenant le numéro des index associé à ce noeud, puis actualise l'ensemble des informations possibles pour le noeud */
bool conditions_division(noeud * courant, double nombre_min_ind, double preci_min, double preci_max, noeud * racine, int hauteur_max);
/* Fonction qui renvoie vrai si les conditions de la division sont respectée, faux si la division ne peut pas s'effectuer */
void creation_suite_arbre(noeud * parent,double nombre_min_ind, double preci_min, double preci_max, noeud * racine, int hauteur_max);
/* Fonction qui permet la création de la suite de l'arbre, utilisant le calcul du meilleur critère de division puis la fonction divise en fonction du résultat du booléen de condition_division. Fonction récursive. */



#endif

