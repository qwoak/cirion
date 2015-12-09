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
 * @version 0.2.1.2
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    04 Decembre 2015
 * @brief   Cirion Engine.
 */

#ifndef CIRION_HPP
#define CIRION_HPP
#define CIRION_VER  (const char*)"0.3.1" // major.minor[.build[.revision]]
#define RENDERER_W  320
#define RENDERER_H  240

namespace cirion
{
    void init();
    void handleEvents();
    void update();
    void render();
    void run();
    void quit();
}

#endif // CIRION_HPP
