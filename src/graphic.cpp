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
 * @file    graphic.cpp
 * @version 0.2.1
 * @author  Jérémy S. "Qwoak"
 * @date    21 Décembre 2015
 * @brief   Element graphique singulier.
 */

#include <Cirion/graphic.hpp>

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Graphic
cirion::Graphic::Graphic()
{
}

//! @brief Déstructeur pour la classe Graphic
cirion::Graphic::~Graphic()
{
}

/* +------------------------------------------------------------------------+
   ! Définition des méthodes publiques                                      !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de traîtement de l'évenement.
void cirion::Graphic::handleEvent( SDL_Event* event )
{
    //!< Il n'y a pas d'évenements à traiter pour l'objet Graphic.
}

//! @brief Procédure de mise à jour de l'objet.
//! @param timeStep Temps écoulé depuis la dernière image.
void cirion::Graphic::update( int timeStep )
{
    //!< Il n'y a pas de mises à jour à effectuer pour l'objet Graphic.
}
