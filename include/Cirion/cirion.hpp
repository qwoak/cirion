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
 * @file    cirion.hpp
 * @version 0.2.3
 * @author  Jérémy S. "Qwoak"
 * @date    13 Janvier 2016
 * @brief   Coeur du moteur
 */

#ifndef CIRION_HPP
#define CIRION_HPP

#include <vector>
#include <Cirion/config.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/texture.hpp>
#include <Cirion/timer.hpp>
#include <Cirion/world.hpp>

extern const char* gVersion;
extern const char* gWorkingDir;
extern const int gRendererWidth;
extern const int gRendererHeight;
extern cirion::Config gConfig;
extern bool gIsRunning;
extern cirion::Timer gRenderTimer;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Event gEvent;
extern std::vector<cirion::Texture*> gTextures;
extern std::vector<cirion::GameObject*> gGameObjects;
extern cirion::World gWorld;

namespace cirion
{
    void init();
    void handleEvents();
    void update( int timeStep = 0 );
    void render();
    void run();
    void quit();
}

#endif // CIRION_HPP
