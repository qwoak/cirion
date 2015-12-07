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
 * @file    log.cpp
 * @version 0.1.0.2
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Report des messages au journal.
 */

#include <iostream>
#include <ostream>
#include <fstream>
#include <Cirion/ciexception.hpp>
#include <Cirion/log.hpp>

using namespace std;

#ifdef DEBUG
    /** Le flux de notre journal, redirigé vers std::clog */
    ostream gCirionLog( clog.rdbuf() );
#else
    /** Un flux de fichier. */
    ofstream gLogFile( "Cirion.log" );
    /** Le flux de notre journal, redirigé vers le flux de fichier. */
    ostream  gCirionLog( gLogFile.rdbuf() );
#endif

//! @brief Procédure de report des messages au journal.
//! @param msg Message.
//! @param from Identifiant de l'appelant.
void cirion::log( const char* msg, const char* from )
{
    gCirionLog << "[INFO from "
               << from
               << "]: "
               << endl
               << msg
               << endl
               << endl;
}

//! @brief Procédure de report des exceptions au journal.
//! @param e Exception Cirion
void cirion::log( CiException e )
{
    gCirionLog << "[EXCEPTION from "
               << e.from()
               << "]: "
               << endl
               << e.what()
               << endl
               << endl;
}
