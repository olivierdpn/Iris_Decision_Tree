//
//  vector.c
//  TD4
//
//  Created by Olivier Dupain on 24/11/2017.
//  Copyright © 2017 Olivier Dupain. All rights reserved.
//

#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

vector * create_vector()
{
    vector * vect = (vector*)malloc(sizeof(vector));
    vect->contenu=NULL;
    vect->taillelogique=0;
    vect->taillephysique=0;
    
    return vect;
}

bool is_null_or_empty(vector const * p_vec)
{
    bool vide = false;
    if (p_vec==NULL)
    {
        vide=true;
    }
    return vide;
}

bool add(double element, vector * p_vec)
{
    bool rajoutOK = false;
    
    if (p_vec->taillephysique==p_vec->taillelogique)
    {
        p_vec->taillelogique=p_vec->taillelogique+1;
        p_vec->taillephysique=p_vec->taillephysique+1;
        
        double * nouveauCont = (double*)malloc(sizeof(double)*(p_vec->taillephysique+1));
        for (int i =0; i<p_vec->taillephysique-1;i++)
        {
            nouveauCont[i] = p_vec->contenu[i];
        }
        nouveauCont[p_vec->taillephysique-1]=element;
        p_vec->contenu=nouveauCont;
        
        rajoutOK=true;
    }
    else
    {
        p_vec->taillelogique++;
        p_vec->contenu[p_vec->taillelogique-1]=element;
        
        rajoutOK=true;
    }
    return rajoutOK;
}

unsigned int size(vector const * p_vec)
{
    return p_vec->taillelogique;
}

double* element_at(unsigned int index, vector const * p_vec)
{
    if (index<p_vec->taillelogique)
    {
        return p_vec->contenu+index;
    }
    else
    {
        return NULL;
    }
}

bool remove_at(unsigned int index, vector * p_vec)
{
    bool retirOK = false;
    
    if (index<p_vec->taillelogique)
    {
        p_vec->taillelogique--;
        for (int i=index;i<p_vec->taillelogique;i++)
        {
            p_vec->contenu[i]=p_vec->contenu[i+1];
        }
        retirOK=true;
    }
    return retirOK;
}

void delete_vector(vector * p_vec) //demander si on peut le faire directement ici ou obligé de passer par le code appellant ? 
{
    free(p_vec->contenu);
    p_vec->contenu=NULL;
    free(p_vec);
    p_vec=NULL;
}


