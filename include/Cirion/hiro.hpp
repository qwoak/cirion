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
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    11 Novembre 2015
 * @brief   Personnage jouable.
 */

#ifndef HIRO_HPP
#define HIRO_HPP

#include <Cirion/frame.hpp>
#include <Cirion/object.hpp>

namespace cirion
{
    /**
     * @class Hiro hiro.hpp
     *
     * Une classe pour manipuler le personnage jouable.
     */
    class Hiro: public Object
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
        void create();
        void update();
        void handleEvent();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privés.                              !
           +----------------------------------------------------------------+ */
        bool mIsFacingRight;
        std::vector<cirion::frame_t> mStandingFrames;
        std::vector<cirion::frame_t> mRunningFrames;
    };
}

#endif // HIRO_HPP
