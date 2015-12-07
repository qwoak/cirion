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
 * @version 0.2
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Novembre 2015
 * @brief   Bulle utilisée dans l'introduction.
 */

#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include <Cirion/object.hpp>

namespace cirion
{
    /**
     * @class Bubble bubble.hpp
     *
     * Une classe pour manipuler une bulle dans un champ de bulles.
     */
    class Bubble: public Object
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Bubble();
        ~Bubble();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create();
        void update();
        void handleEvent();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privés.                              !
           +----------------------------------------------------------------+ */
        float mZ;
    };
}

#endif // BUBBLE_HPP