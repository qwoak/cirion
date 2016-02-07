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
 * @file    introbubble.cpp
 * @version 0.3.4
 * @author  Jérémy S. "Qwoak"
 * @date    05 Février 2016
 * @brief   Bulle utilisée dans l'introduction.
 */

#include <cstdlib> // srand(), rand()
#include <ctime> // time()
#include <iostream>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/introbubble.hpp>
#include <Cirion/log.hpp>
#include <Cirion/point3.hpp>

//! @brief Constructeur pour la classe Bubble.
cirion::IntroBubble::IntroBubble(): mBubblePosition( Point3f(0, 0, 0) )
{
}

//! @brief Déstructeur pour la classe Bubble.
cirion::IntroBubble::~IntroBubble()
{
}

//! @brief Procédure de création de la bulle.
//! @throw CiException en cas d'échec.
void cirion::IntroBubble::create()
{
    try
    {
        setTexture( (char*)"TexBubble" );
    }

    catch( CiException const& e )
    {
        log( e );
        throw CiException( (const char*)"Unable to process bubble creation.",
            __PRETTY_FUNCTION__ );
    }

    mSrc.w = 16;
    mSrc.h = 16;
    mDest.w = mSrc.w;
    mDest.h = mSrc.h;

    // Première génération.
    regen( true );
}

//! @brief Procédure de traîtement de l'évenement.
//! @param event Pointeur vers une structure d'évenements SDL2.
void cirion::IntroBubble::handleEvent( SDL_Event* event )
{
    //!< Il n'y a pas d'évenements à traiter pour l'objet IntroBubble
}

//! @brief Procédure de mise à jour de la bulle.
//! @param dt
//! @param data
void cirion::IntroBubble::update( int dt, void* data )
{
    // Mise à jour de la profondeur de la bulle.
    mBubblePosition.mZ -= 0.075 * (float)dt / 20;
    // Mise à jour de la transparence de la texture.
    //mAlpha = -mBubblePosition.mZ / 8 * 255;

    if( mBubblePosition.mZ <= 0 )
    {
        // Régénération.
        regen();
    }

    // Mise à jour du repère source de l'objet.
    mSrc.x = (int)(mBubblePosition.mZ) * 16;
    // Mise à jour de la position de l'objet.
    mPosition.mX = gRendererWidth / 2 
                 + mBubblePosition.mX / mBubblePosition.mZ
                 - 8;

    mPosition.mY = gRendererHeight / 2
                 + mBubblePosition.mY / mBubblePosition.mZ
                 - 8;
}

/* +------------------------------------------------------------------------+
   ! Définition des méthodes privées                                        !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de régénération de la bulle.
//! @param randomDepth Indique le calcul d'une nouvelle profondeur aléatoire.
void cirion::IntroBubble::regen( bool randomDepth )
{
    if( randomDepth )
    {
        // Nouvelle profondeur aléatoire ( 8.0 <= mBubbleZ < 16.0 ).
        mBubblePosition.mZ = (float)( rand() % 80 ) / 10 + 8;
    }

    else
    {
        // Reset à la profondeur maximale du champ.
        mBubblePosition.mZ = 8;
    }
    
    // Nouvelle abscisse et ordonnée.
    mBubblePosition.mX = rand() % ( 8 * gRendererWidth  ) - ( 8 * 160 );
    mBubblePosition.mY = rand() % ( 8 * gRendererHeight ) - ( 8 * 120 );
}
