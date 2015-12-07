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
 * @file    config.hpp
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Août 2015
 * @brief   Gestion de la configuration.
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <tinyxml2.h>

namespace cirion
{
    /**
     * @struct config_t
     *
     * Une structure utilisée pour représenter l'architecture du fichier de
     * configuration.
     */
    typedef struct
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* root;
        tinyxml2::XMLElement* window;
        tinyxml2::XMLElement* renderer;

    } config_t;

    /**
     * @class Config config.hpp
     *
     * Une classe pour charger, modifier et sauvegarder un fichier de
     * configuration Cirion au format XML.
     */
    class Config
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Config();
        ~Config();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes.                                      !
           +----------------------------------------------------------------+ */
        void load( std::string filepath );
        void setFullscreen( bool fullscreen );
        void setWindowSize( int width, int height );
        void setFullscreenSize( int width, int height );
        void setFramerate( int framerate );
        bool isFullscreen();
        int getWindowWidth();
        int getWindowHeight();
        int getFullscreenWidth();
        int getFullscreenHeight();
        int getFramerate();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs.                                     !
           +----------------------------------------------------------------+ */
        bool mFullscreen;      //!< Drapeau de plein-écran
        int mWindowWidth;      //!< Largeur de la fenêtre SDL2 en pixels
        int mWindowHeight;     //!< Hauteur de la fenêtre SDL2 en pixels
        int mFullscreenWidth;  //!< Largeur plein-écran en pixels
        int mFullscreenHeight; //!< Hauteur plein-écran en pixels
        int mFramerate;        //!< Taux de rafraichissement désiré
    };
}

#endif // CONFIG_HPP
