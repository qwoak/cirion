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
 * @file    texture.hpp
 * @version 0.4
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Manipulation des textures.
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <Cirion/surface.hpp>

namespace cirion
{
    /**
     * @class Texture texture.hpp
     *
     * Une classe pour manipuler les textures.
     */
    class Texture
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Texture();
        ~Texture();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create( Surface* surface );
        void create( const char* name );
        void setBlendMode( SDL_BlendMode mode );
        void setAlphaMod( Uint8 a );
        void setRgbMod( Uint8 r, Uint8 g, Uint8 b );
        const char* getName();
        SDL_Texture* getSdl2Texture();
        int getWidth();
        int getHeight();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes privées.                              !
           +----------------------------------------------------------------+ */
        void setName( const char* name );
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs.                                     !
           +----------------------------------------------------------------+ */
        char* mName;           //!< Le nom de la texture.
        SDL_Texture* mTexture; //!< La structure de texture SDL2;
    };
}

#endif // TEXTURE_HPP
