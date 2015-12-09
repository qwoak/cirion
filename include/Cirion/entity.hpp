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
 * @file    entity.hpp
 * @version 0.1.1.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    04 Décembre 2015
 * @brief   Manipulation des entités.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <tinyxml2.h>
#include <Cirion/frame.hpp>
#include <Cirion/gameobject.hpp>

namespace cirion
{
    class Entity : public Object
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Entity();
        virtual ~Entity();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void handleEvent();
        void update( int timeStep = 0 );
        const char* getSpritesheetName();
        std::vector<frame_t> getAnimation( const char* name );

        //protected:
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes protégés.                             !
           +----------------------------------------------------------------+ */
        void load( const char* name );
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs protégés.                            !
           +----------------------------------------------------------------+ */
        tinyxml2::XMLDocument mXml;
    };
}

#endif // ENTITY_HPP
