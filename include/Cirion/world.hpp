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
 * @file    world.hpp
 * @version 0.4.1
 * @author  Jérémy S. "Qwoak"
 * @date    21 Décembre 2015
 * @brief   Le monde.
 */

#ifndef WORLD_HPP
#define WORLD_HPP
#define TILE_W 16
#define TILE_H 16

#include <fstream>
#include <vector>
#include <Cirion/cmf.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/point2.hpp>
#include <Cirion/surface.hpp>
#include <Cirion/texture.hpp>

extern const int tileWidth;
extern const int tileHeight;

namespace cirion
{
    /**
     * @class World world.hpp
     *
     * Une classe pour maniupuler le monde.
     */
    class World
    {
    public:
        World();
        ~World();
        void create( const char* name );
        void handleEvent( SDL_Event* event = NULL );
        void update( int timeStep = 0 );
        void draw();

    private:
        void drawBackground();
        void drawMap();
        void drawObjects();

        /** Position dans le monde */
        Point2f mPosition;
        /** Les données de la map */
        Cmf mCmf;
        /** La texture du tileset */
        Texture mTileset;
        /** La texture du background */
        Texture mBackground;
        /** Repère source de la tuile */
        SDL_Rect mTileSrc;
        /** Repère de destination de la tuile */
        SDL_Rect mTileDest;
        /** Repère source du background */
        SDL_Rect mBackgroundSrc;
        /** Repère de destination du background */
        SDL_Rect mBackgroundDest;
        /** Vecteur des objets contenu dans le monde */
        std::vector<GameObject*> mObjects;
    };
}

#endif
