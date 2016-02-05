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
 * @file    gameobject.hpp
 * @version 0.4.4
 * @author  Jérémy S. "Qwoak"
 * @date    05 Février 2016
 * @brief   Manipulation des objets.
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>
#include <Cirion/texture.hpp>
#include <Cirion/point2.hpp>

namespace cirion
{
    /**
     * @class Object object.hpp
     *
     * Une classe abstraîte pour manipuler des objets.
     */
    class GameObject
    {
        public:
        GameObject();
        virtual ~GameObject();
        virtual void handleEvent( SDL_Event* event = NULL ) = 0;
        virtual void update( int dt = 0, void* data = NULL ) = 0;
        virtual void draw( const Point2f& origin = Point2f( 0, 0 ) );
        void setTexture( const char* name );
        void setSrc( int x, int y, int w, int h );
        void setPosition( const Point2f& position );
        SDL_Rect getSrc();
        SDL_Rect getDest();
        Point2f getPosition();

        protected:
        /** La position de l'objet */
        Point2f mPosition;
        /** Pointeur vers la texture de l'objet */
        Texture* mTexture;
        /** Le repère source, pour l'affichage */
        SDL_Rect mSrc;
        /** Le repère de destination, pour l'affichage */
        SDL_Rect mDest;
    };
}

#endif // GAMEOBJECT_HPP
