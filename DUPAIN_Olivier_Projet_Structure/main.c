#include <stdio.h>
#include "vector.h"
#include "donnees.h"
#include <stdlib.h>

void afficher_matrice(matrice_donnees * matrice1)
{
    for(int i =0; i< matrice1->nb_lignes;i++)
    {
        for(int j=0;j<matrice1->nb_colonnes;j++)
        {
            printf(" %lg ",matrice1->matrice[i][j]);
        }
        printf("\n");
    }
}
// Affiche d'un certain nombre d'espaces, proportionnel à offset
void afficher_offset(int offset)
{
    for(int i = 0 ; i < offset ; i++)
    {
        printf("      ");
    }
}

// Affichage récursif <=> parcours préfixé
// Initialisation : offset = 0
void affichage_arborescence(noeud * arbre, int offset)
{
    if(arbre != NULL)
    {
        // Etape 1 - afficher la valeur
        printf("\n");
        if (offset == 0)
        {
            printf("Racine de l'arbre : \n");
        }
        afficher_offset(offset);
        afficher_offset(offset);
        if(est_feuille(arbre)==true)
        {
            printf("Feuille : \n");
            afficher_offset(offset);
            afficher_offset(offset);
        }

        if( offset != 0 ) // tous les éléments sauf la racine
        {
            printf("|-");
        }
        printf("Précision en Y : %lg \n", arbre->precision_y);
        afficher_offset(offset);
        afficher_offset(offset);
        if( offset != 0 ) // tous les éléments sauf la racine
        {
            printf("|-");
        }
        printf("Nombre d'individu : %d \n", size(arbre->index));
        afficher_offset(offset);
        afficher_offset(offset);
        if( offset != 0 ) // tous les éléments sauf la racine
        {
            printf("|-");
            if(arbre->diviseur->inf_sup==0)
            {
            printf("Chemin : X%d <= %lg",arbre->diviseur->X,arbre->diviseur->mediane);
            }
            if(arbre->diviseur->inf_sup==1)
            {
            printf("Chemin : X%d > %lg",arbre->diviseur->X,arbre->diviseur->mediane);
            }
            printf("\n");
        }
        // Etape 2 - appel récursif avec sous-arbre gauche
       
        affichage_arborescence(arbre->fils_gauche, offset+1);
        // Etape 2 - appel récursif avec sous-arbre de droite
        
        affichage_arborescence(arbre->fils_droit, offset+1);
    }
    //else <=> arrêt de la récursivité
}

void affiche_hauteur_arbre(noeud * racine)
{
    int hauteur = hauteur_de_arbre(racine);
    printf("\nLa hauteur de l'arbre est : %d.\n\n", hauteur);
}

void affiche_largeur_arbre(noeud * racine)
{
    int largeur = nombre_feuilles(racine);
    printf("\nLa largeur de l'arbre est : %d.\n\n",largeur);
}

void cherche_chemin(noeud * fils)
{
    //ON PART D'UNE FEUILLE TROUVER ET ON REMONTE A LA RACINE
    if(fils->parent!=NULL)
    {
    cherche_chemin(fils->parent); //placer ici pour avoir le chemin à l'endroit car l'algo remonte vers le parent et on veut le chemin descendant
        if((fils->parent)->parent != NULL)
        {
            printf("puis ");
        }
    if (fils->diviseur->inf_sup==0)
    {
        printf("X%d <= %lg ", fils->diviseur->X, fils->diviseur->mediane);
    }
    if (fils->diviseur->inf_sup==1)
    {
        printf("X%d > %lg ", fils->diviseur->X, fils->diviseur->mediane);
    }
    }
}

void cherche_feuille(noeud * racine)
{
    
    if(est_feuille(racine)==false)
    {
        cherche_feuille(racine->fils_gauche);
        cherche_feuille(racine->fils_droit);
    }
    else
    {
        printf("\nFEUILLE :\n");
        double precision = racine->precision_y;
        int nombre_ind = size(racine->index);
        printf("Précision en Y : %lg.\n", precision);
        printf("Nombre d'individu : %d.\n",nombre_ind);
        printf("Chemin : ");
        cherche_chemin(racine); // pour afficher le chemin depuis la racine 
        printf("\n");
        
    }
}

void affiche_feuille(noeud * racine)
{
    printf("\nLes informations contenues dans les %d feuilles sont :\n",nombre_feuilles(racine));
    cherche_feuille(racine);
}

void predire(noeud * racine)
{
    if (racine->y==1)
    {
        printf("\nL'estimation sera donnée pour une iris setosa.\n\n");
    }
    if (racine->y==2)
    {
        printf("\nL'estimation sera donnée pour une iris versicolor.\n\n");
    }
    if (racine->y==3)
    {
        printf("\nL'estimation sera donnée pour une iris virginica.\n\n");
    }
    double long_sepale=0;
    double larg_sepale=0;
    double long_petale=0;
    double larg_petale=0;
    
    printf("Veuillez entrer la longueur du sepale :\n");
    scanf("%lg",&long_sepale);
    printf("Veuillez entrer la largeur du sepale :\n");
    scanf("%lg",&larg_sepale);
    printf("Veuillez entrer la longueur du petale :\n");
    scanf("%lg",&long_petale);
    printf("Veuillez entrer la largeur du petale :\n");
    scanf("%lg",&larg_petale);
    double pre = 0 ;
    double precision = predire_recu(racine, long_sepale,larg_sepale,long_petale,larg_petale,pre);
    
    printf("\nD'après l'arbre de décision, la précision associée à ce nouvel individu est : %lg.\n\n",precision);
    
}

void menu (noeud * racine)
{
    int choix=0;
    while(choix!=6)
    {
        printf("---MENU---\n\n1- Afficher hauteur de l'arbre\n2- Afficher largeur de l'arbre, nombre de feuilles\n3- Afficher l'arbre sous forme arborescente \n4- Afficher les feuilles\n5- Prédire\n6 - Quitter\n\nChoisissez une action : ");
        
        scanf("%d",&choix);
        printf("\n");
        switch(choix)
        {
            case 1 :
            {
                affiche_hauteur_arbre(racine);
                break;
            }
            case 2 :
            {
                affiche_largeur_arbre(racine);
                break;
            }
            case 3 :
            {
                printf("---- AFFICHAGE ARBORESCENCE ----\n");
                affichage_arborescence(racine, 0);
                printf("\n");
                break;
            }
            case 4 :
            {
                affiche_feuille(racine);
                printf("\n");
                break;
            }
            case 5 :
            {
                predire(racine);
                break;
            }
            case 6 :
            {
                liberer_donnees(racine->matrice);
                printf("Vous avez quitté l'arbre de prédiction!\n\n");
                break;
            }
            default:
                printf("L'entrée choisie n'est pas correct ! Vous devez entrer un nombre entre 1 et 10 !\n\n");
                break;
        }
    }
}

void initialisation_pre_menu()
{
    
    printf(" ---- Bienvenue dans l'arbre de décision : ----\n\n");
    printf("Veuillez entrer la valeur Y à prédire : \n1 - iris setosa\n2 - iris versicolor\n3 - iris virginica\n");
    int Y = 0;
    scanf("%d",&Y);
    printf("Veuillez saisir le seuil minimal en pourcentage : \n");
    double min = 0;
    scanf("%lg",&min);
    printf("Veuillez saisir le seuil maximal en pourcentage : \n");
    double max = 0;
    scanf("%lg",&max);
    max = max/100;
    min=min/100;
    printf("Veuillez saisir le nombre d'individu minimum en pourcentage du nombre d'individu de départ : \n");
    double nbr_ind_min = 0;
    scanf("%lg",&nbr_ind_min);
    printf("Veuillez saisir la hauteur maximale de l'arbre : \n");
    int hauteur_max = 0;
    scanf("%d",&hauteur_max);
    noeud * racine = racine_arbre(Y);
    nbr_ind_min=(nbr_ind_min/100);
    
    creation_suite_arbre(racine,nbr_ind_min, min, max,racine, hauteur_max);
    
    printf("\nVotre arbre a été initialisé.\n");
    printf("\n\n");
    menu(racine);
}



int main(int argc, const char * argv[]) {
    
    initialisation_pre_menu();
    
    return 0;
}
