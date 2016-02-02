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
 * @file    timer.cpp
 * @version 1
 * @author  Jérémy S. "Qwoak"
 * @date    22 Août 2015
 * @brief   Minuterie
 */

#include <Cirion/timer.hpp>

/* +------------------------------------------------------------------------+
   ! Définitions constructeurs / déstructeurs.                              !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Timer.
cirion::Timer::Timer()
{
    mRunning    = false;
    mStartTicks = 0;
    mStopTicks  = 0;
}

/*  +-----------------------------------------------------------------------+
    ! Définition méthodes.                                                  !
    +-----------------------------------------------------------------------+ */

//! @brief Procédure de démarrage du chronomètre.
void cirion::Timer::start()
{
    if( !mRunning )
    {
        mRunning    = true;
        mStartTicks = SDL_GetTicks() - mStopTicks;
        mStopTicks  = 0;
    }
}

//! @brief Procédure d'arrêt du chronomètre.
void cirion::Timer::stop()
{
    if( mRunning )
    {
        mRunning    = false;
        mStopTicks  = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

//! @brief Procédure de remize à zéro du chronomètre.
void cirion::Timer::reset()
{
    mStartTicks = SDL_GetTicks();
    mStopTicks  = 0;
}

//! @brief  Fonction accesseur.
//! @return Le temps d'écoulement du chronomètre.
Uint32 cirion::Timer::getTicks()
{
    return mRunning ? SDL_GetTicks() - mStartTicks : mStopTicks;
}
