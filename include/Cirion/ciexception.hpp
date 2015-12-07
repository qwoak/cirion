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
 * @file    ciexception.hpp
 * @version 0.1.1.1
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Exception Cirion.
 */

#ifndef CIEXEPTION_HPP
#define CIEXEPTION_HPP

#include <exception>
#include <string>

namespace cirion
{
    class CiException : public std::exception
    {
        public:
        /* +----------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.                  !
           +----------------------------------------------------------------+ */
        CiException( const char* whatStr, const char* fromStr ) throw();
        virtual ~CiException() throw();

        /* +----------------------------------------------------------------+
           ! Déclaration des accesseurs.                                    !
           +----------------------------------------------------------------+ */
        virtual const char* what() const throw();
        virtual const char* from() const throw();

        private:
        /* +----------------------------------------------------------------+
           ! Déclaration des attributs.                                     !
           +----------------------------------------------------------------+ */
        std::string mWhatStr;
        std::string mFromStr;
    };
}

#endif // CIEXEPTION_HPP
