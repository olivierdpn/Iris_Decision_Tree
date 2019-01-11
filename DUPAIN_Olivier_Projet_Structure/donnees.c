#include "donnees.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//----------------------------------------------------------
// Traitement des données :
//----------------------------------------------------------

matrice_donnees* charger_donnnees(const char* nom_fichier)
{
    FILE* fichier = fopen(nom_fichier,"r");
    if( fichier != NULL )
    {
        unsigned int nb_lignes;
        unsigned int nb_colonnes;
        
        // Etape 1 - traitement première ligne
        fscanf(fichier, "%u %u", &nb_lignes, &nb_colonnes); // %u <=> unsigned int
        fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
        
        // Etape 2 - allocation des lignes de la matrice
        double** matrice = (double**) malloc( nb_lignes * sizeof(double*) );
        
        // Etape 3 - remplissage de la matrice
        for(int ligne = 0 ; ligne < nb_lignes ; ligne++)
        {
            // allocation des colonnes de la matrice (pour chaque ligne)
            matrice[ligne] = (double*) malloc( nb_colonnes * sizeof(double) );
            
            for(int colonne = 0 ; colonne < nb_colonnes ; colonne++)
            {
                if(colonne != nb_colonnes-1)
                {
                    fscanf(fichier, "%lg ", &matrice[ligne][colonne]);
                }
                else // dernière colonne (où le réel n'est pas suivi d'un espace)
                {
                    fscanf(fichier, "%lg" , &matrice[ligne][colonne]);
                }
            }
            
            fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
        }
        
        matrice_donnees * data = (matrice_donnees*) malloc(sizeof(matrice_donnees));
        data->nb_colonnes = nb_colonnes;
        data->nb_lignes = nb_lignes;
        data->matrice = matrice;
        
        fclose(fichier);
        return data;
    }
    
    printf("Fichier %s inconnu.\n", nom_fichier);
    return NULL;
}

matrice_donnees* liberer_donnees(matrice_donnees * data)
{
    if(data != NULL)
    {
        for(int ligne = 0 ; ligne < data->nb_lignes ; ligne++)
        {
            if(data->matrice[ligne] != NULL) // normalement toujours vrai
                free(data->matrice[ligne]);
        }
        free(data->matrice);
        free(data);
    }
    return NULL;
}

//----------------------------------------------------------
// Fonctionnalités
//----------------------------------------------------------

int hauteur_de_arbre(noeud const * parent)
{
    int hauteur_g =0;
    int hauteur_d = 0;
    int hauteur=0;
    if(parent != NULL)
    {
        hauteur_g  = 1+ hauteur_de_arbre(parent->fils_gauche);
        hauteur_d = 1 + hauteur_de_arbre(parent->fils_droit);
    }
    else return 0;
    
    if(hauteur_g>hauteur_d)  //récupère le max entre hauteur droite et hauteur gauche
    {
        hauteur = hauteur_g;
    }
    else
    {
        hauteur = hauteur_d;
    }
    return hauteur;
}

bool est_feuille(noeud const * element)
{
    bool test = false;
    if (element != NULL)
    {
        if(element->fils_gauche == NULL && element->fils_droit == NULL)
        {
            test = true;
        }
    }
    return test ;
}

int nombre_feuilles(noeud const * parent)
{
    if(parent == NULL ) return 0;
    
    else if(est_feuille(parent))
    {
        return 1;
    }
    return nombre_feuilles(parent->fils_droit) + nombre_feuilles(parent->fils_gauche);
}

double predire_recu(noeud * racine, double long_sepale, double larg_sepale, double long_petale, double larg_petale, double pre)
{
    if (!est_feuille(racine))
    {
        if ((racine->fils_gauche)->diviseur->X==1)                  //test pour connaitre quelle colonne doit être vérifiée
        {
            if (long_sepale<=(racine->fils_gauche)->diviseur->mediane) //test pour savoir si on va dans fils droit, fils gauche
            {
                pre = racine->fils_gauche->precision_y;
                return predire_recu(racine->fils_gauche, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
            else
            {
                pre = racine->fils_droit->precision_y;
                return predire_recu(racine->fils_droit, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
        }
        if ((racine->fils_gauche)->diviseur->X==2)
        {
            if (larg_sepale<=(racine->fils_gauche)->diviseur->mediane)
            {
                pre = racine->fils_gauche->precision_y;
                return predire_recu(racine->fils_gauche, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
            else
            {
                pre = racine->fils_droit->precision_y;
                return predire_recu(racine->fils_droit, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
            
        }
        if ((racine->fils_gauche)->diviseur->X==3)
        {
            
            if (long_petale<=(racine->fils_gauche)->diviseur->mediane)
            {
                pre = racine->fils_gauche->precision_y;
                return predire_recu(racine->fils_gauche, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
            else
            {
                pre = racine->fils_droit->precision_y;
                return predire_recu(racine->fils_droit, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
        }
        else
        {
            if (larg_petale<=(racine->fils_gauche)->diviseur->mediane)
            {
                pre = racine->fils_gauche->precision_y;
                return predire_recu(racine->fils_gauche, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
            else
            {
                pre = racine->fils_droit->precision_y;
                return predire_recu(racine->fils_droit, long_sepale, larg_sepale, long_petale, larg_petale,pre);
            }
        }
    }
    else return pre;
}


//----------------------------------------------------------
// Création de l'arbre :
//----------------------------------------------------------

noeud * racine_arbre(int Y)
{
    noeud * premier = (noeud*)malloc(sizeof(noeud));
    premier->diviseur=NULL;
    premier->fils_droit=NULL;
    premier->fils_gauche=NULL;
    matrice_donnees * matrice1 = charger_donnnees("iris.txt");
    premier->index=create_vector();
    for (int i=0; i<matrice1->nb_lignes;i++)
    {
        add(i,premier->index);
    }
    premier->matrice=matrice1;
    premier->parent=NULL;
    premier->y=Y;
    premier->precision_y=precision_Y(premier);
    return premier;
}

noeud * create_noeud_suivant(noeud *parent)
{
    noeud * suivant = (noeud*)malloc(sizeof(noeud));
    suivant->diviseur=NULL;
    suivant->fils_droit=NULL;
    suivant->fils_gauche=NULL;
    suivant->index=create_vector();
    suivant->matrice=parent->matrice;
    suivant->y=parent->y;
    
    return suivant;
}

vector * tableau_index(noeud * courant, int Xi)
{
    vector * new_tab = create_vector();
    
    for (int i=0;i<courant->matrice->nb_lignes;i++)
    {
        for(int j = 0;j<size(courant->index);j++)
        {
            if (i==courant->index->contenu[j])
            {
            add(courant->matrice->matrice[i][Xi],new_tab);
            }
        }
    }
    return new_tab;
}

void ordonner_tableau(double * tableau, int taille)
{
    for (int index_pas_trie=0; index_pas_trie<taille-1; index_pas_trie++)
    {
        // Recherche du maximum à droite de A[I]
        int pos_max = index_pas_trie;
        for (int index =index_pas_trie+1; index<taille; index++)
            if (tableau[index]<tableau[pos_max]) pos_max=index;
        // Echange de A[I] avec le maximum
        double permut =tableau[index_pas_trie];
        tableau[index_pas_trie]=tableau[pos_max];
        tableau[pos_max]=permut;
    }
}

double max_tableau(double * tableau, int taille)
{
    double max=0;
    for(int i=0;i<taille;i++)
    {
        if(tableau[i]>max)
        {
            max=tableau[i];
        }
    }
    return max;
}

int pos_max(double * tableau,int taille)
{
double max=0;
int pos=0;
    for(int i=0;i<taille;i++)
    {
        if(tableau[i]>max)
        {
            max=tableau[i];
            pos=i;
        }
    }
    return pos;
}

double mediane(noeud * courant,int Xi)
{
    double mediane = 0;
    vector * new_tab = tableau_index(courant,Xi);
    int taille = size(new_tab);
    
    double * tableau_mediane = (double*)malloc(sizeof(double)*taille);
    for(int i=0;i<taille;i++)
    {
        tableau_mediane[i]=new_tab->contenu[i];
    }
    
    //RECHERCHE DE LA MEDIANE

    ordonner_tableau(tableau_mediane, taille);

    if(taille%2==0)
    {
        mediane = (tableau_mediane[taille/2]+tableau_mediane[(taille/2)-1])/2;
    }
    else
    {
        mediane = tableau_mediane[(taille/2)];
    }
    
    //MEDIANE CORRIGEE
    
    double max_tab = max_tableau(tableau_mediane, taille);
    int position = pos_max(tableau_mediane, taille);
    if (max_tab==mediane)
    {
        mediane =tableau_mediane[position-1];
    }
    return mediane;
}

precision * deter_precision(noeud * courant)
{
    precision * preci_Xi = (precision*)malloc(sizeof(precision)*4);
    int i=0;
    // CREATION DU TABLEAU DE PRECISION AVEC LES VALEURS DE PRECISION INF ET SUP
    for(int Xi=1;Xi<courant->matrice->nb_colonnes;Xi++)
    {
    vector * new_tab = tableau_index(courant,Xi);

    double taille= size(new_tab);
    int taille1_imp =0;
    int taille2_imp =0;
    
    double med = mediane(courant,Xi);
    
    double compteur_inf = 0;
    double compteur_sup = 0;
    
    //CALCUL DE LA PRECSION
    for (int i=0;i<taille;i++)
    {
        int place_index = courant->index->contenu[i];
        if (new_tab->contenu[i]>med && courant->matrice->matrice[place_index][0]==courant->y)
        {
            compteur_sup++; // les compteurs : du bon coté de la médiane ET valeur Y recherchée !
        }
        if (new_tab->contenu[i]<=med && courant->matrice->matrice[place_index][0]==courant->y)
        {
            compteur_inf++;
        }
        if (new_tab->contenu[i]>med)
        {
            taille1_imp++; // les tailles : nombre d'élèments du bon côté de la médiane
        }
        if (new_tab->contenu[i]<=med)
        {
            taille2_imp++;
        }
    }
    // calcul des précisions et remplissage du tableau
    compteur_sup = compteur_sup/taille1_imp;
    compteur_inf = compteur_inf/taille2_imp;
    
    preci_Xi[i].inf=compteur_inf;
    preci_Xi[i].sup=compteur_sup;
    
    i++;
        
    }
    return preci_Xi;
}

critere_de_division * meilleur_diviseur(noeud * courant)
{
    critere_de_division * deter_critere = (critere_de_division*)malloc(sizeof(critere_de_division));
    precision * preci_Xi = deter_precision(courant);
    
    double preci_max = 0;
    int position_max = 0;
    // RECHERCHE du max dans le tableau de précision
    for (int i=0;i<courant->matrice->nb_colonnes-1;i++)
    {
        if (preci_Xi[i].inf>preci_max)
        {
            preci_max = preci_Xi[i].inf;
            position_max=i;
        }
        if (preci_Xi[i].sup>preci_max)
        {
            preci_max = preci_Xi[i].sup;
            position_max = i;
        }
    }
    // Actualisation du maximum de données possible dans le critère de précision
    deter_critere->X= position_max+1;
    deter_critere->mediane = mediane(courant,position_max+1);
    deter_critere->divPre = preci_Xi;

    return deter_critere;
}

double precision_Y(noeud * courant)
{
    double taille = size(courant->index);
    double precision =0;
    double compteur = 0;
    if (taille>0)
    {
    int valeur_dans_tab_index =0;
    for (int i = 0; i<taille;i++)
    {
        valeur_dans_tab_index=courant->index->contenu[i];
        if (courant->matrice->matrice[valeur_dans_tab_index][0]==courant->y) // présent dans la matrice ET bonne valeur de Y
        {
            compteur++;
        }
    }
    precision =compteur/taille;
    }
    return precision;
}

void divise(noeud * parent, critere_de_division * div)
{
    //création des fils droits et gauches :
    noeud * fils_droit = create_noeud_suivant(parent);
    noeud * fils_gauche = create_noeud_suivant(parent);
    //actualisation des données de fils droit et gauche
    
    //2ème critère de division car besoin de 2 pour que que le signe de inf_sup soit différent
    critere_de_division * div2 = (critere_de_division*)malloc(sizeof(critere_de_division));
    div2->mediane = div->mediane;
    div2->X = div->X;
    div2->divPre = div->divPre;
    div2->inf_sup =1;
    div->inf_sup = 0;
    
    for (int i=0;i<parent->matrice->nb_lignes;i++)
    {
        for(int j = 0;j<size(parent->index);j++)
        {
            if (i==parent->index->contenu[j]) // si dans le vecteur index
            {
                if (parent->matrice->matrice[i][div->X] <= div->mediane ) // test de placement du bon côté de la médiane
                {
                    add(i,fils_gauche->index);
                    fils_gauche->diviseur=div;
                    parent->fils_gauche=fils_gauche;
                    fils_gauche->parent=parent;
                    fils_gauche->precision_y=precision_Y(fils_gauche);
                }
                else
                {
                    add(i,fils_droit->index);
                    fils_droit->diviseur=div2;
                    parent->fils_droit=fils_droit;
                    fils_droit->parent=parent;
                    fils_droit->precision_y=precision_Y(fils_droit);
                }
            }
        }
    }
}

bool conditions_division(noeud * courant, double nombre_min_ind, double preci_min, double preci_max, noeud * racine, int hauteur_max)
{
    bool division = false;
    double nbr_min =nombre_min_ind*courant->matrice->nb_lignes;
    int hauteur_arbre_racine = hauteur_de_arbre(racine);
    
    if(hauteur_arbre_racine < hauteur_max && size(courant->index) >= nbr_min && courant->precision_y>preci_min && courant->precision_y<preci_max) // test si l'ensemble des condtions relatives au lancement de la division sont respectées
    {
        division = true;
    }
    
    return division;
}

void creation_suite_arbre(noeud * parent,double nombre_min_ind, double preci_min, double preci_max, noeud * racine, int hauteur_max)
{
    bool division=conditions_division(parent, nombre_min_ind, preci_min, preci_max, racine, hauteur_max); // si conditions OK
    if (parent!= NULL)
    {
    if (division)
    {
        critere_de_division * new_div = meilleur_diviseur(parent); //creation critère
        divise(parent, new_div); //division
        //RECURSIVITE
        creation_suite_arbre(parent->fils_droit,  nombre_min_ind, preci_min, preci_max, racine, hauteur_max);
        creation_suite_arbre(parent->fils_gauche, nombre_min_ind, preci_min, preci_max, racine, hauteur_max);
    }
    }
}


