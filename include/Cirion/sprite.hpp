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
 * @version 0.3
 * @author  Jérémy S. "Qwoak"
 * @date    05 Février 2016
 * @brief   Manipulation des sprites.
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <tinyxml2.h>
#include <vector>
#include <Cirion/gameobject.hpp>
#include <Cirion/point2.hpp>
#include <SDL2/SDL.h>

namespace cirion
{
    /**
     * Une structure pour représenter une image dans une animation.
     */
    typedef struct
    {
        Point2i left;
        Point2i right;
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
    class Sprite : public GameObject
    {
    public:
        Sprite();
        ~Sprite();
        void create( tinyxml2::XMLElement* spriteNode );
        bool collide( Sprite* sprite );
        void handleEvent( SDL_Event* event = NULL );
        void update( int dt = 0, void* data = NULL );
        void setRelative( const Point2f& relative );
        void setFacingRight( bool facingRight );
        void setAnimation( const char* name );
        Point2f getRelative();
        SDL_Rect getHitbox();
        bool isFacingRight();
    private:
        Point2f mRelative;
        SDL_Rect mHitbox;
        bool mCollidable;
        bool mFacingRight;
        int mEleapsed;
        unsigned int mFrameIndex;
        std::vector<Animation> mAnimations;
        Animation* mAnimation;
    };
}

#endif // SPRITE_HPP
