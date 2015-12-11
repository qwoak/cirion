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
 * @file    object.hpp
 * @version 0.4.2.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    11 Décembre 2015
 * @brief   Objet graphique
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>
#include <Cirion/point.hpp>
#include <Cirion/texture.hpp>

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
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        GameObject();
        virtual ~GameObject() = 0;
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        virtual void handleEvent() = 0;
        virtual void update( int timeStep = 0 ) = 0;
        virtual void draw( int xOrigin = 0, int yOrigin = 0 );
        void setTexture( const char* name );
        void setSrc( int x, int y, int w, int h );
        void setPosition( int x, int y );
        SDL_Rect getSrc();
        SDL_Rect getDest();
        Point getPosition();

        protected:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs protégés.                            !
           +----------------------------------------------------------------+ */
        Point mPosition;   //!< Position de l'objet
        Uint8 mAlpha;      //!< Quantité alpha pour la modulation.
        Texture* mTexture; //!< La texture de l'objet
        SDL_Rect mSrc;     //!< Le repère source pour l'affichage
        SDL_Rect mDest;    //!< Le repère de destination pour l'affichage
    };
}

#endif // GAMEOBJECT_HPP
