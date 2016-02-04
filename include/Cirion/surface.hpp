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
 * @file    surface.hpp
 * @version 0.2.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    28 Novembre 2015
 * @brief   Manipulation des surfaces.
 */

#ifndef SURFACE_HPP
#define SURFACE_HPP

// Définition du masque RGBA
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define R_MASK 0xff000000
    #define G_MASK 0x00ff0000
    #define B_MASK 0x0000ff00
    #define A_MASK 0x000000ff
#else
    #define R_MASK 0x000000ff
    #define G_MASK 0x0000ff00
    #define B_MASK 0x00ff0000
    #define A_MASK 0xff000000
#endif

#include <SDL2/SDL.h>

namespace cirion
{
    /**
     * @class Surface surface.hpp
     *
     * Une classe pour manipuler les surfaces.
     */
    class Surface
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Surface();
        ~Surface();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create( int width, int height );
        void create( const char* filepath );
        void setBlendMode( SDL_BlendMode mode );
        void setAlphaMod( Uint8 alpha );
        void setRgbMod( Uint8 red, Uint8 green, Uint8 blue );
        SDL_Surface* getSdl2Surface();
        int getWidth();
        int getHeight();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privés.                              !
           +----------------------------------------------------------------+ */
        SDL_Surface* mSurface; //!< La structure de surface SDL2
    };
}

#endif // SURFACE_HPP
