/*
 * This file is part of Cirion.
 *
 * Cirion, a side-scrolling game engine built over SDL2 and TinyXML2.
 * Copyright (C) 2015 S. Jérémy "Qwoak"
 *
 * Cirion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cirion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file    object.cpp
 * @version 0.4
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    10 Novembre 2015
 * @brief   Objet graphique.
 */

#include <cstring>
#include <sstream>
#include <vector>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp> //!< RENDERER_WIDTH et RENDERER_HEIGHT
#include <Cirion/log.hpp>
#include <Cirion/object.hpp>
#include <Cirion/texture.hpp>

using namespace std;
using namespace cirion;

extern SDL_Renderer*    gRenderer; //!< cf cirion.cpp
extern vector<Texture*> gTextures; //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Object.
cirion::Object::Object():
    mTexture(NULL)
{
    mSrc.x  = 0;
    mSrc.y  = 0;
    mSrc.w  = 0;
    mSrc.h  = 0;
    mDest.x = 0;
    mDest.y = 0;
    mDest.w = 0;
    mDest.h = 0;
}

//! @brief Déstructeur pour la classe Object.
cirion::Object::~Object()
{
}
 
/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de dessin de l'objet.
//! @param xOrigin
//! @param yOrigin
void cirion::Object::draw( int xOrigin, int yOrigin )
{
    //mDest.x = mX - xOrigin;
    //mDest.y = mY - yOrigin;

    if( mTexture != NULL )
    {
        /* L'objet est-il visible ? */
        //if(    mDest.x < RENDERER_WIDTH
        //    && mDest.y < RENDERER_HEIGHT )
        //{
        //    if(    mDest.x + mDest.w > 0
        //        && mDest.y + mDest.h > 0 )
        //    {
                /* Copie de la texture dans le renderer */
                SDL_RenderCopy( gRenderer,
                                mTexture->getSdl2Texture(),
                                &mSrc,
                                &mDest );
        //    }
        //}
    }
}

//! @brief Procédure de liage d'une texture à l'objet.
//! @param name Le nom de la texture.
//! @throw CiException
void cirion::Object::setTexture( const char* name )
{
    /** Drapeau d'existence de la texture demandée dans le vecteur des
    textures. */
    bool exists = false;

    /* Parcours du vecteur des textures. */
    for( size_t i = 0; i != gTextures.size(); i++ )
    {
        /* Si la texture demandée existe déjà dans le vecteur des textures: */
        if( strcmp( gTextures[i]->getName(), name) == 0 )
        {
            exists   = true;         // On note que la texture existe.
            mTexture = gTextures[i]; // Liage de la texture à l'objet.
            break;                   // On arrête la recherche.
        }
    }

    /* Si la texture n'existe pas dans le vecteur des textures: */
    if( !exists )
    {
        Texture* texture = new Texture();
        
        try
        {
            /* Creation de la texture demandée */
            texture->create( name );
        }

        catch( CiException const& e )
        {
            log( e );
            mTexture = NULL;
        }

        /* On met la texture crée dans le vecteur des textures et on la lie à
        l'objet. */
        gTextures.push_back( texture );
        mTexture = texture;
    }
}

//! @brief Procédure de définition du repère source (Clipping).
//! @param x Abcisse en pixels.
//! @param y Ordonnée en pixels.
//! @param w Largeur en pixels.
//! @param h Hauteur en pixels.
void cirion::Object::setSrc( int x, int y, int w, int h )
{
    mSrc.x = x;
    mSrc.y = y;
    mSrc.w = w;
    mSrc.h = h;
    mDest.w = w;
    mDest.h = h;
}

//! @brief Procédure de définition des coordonnées d'affichage.
//! @param x Abcisse en pixels.
//! @param y Ordonnée en pixels.
void cirion::Object::setPosition( int x, int y )
{
    mDest.x = x;
    mDest.y = y;
}

//! @brief Fonction accesseur.
//! @return Le repère source.
SDL_Rect cirion::Object::getSrc()
{
    return mSrc;
}

//! @brief Fonction accesseur.
//! @return Le repère de destination.
SDL_Rect cirion::Object::getDest()
{
    return mDest;
}
