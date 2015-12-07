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
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Août 2015
 * @brief   Gestion de la configuration.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <Cirion/ciexception.hpp>
#include <Cirion/xmlerror.hpp>
#include <Cirion/config.hpp>

using namespace std;
using namespace tinyxml2;
using namespace cirion;

/* +------------------------------------------------------------------------+
   ! Définitions des constructeurs / déstructeurs.                          !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Config.
cirion::Config::Config()
{
    mFullscreen         = false;
    mWindowWidth        = 640;
    mWindowHeight       = 480;
    mFullscreenWidth    = 640;
    mFullscreenHeight   = 480;
    mFramerate          = 50;
}

//! @brief Déstructeur pour la classe Config.
cirion::Config::~Config()
{
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de chargement d'un fichier de configuration.
//! @param filepath Chemin vers le fichier.
//! @throw CiException
void cirion::Config::load( string filepath )
{
    config_t config;

    // --- Ouverture du fichier XML. -------------------------------------------
    if( config.doc.LoadFile( filepath.c_str() ) != XML_NO_ERROR )
    {
        ostringstream oss;

        oss << "Unable to load the configuration file \""
            << filepath
            << "\": "
            << getXmlErrorStr( config.doc.ErrorID() );

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Récuperation du noeud racine. ---------------------------------------
    config.root = config.doc.FirstChildElement( "config" );

    if( config.root != NULL )
    {
        // --- Récuperation des neuds. -----------------------------------------
        config.window   = config.root->FirstChildElement( "window"   );
        config.renderer = config.root->FirstChildElement( "renderer" );

        // --- Lecture des attributs. ------------------------------------------
        if( config.window != NULL )
        {
            /* Configuration de la fenêtre SDL2. */
            config.window->QueryBoolAttribute( "fs"  , &mFullscreen       );
            config.window->QueryIntAttribute ( "w_w" , &mWindowWidth      );
            config.window->QueryIntAttribute ( "w_h" , &mWindowHeight     );
            config.window->QueryIntAttribute ( "fs_w", &mFullscreenWidth  );
            config.window->QueryIntAttribute ( "fs_h", &mFullscreenHeight );
        }

        if( config.renderer != NULL )
        {
            /* Configuration du rendu. */
            config.renderer->QueryIntAttribute( "fps" , &mFramerate );
        }
    }
}

//! @brief Procédure de basculement du mode plein-écran.
//! @param fullscreen Etat.
void cirion::Config::setFullscreen( bool fullscreen )
{
    mFullscreen = fullscreen;
}

//! @brief Procédure de paramètrage de la taille de la fenêtre en mode fenétré.
//! @param width Largeur en pixels.
//! @param height Hauteur en pixels.
void cirion::Config::setWindowSize( int width, int height )
{
    mWindowWidth  = width  <= 0 ? 0 : width;
    mWindowHeight = height <= 0 ? 0 : height;
}

//! @brief Procédure de paramètrage de la taille de la fenêtre en mode 
//! plein-écran.
//! @param width Largeur en pixels.
//! @param height Hauteur en pixels.
void cirion::Config::setFullscreenSize( int width, int height )
{
    mFullscreenWidth  = width  <= 0 ? 0 : width;
    mFullscreenHeight = height <= 0 ? 0 : height;
}

//! @brief Procédure de paramètrage de la fréquence de rafraichissement.
//! @param fps Nombre d'images par secondes.
void cirion::Config::setFramerate( int fps )
{
    mFramerate = fps <= 0 ? 0 : fps;
}

//! @brief Accesseur.
//! @return Etat de la fenêtre.
//!     true : Mode plein-écran.
//!     false: mode fenétré.
bool cirion::Config::isFullscreen()
{
    return mFullscreen;
}

//! @brief Accesseur.
//! @return Largeur en pixels de la fenêtre dans le mode fenétré.
int cirion::Config::getWindowWidth()
{
    return mWindowWidth;
}

//! @brief Accesseur.
//! @return Hauteur en pixels de la fenêtre dans le mode fenétré.
int cirion::Config::getWindowHeight()
{
    return mWindowHeight;
}

//! @brief Accesseur.
//! @return Largeur en pixels de la fenêtre dans le mode plen-écran.
int cirion::Config::getFullscreenWidth()
{
    return mFullscreenWidth;
}

//! @brief Accesseur.
//! @return Heuteur en pixels de la fenêtre dans le mode plen-écran.
int cirion::Config::getFullscreenHeight()
{
    return mFullscreenHeight;
}

//! @brief Accesseur.
//! @return Taux de rafraichissement en nombre d'images par seconde.
int cirion::Config::getFramerate()
{
    return mFramerate;
}
