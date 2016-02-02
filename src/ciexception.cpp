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
 * @file	ciexception.cpp
 * @version	0.1.1
 * @author  Jérémy S. "Qwoak"
 * @date	23 Août 2015
 * @brief	Exception Cirion.
 */

#include <iostream>
#include <string>
#include <Cirion/ciexception.hpp>

using namespace std;

/* +------------------------------------------------------------------------+
   ! Définitions constructeurs / déstructeurs.								!
   +------------------------------------------------------------------------+ */

//! @brief Constructeur de la classe CiException.
//! @param what_str Message de l'exception.
//! @param from_str Origine de l'exception.
cirion::CiException::CiException(
	const char* whatStr,
	const char* fromStr) throw()
{
	mWhatStr = string( whatStr );
	mFromStr = string( fromStr );
}

//! @brief Déstructeur de la classe CiException.
cirion::CiException::~CiException() throw()
{
}

/* +------------------------------------------------------------------------+
   ! Définitions accesseurs.												!
   +------------------------------------------------------------------------+ */

//! @brief Retourne le message de l'exception.
const char* cirion::CiException::what() const throw()
{
	return mWhatStr.c_str();
}

//! @brief Retourne l'origine de l'exception.
const char* cirion::CiException::from() const throw()
{
	return this->mFromStr.c_str();
}
