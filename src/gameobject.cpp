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
 * @file    gameobject.cpp
 * @version 0.4.1.2
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    04 Décembre 2015
 * @brief   Manipulation des objets.
 */

#include <cstring>
#include <sstream>
#include <vector>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp> //!< RENDERER_W et RENDERER_H
#include <Cirion/gameobject.hpp>
#include <Cirion/log.hpp>
#include <Cirion/texture.hpp>

using namespace std;
using namespace cirion;

extern SDL_Renderer*    gRenderer; //!< cf cirion.cpp
extern vector<Texture*> gTextures; //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe GameObject.
cirion::GameObject::GameObject():
    mX      (0),
    mY      (0),
    mAlpha  (255),
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

//! @brief Déstructeur pour la classe GameObject.
cirion::GameObject::~GameObject()
{
}

/* +------------------------------------------------------------------------+
   ! Définition des méthodes publiques                                      !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de dessin de l'objet.
//! @param xOrigin Abscisse de l'origine du repère.
//! @param yOrigin Ordonnée de l'origine du repère.
void cirion::GameObject::draw( int xOrigin, int yOrigin )
{
    // Calcul des coordonnées d'affichage.
    mDest.x = mX - xOrigin;
    mDest.y = mY - yOrigin;

    if( mTexture != NULL )
    {
        // L'objet est-il visible ?
        if(    mDest.x < RENDERER_W
            && mDest.y < RENDERER_H )
        {
            if(    mDest.x + mDest.w > 0
                && mDest.y + mDest.h > 0 )
            {
                // Modulation alpha.
                mTexture->setAlphaMod( mAlpha );

                // Copie de la texture dans le renderer.
                SDL_RenderCopy( gRenderer,
                                mTexture->getSdl2Texture(),
                                &mSrc,
                                &mDest );
            }
        }
    }
}

//! @brief Procédure d'association d'une texture à l'objet.
//! @param name Le nom de la texture.
//! @throw CiException en cas d'échec.
void cirion::GameObject::setTexture( const char* name )
{
    // Drapeau d'existence de la texture demandée dans le vecteur des textures.
    bool exists = false;

    // Parcours du vecteur des textures.
    for( size_t i = 0; i != gTextures.size(); i++ )
    {
        // Si la texture demandée existe déjà dans le vecteur des textures :
        if( strcmp( gTextures[i]->getName(), name) == 0 )
        {
            exists   = true;         // Report de l'existence de la texture.
            mTexture = gTextures[i]; // Association de la texture à l'objet.
            break;                   // Arrêt de la recherche.
        }
    }

    // Si la texture n'existe pas dans le vecteur des textures :
    if( !exists )
    {
        Texture* texture = new Texture();
        
        try
        {
            // Creation de la texture demandée.
            texture->create( name );
        }

        catch( CiException const& e )
        {
            log( e );
            mTexture = NULL;

            throw CiException( 
                (const char*)"Unable to set the requested texture.", 
                __PRETTY_FUNCTION__ );
        }

        /* On met la texture crée dans le vecteur des textures et on la lie à
        l'objet. */
        gTextures.push_back( texture );
        mTexture = texture;
    }
}

//! @brief Procédure de féfinition du repère source.
//! @param x Abcisse de l'origine en pixels.
//! @param y Ordonnée de l'origine en pixels.
//! @param w Largeur du repère en pixels.
//! @param h Hauteur du repère en pixels.
void cirion::GameObject::setSrc( int x, int y, int w, int h )
{
    mSrc.x  = x;
    mSrc.y  = y;
    mSrc.w  = w;
    mSrc.h  = h;
    mDest.w = w;
    mDest.h = h;
}

//! @brief Procédure de définition de la position de l'objet.
//! @param x Abcisse du repère en pixels.
//! @param y Ordonnée du repère en pixels.
void cirion::GameObject::setPosition( int x, int y )
{
    mX = x;
    mY = y;
}

//! @brief Fonction accesseur.
//! @return Le repère source.
SDL_Rect cirion::GameObject::getSrc()
{
    return mSrc;
}

//! @brief Fonction accesseur.
//! @return Le repère de destination.
SDL_Rect cirion::GameObject::getDest()
{
    return mDest;
}
