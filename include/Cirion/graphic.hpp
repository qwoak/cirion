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
 * @file    graphic.hpp
 * @version 0.1.2
 * @author  Jérémy S. "Qwoak"
 * @date    21 Decembre 2015
 * @brief   Element graphique singulier.
 */

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <Cirion/gameobject.hpp>

namespace cirion
{
    class Graphic : public GameObject
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Graphic();
        ~Graphic();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void handleEvent( SDL_Event* event = NULL );
        void update( int timeStep = 0 );
    };
}

#endif // GRAPHIC_HPP
