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
 * @file    bubble.cpp
 * @version 0.2
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Octobre 2015
 * @brief   Bulle utilisée dans l'introduction.
 */

#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime>   /* time */
#include <Cirion/bubble.hpp>

using namespace std;
using namespace cirion;

extern int gTimeStep; //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définitions des constructeurs / déstructeurs.                          !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Bubble.
cirion::Bubble::Bubble():
    mZ( 0 )
{
}

//! @brief Déstructeur pour la classe Bubble.
cirion::Bubble::~Bubble()
{
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief
void cirion::Bubble::create()
{
    mZ = (float)(rand() % 80 ) / 10 + 8 ;

    mX = rand() % (8 * 320) - (8 * 160);
    mY = rand() % (8 * 240) - (8 * 120);

    setTexture( (char*)"Bubbles" );
    setSrc( 0, 0, 16, 16 );
    setPosition( 160 + mX/mZ, 120 + mY/mZ );
}

//! @brief
void cirion::Bubble::update()
{
    mZ -= 0.075 * (float)gTimeStep / 20;

    if( mZ <= 0 )
    {
        mZ = 8;
        mX = rand() % (int)(mZ * 320) - (int)(mZ * 160);
        mY = rand() % (int)(mZ * 240) - (int)(mZ * 120);
    }

    if( mZ > 8 )
    {
        setSrc( 0, 0, 0, 0 );
        setPosition( 0, 0 );
    }

    else
    {
        setSrc( (int)(mZ) * 16, 0, 16, 16 );
        setPosition( 160 + mX/mZ, 120 + mY/mZ );            
    }
}

//! @brief
void cirion::Bubble::handleEvent()
{
}
