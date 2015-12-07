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
 * @file    timer.hpp
 * @version 1.0
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    22 Août 2015
 * @brief   Minuterie
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL2/SDL.h>

namespace cirion
{
    /**
     * @class Timer timer.hpp
     *
     * Une classe pour mesurer l'écoulement du temps.
     */
    class Timer
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Timer();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes.                                      !
           +----------------------------------------------------------------+ */
        bool isRunning();
        void start();
        void stop();
        void reset();
        Uint32 getTicks();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs.                                     !
           +----------------------------------------------------------------+ */
        bool mRunning;      //!< Drapeau de mise en fonction
        Uint32 mStartTicks; //!< Compteur de battements au démarrage
        Uint32 mStopTicks;  //!< Compteur de battements à l'arrêt
    };
}

#endif // TIMER_HPP
