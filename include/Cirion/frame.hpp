/*
 * This file is part of Cirion.
 *
 * Cirion, a side-scrolling game engine built over SDL2 and TinyXML2.
 * Copyright (C) 2015 Salmon Jérémy
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
 * @file    frame.hpp
 * @version 0.1
 * @author  Jérémy Salmon <qwoak11@gmail.com>
 * @date    15 Octobre 2015
 * @brief   Definition de types structurés pour l'animation des entités.
 */

 #ifndef FRAME_HPP
 #define FRAME_HPP

namespace cirion
{
    /**
     * Une "sous-image" utilisée pour stocker la position d'un sprite dans le
     * spritesheet.
     */
    typedef struct
    {
        int src_x; //!< Abscisse du sprite dans le spritesheet
        int src_y; //!< Ordonnée du sprite dans le spritesheet
    } subframe_t;

    /**
     * Une structure représentant un moment de l'animation d'une entité.
     */
    typedef struct
    {
        subframe_t left;     //!< Ss. image utilisée pour l'orientation à gauche
        subframe_t right;    //!< Ss. image utilisée pour l'orientation à droite
        int        duration; //!< Durée d'aff. du sprite en ms (0 = infinie)
    } frame_t;
}

#endif // FRAME_HPP
