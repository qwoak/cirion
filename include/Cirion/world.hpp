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
 * @version 0.4.0.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    08 Novembre 2015
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
#include <Cirion/surface.hpp>
#include <Cirion/texture.hpp>

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
        /* +------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.              !
           +------------------------------------------------------------+ */
        World();
        ~World();
        /* +------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                        !
           +------------------------------------------------------------+ */
        void create( const char* name );
        void handleEvent();
        void update();
        void draw();

        private:
        /* +------------------------------------------------------------+
           ! Déclaration des méthodes privées.                          !
           +------------------------------------------------------------+ */
        void drawBackground();
        void drawMap();
        void drawObjects();
        /* +------------------------------------------------------------+
           ! Déclaration des attributs privés.                          !
           +------------------------------------------------------------+ */
        int mWorldX;                       //!< Position du monde en abscisse
        int mWorldY;                       //!< Position du monde en ordonnée
        Cmf mMap;                          //!< Les données de la map
        Texture mTileset;                  //!< Le tileset
        Texture mBackground;               //!< Le background
        SDL_Rect mTileSrc;                 //!< Source de la tuile
        SDL_Rect mTileDest;                //!< Destination de la tuile
        SDL_Rect mBackgroundSrc;           //!< Source du background
        SDL_Rect mBackgroundDest;          //!< Destination du background
        std::vector<GameObject*> mObjects; //!< Vecteur d'objets du monde
    };
}

#endif
