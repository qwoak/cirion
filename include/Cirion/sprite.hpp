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
 * @file    sprite.hpp
 * @version 0.1.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    11 Decembre 2015
 * @brief   Manipulation des sprites.
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <tinyxml2.h>
#include <Cirion/gameobject.hpp>

namespace cirion
{
    /**
     * Une structure pour représenter un fragment dans un spritesheet.
     */
    typedef struct
    {
        int srcX;
        int srcY;
    } Piece;

    /**
     * Une structure pour représenter la Hitbox d'un sprite.
     */
    typedef struct
    {
        int xRelative;
        int yRelative;
        int width;
        int height;
    } Hitbox;

    /**
     * Une structure pour représenter une image dans une animation.
     */
    typedef struct
    {
        Piece left;
        Piece right;
        int duration;
    } Frame;

    /**
     * Une structure pour représenter une animation d'un sprite.
     */
    typedef struct
    {
        const char* name;
        std::vector<Frame> frames;
    } Animation;

    /**
     * @class Sprite sprite.hpp
     *
     * Une classe derivée pour manipuler des sprites.
     */
    class Sprite : public GameObject {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        Sprite();
        ~Sprite();
        /* +----------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                            !
           +----------------------------------------------------------------+ */
        void create( tinyxml2::XMLElement* spriteNode );
        bool collide( Sprite* sprite );
        void handleEvent( SDL_Event* event );
        void update( int timeStep = 0 );
        void setAnimation( const char* name );
        Hitbox getHitbox();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs privés.                              !
           +----------------------------------------------------------------+ */
        int mFrameIndex;
        std::vector<Animation> mAnimations;
        Animation* mCurrentAnimation;
        Hitbox mHitbox;
        bool mCollidable;
    };
}

#endif // SPRITE_HPP
