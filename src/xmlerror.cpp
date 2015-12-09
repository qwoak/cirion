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
 * @file    xmlerror.cpp
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    11 Août 2015
 * @brief   Description des erreurs TinyXML2.
 */

#include <iostream>
#include <Cirion/xmlerror.hpp>

using namespace std;
using namespace tinyxml2;

/* +------------------------------------------------------------------------+
   ! Définitions méthodes.                                                  !
   +------------------------------------------------------------------------+ */

//! @brief Retourne une description d'une erreur TinyXML2.
//! @param errorID Identifiant de l'erreur.
//! @return Description de l'erreur.
string cirion::getXmlErrorStr( const XMLError errorId )
{
    switch( errorId )
    {
        case XML_NO_ATTRIBUTE:
        return "No attributes.";

        case XML_WRONG_ATTRIBUTE_TYPE:
        return "Wrong attribute type.";

        case XML_ERROR_FILE_NOT_FOUND:
        return "File not found.";

        case XML_ERROR_FILE_COULD_NOT_BE_OPENED:
        return "The specified file couldn't be open.";

        case XML_ERROR_FILE_READ_ERROR:
        return "Read error.";

        case XML_ERROR_ELEMENT_MISMATCH:
        return "Element mismatch.";

        case XML_ERROR_PARSING_ELEMENT:
        return "Error while parsing element.";

        case XML_ERROR_PARSING_ATTRIBUTE:
        return "Error while parsing attribute.";

        case XML_ERROR_IDENTIFYING_TAG:
        return "Error while identifying tag.";

        case XML_ERROR_PARSING_TEXT:
        return "Error while parsing text.";

        case XML_ERROR_PARSING_CDATA:
        return "Error while parsing cdata.";

        case XML_ERROR_PARSING_COMMENT:
        return "Error while parsing comment.";

        case XML_ERROR_PARSING_DECLARATION:
        return "Error while parsing declaration.";

        case XML_ERROR_PARSING_UNKNOWN:
        return "Unknown parsing error.";

        case XML_ERROR_EMPTY_DOCUMENT:
        return "Empty document.";

        case XML_ERROR_MISMATCHED_ELEMENT:
        return "Mismatched element";

        case XML_ERROR_PARSING:
        return "Parsing error.";

        case XML_CAN_NOT_CONVERT_TEXT:
        return "Unable to convert text.";

        case XML_NO_TEXT_NODE:
        return "No text node.";

        default:
        return "All you need is love.";
    }
}
