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
 * @file    demo.cpp
 * @version 0.3.1.2
 * @author  Jérémy S.
 * @date    02 Février 2016
 * @brief   Demo.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/graphic.hpp>
#include <Cirion/hiro.hpp>
#include <Cirion/introbubble.hpp>
#include <Cirion/log.hpp>
#include <Cirion/world.hpp>

using namespace std;
using namespace cirion;

int main( int argc, char* argv[] )
{
    // Définition du chemin des ressources.
    gWorkingDir = (char*)"./Data";

    try
    {
        // Initialisation
        init();

        // Création du monde
        gWorld.create( (const char*)"0" );

        // Géneration du champ de bulles
        /*for( size_t i = 0; i != 250; i++ )
        {
            IntroBubble* bubble = new IntroBubble();
            bubble->create();
            gGameObjects.push_back( bubble );
        }*/

        // Création du personnage
        Hiro* hiro = new Hiro();
        hiro->create( "DummyAlt" );
        hiro->setPosition( Point2f( 144.0f, 102.0f ) );
        gGameObjects.push_back( hiro );
    }

    catch( CiException const& e )
    {
        log( e );
        quit();
        return -1;
    }

    run();
    quit();
    return 0;
}
