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
 * @version 0.1.2.1
 * @author  Jérémy S. "Qwoak"
 * @date    14 Janvier 2016
 * @brief   Manipulation des entités.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <tinyxml2.h>
#include <Cirion/gameobject.hpp>
#include <Cirion/point2.hpp>
#include <Cirion/sprite.hpp>

namespace cirion
{
    class Entity : public GameObject
    {
        public:
        Entity();
        virtual ~Entity();
        void load( const char* entityName );
        void draw( const Point2f& origin = Point2f( 0.0f, 0.0f ) );
        tinyxml2::XMLElement* getSpriteNode( const char* spriteName );

        protected:
        /** Le document XML de l'entité */
        tinyxml2::XMLDocument mXml;
        /** Le vecteur de sprites qui composent l'entité */
        std::vector<Sprite*> mSprites;
    };
}

#endif // ENTITY_HPP
