/*
 * This file is part of Cirion.
 *
 * Cirion, 
 a side-scrolling game engine built over SDL2 and TinyXML2.
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
 * @file    world.cpp
 * @version 0.2.1.2
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Novembre 2015
 * @brief   Le monde.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp> //!< RENDERER_WIDTH et RENDERER_HEIGHT
#include <Cirion/log.hpp>
#include <Cirion/surface.hpp>
#include <Cirion/world.hpp> //!< TILE_WIDTH et TILE_HEIGHT

using namespace std;
using namespace cirion;

extern SDL_Renderer* gRenderer;    //!< cf. cirion.cpp
 
/* +------------------------------------------------------------------------+
   ! Définitions des constructeurs / déstructeurs.                          !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe World.
cirion::World::World()
{
    mBackgroundSrc.x  = 0; mBackgroundSrc.y  = 0;
    mBackgroundSrc.w  = 0; mBackgroundSrc.h  = 0;
    mBackgroundDest.x = 0; mBackgroundDest.y = 0;
    mBackgroundDest.w = 0; mBackgroundDest.h = 0;
    mTileSrc.x        = 0; mTileSrc.y        = 0;
    mTileSrc.w        = 0; mTileSrc.h        = 0;
    mTileDest.x       = 0; mTileDest.y       = 0;
    mTileDest.w       = 0; mTileDest.h       = 0;
    mWorldX           = 0; mWorldY           = 0;
}

//! @brief Déstructeur pour la classe World.
cirion::World::~World()
{
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de création du monde.
//! @param filepath Chemin vers un fichier CMF.
//! @throw CiException
void cirion::World::create( const char* name )
{
    try
    {
        /* Chargement du fichier CMF. */
        mMap.load( name );

        /* Création des ressources. */
        mTileset.create( mMap.getTilesetName() );
        mBackground.create( mMap.getBackgroundName() );
    }

    catch( CiException const& e )
    {
        log( e );

        throw CiException( "Unable to processing world creation.",
            __PRETTY_FUNCTION__ );
    }

    /* Init. des dimensions sources et d'affichage du background. */
    mBackgroundSrc.w  = mBackground.getWidth();
    mBackgroundSrc.h  = mBackground.getHeight();
    mBackgroundDest.w = mBackgroundSrc.w;
    mBackgroundDest.h = mBackgroundSrc.h;

    /* Init. des dimensions sources et d'affichage d'une tuile. */
    mTileSrc.w  = TILE_WIDTH;
    mTileSrc.h  = TILE_HEIGHT;
    mTileDest.w = mTileSrc.w;
    mTileDest.h = mTileSrc.h;
}

//! @brief Procédure de gestion d'un évenement pour le monde.
void cirion::World::handleEvent()
{
    /* Pacrours de la liste des objets */
    for( size_t i = 0; i != mObjects.size(); i++ )
    {
        /* Gestion de l'évenement pour l'objet. */
        mObjects[i]->handleEvent();
    }
}

//! @brief Procédure de mise à jour du monde.
void cirion::World::update()
{
    // --- Déplacement vertical. -----------------------------------------------

    /* Centrage si hauteur inférieure au renderer. */
    if( mMap.getHeight() * TILE_HEIGHT < RENDERER_HEIGHT )
    {
        mWorldY = (int)( mMap.getHeight() * TILE_HEIGHT - RENDERER_HEIGHT ) / 2;
    }

    // --- Déplacement horizontal. ---------------------------------------------

    /* Centrage si largeur inférieure au renderer. */
    if( mMap.getWidth()  * TILE_WIDTH  < RENDERER_WIDTH   )
    {
        mWorldX = (int)( mMap.getWidth()  * TILE_WIDTH  - RENDERER_WIDTH  ) / 2;
    }

    // --- Mise à jour des objets. ---------------------------------------------

    /* Pacrours de la liste des objets */
    for( size_t i = 0; i != mObjects.size(); i++ )
    {
        mObjects[i]->update();
    }
}

//! @brief Procédure de dessin du background.
void cirion::World::drawBackground()
{
    if( mBackground.getSdl2Texture() != NULL )
    {
        for( mBackgroundDest.y 
                = mWorldY > 0
                ? -mWorldY / 2 % mBackgroundDest.h
                : -mWorldY / 2 % mBackgroundDest.h - mBackgroundDest.h;
             mBackgroundDest.y  < RENDERER_HEIGHT;
             mBackgroundDest.y += mBackgroundDest.h )
        {
            for( mBackgroundDest.x
                    = mWorldX > 0
                    ? -mWorldX / 2 % mBackgroundDest.w
                    : -mWorldX / 2 % mBackgroundDest.w - mBackgroundDest.w;
                 mBackgroundDest.x  < RENDERER_WIDTH;
                 mBackgroundDest.x += mBackgroundDest.w )
            {
                /* Copie du background dans le renderer. */
                SDL_RenderCopy( gRenderer,
                                mBackground.getSdl2Texture(),
                                &mBackgroundSrc,
                                &mBackgroundDest );
            }
        }
    }
}

// @brief Procédure de dessin de la map.
void cirion::World::drawMap()
{
    unsigned char tile;       //!< Valeur de la tuile parcourue depuis le cmf.
    size_t        tileStartX; //!< Abscisse de la tuile de démarrage dans cmf.
    size_t        tileStartY; //!< Ordonnée de la tuile de démarrage dans cmf.
    size_t        tileEndX;   //!< Abscisse de la tuile de fin dans le cmf.
    size_t        tileEndY;   //!< Ordonnée de la tuile de fin dans le cmf.

    /* --- Calcul des tuiles de départ et de fin pour l'affichage de la map. -*/

    /* Si hauteur plus grande que le renderer, clip ... */
    if( mMap.getHeight() > RENDERER_HEIGHT / TILE_HEIGHT )
    {
        tileStartY = ( mWorldY ) / TILE_HEIGHT;
        tileEndY   = ( mWorldY + ( TILE_HEIGHT - 1 ) + RENDERER_HEIGHT ) 
                   / TILE_HEIGHT;
    }

    /* ... Sinon, affichage en entier sur la hauteur */
    else
    {
        tileStartY = 0;
        tileEndY   = mMap.getHeight();
    }

    /* Si largeur plus grande que le renderer, clip ... */
    if( mMap.getWidth() > RENDERER_WIDTH / TILE_WIDTH )
    {
        tileStartX = ( mWorldX ) / TILE_WIDTH;
        tileEndX   = ( mWorldX + ( TILE_WIDTH - 1 ) + RENDERER_WIDTH )
                   / TILE_WIDTH;
    }

    /* ... Sinon, affichage en entier sur la largeur */
    else
    {
        tileStartX = 0;
        tileEndX   = mMap.getWidth();
    }

    /* --- Dessin de la map. ------------------------------------------------ */
    if( mTileset.getSdl2Texture() != NULL )
    {
        for( size_t y  = tileStartY;
             y        != tileEndY;
             y        ++ )
        {
            for( size_t x  = tileStartX;
                 x        != tileEndX;
                 x        ++ )
            {
                /* Lecture de l'index. */
                tile = mMap.getTile( y, x );

                /* Calcul des coordonnées de la tuile dans le tileset. */
                mTileSrc.x = ( tile % 16 ) * TILE_WIDTH;
                mTileSrc.y = ( tile / 16 ) * TILE_HEIGHT;

                /* Positionnement de la tuile pour l'affichage. */
                mTileDest.x = ( x * TILE_WIDTH  ) - mWorldX;
                mTileDest.y = ( y * TILE_HEIGHT ) - mWorldY;

                /* Copie de la tuile dans le renderer. */
                SDL_RenderCopy( gRenderer,
                                mTileset.getSdl2Texture(),
                                &mTileSrc,
                                &mTileDest );
            }
        }
    }
}

// @brief Procédure de dessin des objets.
void cirion::World::drawObjects()
{
    /* Parcours de la liste des objets */
    for( size_t i = 0; i != mObjects.size(); i++ )
    {
        /* Dessin de l'objet */
        mObjects[i]->draw( mWorldX, mWorldY );
    }
}

//! @brief Procédure de dessin du monde.
void cirion::World::draw()
{
    drawBackground();
    drawMap();
    drawObjects();
}
