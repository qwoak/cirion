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
 * @version 0.3.0.1
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Demo.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <Cirion/bubble.hpp>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>    
#include <Cirion/graphic.hpp>
#include <Cirion/log.hpp>
#include <Cirion/object.hpp>
#include <Cirion/world.hpp>

using namespace std;
using namespace cirion;

extern World gWorld;      //!< cf. cirion.cpp
extern char* gWorkingDir; //!< cf. cirion.cpp
extern vector<Object*>gObjects;

int main( int argc, char* argv[] )
{
    // Définition du chemin des ressources.
    setWorkingDir( (char*)"./Data" );

    try
    {
    	// Initialisation des libs et du moteur.
        init();

        // Creation du monde à partir du cmf.
        gWorld.create( (const char*)"Default" );

        // Géneration du champ de bulles.
        for( size_t i = 0; i != 250; i++ )
        {
            Bubble* bubble = new Bubble();
            bubble->create();

            // Envoi de la bulle dans le vecteur d'objets
            gObjects.push_back( bubble );
        }

        /**
         * @todo Pour l'introduction: Envoyer un event perso pour stopper la
         * regéneration des bulles après un certain temps.
         */

        // Création du logo.
        Graphic* logo = new Graphic();
        logo->setTexture( (const char*)"Logo" );
        logo->setSrc( 0, 0, 137, 56 );
        logo->setPosition( 92, 20 );

        // Envoi du logo dans le vecteur d'objets.
        gObjects.push_back( logo );

        /**
        * Le dernier objet envoyé a la priorité d'affichage la plus élevée.
        */
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