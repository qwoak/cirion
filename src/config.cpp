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
 * @file    config.cpp
 * @version 0.2
 * @author  Jérémy S. "Qwoak"
 * @date    03 Janvier 2015
 * @brief   Gestion de la configuration.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <SDL2/SDL.h>
#include <Cirion/ciexception.hpp>
#include <Cirion/config.hpp>
#include <Cirion/xmlerror.hpp>

using namespace std;
using namespace tinyxml2;
using namespace cirion;

//! @brief Constructeur pour la classe Config.
cirion::Config::Config() :
    mWindowWidth( 640 ),
    mWindowHeight( 480 ),
    mIsFullscreen( false ),
    mIsHwRenderEnabled( true ),
    mIsVsyncEnabled( true )
{
    mKeyboardMap.up    = SDLK_z;
    mKeyboardMap.down  = SDLK_s;
    mKeyboardMap.left  = SDLK_q;
    mKeyboardMap.right = SDLK_d;
    mKeyboardMap.jump  = SDLK_l;
    mKeyboardMap.fire  = SDLK_m;
}

//! @brief Procédure de chargement d'un fichier de configuration.
//! @param filepath Chemin vers le fichier.
//! @throw CiException en cas d'échec.
void cirion::Config::load( const char* filepath )
{
    tinyxml2::XMLDocument xml;
    tinyxml2::XMLElement* configNode;
    tinyxml2::XMLElement* windowNode;
    tinyxml2::XMLElement* rendererNode;
    tinyxml2::XMLElement* keymapNode;
    tinyxml2::XMLElement* upNode;
    tinyxml2::XMLElement* downNode;
    tinyxml2::XMLElement* leftNode;
    tinyxml2::XMLElement* rightNode;
    tinyxml2::XMLElement* jumpNode;
    tinyxml2::XMLElement* fireNode;

    // --- Ouverture du fichier XML. -------------------------------------------
    if( xml.LoadFile( filepath ) != XML_NO_ERROR )
    {
        ostringstream oss;

        oss << "Unable to load the configuration file \""
            << filepath
            << "\": "
            << getXmlErrorStr( xml.ErrorID() );

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Récuperation du noeud <config>. -------------------------------------
    configNode = xml.FirstChildElement( "config" );

    if( configNode!= NULL )
    {
        // --- Récuperation du neud <window>. ----------------------------------
        windowNode = configNode->FirstChildElement( "window" );

        if( windowNode != NULL )
        {
            windowNode->QueryIntAttribute ( "w" , &mWindowWidth  );
            windowNode->QueryIntAttribute ( "h" , &mWindowHeight );
            windowNode->QueryBoolAttribute( "fs", &mIsFullscreen   );
        }

        // --- Récuperation du neud <renderer>. --------------------------------
        rendererNode = configNode->FirstChildElement( "renderer" );

        if( rendererNode != NULL )
        {
            rendererNode->QueryBoolAttribute( "hw"   , &mIsHwRenderEnabled );
            rendererNode->QueryBoolAttribute( "vsync", &mIsVsyncEnabled    );
        }

        // --- Récuperation du neud <keymap>. ----------------------------------
        keymapNode = configNode->FirstChildElement( "keymap" );

        if( keymapNode != NULL )
        {
            // --- Récuperation du neud <up>. ----------------------------------
            upNode = keymapNode->FirstChildElement( "up" );

            if( upNode != NULL )
            {
                upNode->QueryIntAttribute ( "value" , &mKeyboardMap.up );
            }

            // --- Récuperation du neud <down>. --------------------------------
            downNode = keymapNode->FirstChildElement( "down" );

            if( downNode != NULL )
            {
                downNode->QueryIntAttribute ( "value" , &mKeyboardMap.down );
            }

            // --- Récuperation du neud <left>. --------------------------------
            leftNode = keymapNode->FirstChildElement( "left" );

            if( leftNode != NULL )
            {
                leftNode->QueryIntAttribute ( "value" , &mKeyboardMap.left );
            }

            // --- Récuperation du neud <right>. -------------------------------
            rightNode = keymapNode->FirstChildElement( "right" );

            if( rightNode != NULL )
            {
                rightNode->QueryIntAttribute ( "value" , &mKeyboardMap.right );
            }

            // --- Récuperation du neud <jump>. --------------------------------
            jumpNode = keymapNode->FirstChildElement( "jump" );

            if( jumpNode != NULL )
            {
                jumpNode->QueryIntAttribute ( "value" , &mKeyboardMap.jump );
            }

            // --- Récuperation du neud <fire>. --------------------------------
            fireNode = keymapNode->FirstChildElement( "fire" );

            if( fireNode != NULL )
            {
                fireNode->QueryIntAttribute ( "value" , &mKeyboardMap.fire );
            }
        }
    }
}

//! @brief Procédure d'écriture du fichier de configuration sur le disque.
//! @param filepath Chemin vers le fichier.
//! @throw CiException en cas d'échec.
void cirion::Config::write( const char* filepath )
{
}
