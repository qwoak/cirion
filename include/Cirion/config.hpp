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
 * @version 0.2
 * @author  Jérémy S. "Qwoak"
 * @date    03 Janvier 2016
 * @brief   Gestion de la configuration.
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <tinyxml2.h>

namespace cirion
{
    /**
     * @struct Keymap
     *
     * Une structure pour stocker la carte des touches.
     */
    typedef struct
    {
        int up, down, left, right, jump, fire;
    } Keymap;

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
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void load( const char* filepath );
        void write( const char* filepath );
        
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs publiques.                           !
           +----------------------------------------------------------------+ */
        int mWindowWidth;
        int mWindowHeight;
        bool mIsFullscreen;
        bool mIsHwRenderEnabled;
        bool mIsVsyncEnabled;
        Keymap mKeyboardMap;
    };
}

#endif // CONFIG_HPP
