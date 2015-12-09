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
 * @version 0.3
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    25 Novembre 2015
 * @brief   Bulle utilisée dans l'introduction.
 */

#include <iostream>
#include <cstdlib> // srand(), rand()
#include <ctime> // time()
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp> // RENDERER_W, RENDERER_H
#include <Cirion/introbubble.hpp>
#include <Cirion/log.hpp>

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Bubble.
cirion::IntroBubble::IntroBubble():
    mBubbleX( 0 ),
    mBubbleY( 0 ),
    mBubbleZ( 0 )
{
}

//! @brief Déstructeur pour la classe Bubble.
cirion::IntroBubble::~IntroBubble()
{
}

/* +------------------------------------------------------------------------+
   ! Définition des méthodes publiques                                      !
   +------------------------------------------------------------------------+ */

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

    // Première génération.
    regen( true );

    // Calcul et définition de la position de l'objet.
    setPosition( RENDERER_W / 2 + mBubbleX / mBubbleZ, 
                 RENDERER_H / 2 + mBubbleY / mBubbleZ );
}

//! @brief Procédure de traîtement de l'évenement.
void cirion::IntroBubble::handleEvent()
{
	//!< Il n'y a pas d'évenements à traiter pour l'objet IntroBubble
}

//! @brief Procédure de mise à jour de la bulle.
//! @param timeStep Temps écoulé depuis la dernière image.
void cirion::IntroBubble::update( int timeStep )
{
    // Mise à jour de la profondeur de la bulle.
    mBubbleZ -= 0.075 * (float)timeStep / 20;
    // Mise à jour de la transparence de la texture.
    mAlpha    = -mBubbleZ / 8 * 255;

    if( mBubbleZ <= 0 )
    {
        // Régénération.
        regen();
    }

    if( mBubbleZ <= 8 )
    {
        // Mise à jour du repère source de l'objet.
        setSrc( (int)(mBubbleZ) * 16, 0, 16, 16 );
        // Mise à jour de la position de l'objet.
        setPosition( RENDERER_W / 2 + mBubbleX / mBubbleZ, 
                     RENDERER_H / 2 + mBubbleY / mBubbleZ );            
    }
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
        mBubbleZ = (float)(rand() % 80 ) / 10 + 8;
    }

    else
    {
        // Reset à la profondeur maximale du champ.
        mBubbleZ = 8;
    }
    
    // Nouvelle abscisse et ordonnée.
    mBubbleX = rand() % (8 * RENDERER_W) - (8 * 160);
    mBubbleY = rand() % (8 * RENDERER_H) - (8 * 120);
}
