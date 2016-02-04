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
 * @file    hiro.hpp
 * @version 0.2
 * @author  Jérémy S. "Qwoak"
 * @date    31 Janvier 2016
 * @brief   Personnage jouable.
 */

#ifndef HIRO_HPP
#define HIRO_HPP

#include <Cirion/entity.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/sprite.hpp>

#define HIRO_XVELOCITY_MAX  0.1f       // Pixels / ms
#define HIRO_XVELOCITY_STEP 0.0005f   // Pixels / ms

namespace cirion
{
    class Hiro : public Entity
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Hiro();
        ~Hiro();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create( const char* entityName );
        void handleEvent( SDL_Event* event = NULL );
        void update( int timeStep = 0 );

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privés.                              !
           +----------------------------------------------------------------+ */
        float mXVelocity;
        float mYVelocity;
        bool mInputLeft;
        bool mInputRight;
        bool mStatusGoLeft;
        bool mStatusGoRight;
        Sprite* mMainSprite;
    };
}

#endif // HIRO_HPP
