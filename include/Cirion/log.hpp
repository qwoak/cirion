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
 * @file    log.hpp
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    23 Août 2015
 * @brief   Report des messages au journal.
 */

#ifndef LOG_HPP
#define LOG_HPP

#include <Cirion/log.hpp>

namespace cirion
{
    void log( const char* msg, const char* from );
    void log( CiException e );
}

#endif // LOG_HPP
