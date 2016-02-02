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
 * @file    introbubble.hpp
 * @version 0.2.3
 * @author  Jérémy S. "Qwoak"
 * @date    01 Janvier 2016
 * @brief   Bulle utilisée dans l'introduction.
 */

#ifndef INTROBUBBLE_HPP
#define INTROBUBBLE_HPP

#include <Cirion/gameobject.hpp>
#include <Cirion/point3.hpp>

namespace cirion
{
    class IntroBubble : public GameObject
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        IntroBubble();
        ~IntroBubble();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create();
        void update( int timeStep = 0 );
        void handleEvent( SDL_Event* event = NULL );

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes privées.                              !
           +----------------------------------------------------------------+ */
        void regen( bool randomDepth = false );
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privéss.                             !
           +----------------------------------------------------------------+ */
        Point3f mBubblePosition;
    };
}

#endif // INTROBUBBLE_HPP
