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
 * @file    entity.cpp
 * @version 0.1.4
 * @author  Jérémy S. "Qwoak"
 * @date    14 Janvier 2016
 * @brief   Manipulation des entités.
 */

#include <sstream>
#include <tinyxml2.h>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/entity.hpp>
#include <Cirion/point2.hpp>
#include <Cirion/xmlerror.hpp>

using namespace cirion;
using namespace std;
using namespace tinyxml2;

//! @brief Constructeur pour la classe Entity.
cirion::Entity::Entity()
{
}

//! @brief Déstructeur pour la classe Entity.
cirion::Entity::~Entity()
{
    for( size_t i = 0; i != mSprites.size(); i++ )
    {
        delete mSprites[i];
    }
}

//! @brief Procédure de chargement du fichier XML de l'entité.
//! @name Nom de l'entité dans le répertoire des entités.
//! @throw CiException en cas d'échec.
void cirion::Entity::load( const char* entityName )
{
    ostringstream filepath;

    filepath << gWorkingDir
             << "/Entities/"
             << entityName
             << ".xml";

    if( mXml.LoadFile( filepath.str().c_str() ) != XML_NO_ERROR )
    {
        ostringstream oss;

        oss << "Unable to load the entity xml file \""
            << filepath.str()
            << "\": "
            << getXmlErrorStr( mXml.ErrorID() );

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }
}

//! @brief Procédure de dessin de l'entité.
//! @param xOrigin Abscisse de l'origine du repère.
//! @param yOrigin Ordonnée de l'origine du repère.
void cirion::Entity::draw( const Point2f& origin )
{
    Point2f absolute;

    for( size_t i = 0; i != mSprites.size(); i++ )
    {
        mSprites[i]->update();
        // Calcul de la position absolue du sprite
        absolute = mPosition + mSprites[i]->getRelative();
        mSprites[i]->setPosition( absolute );
        // Dessin du sprite
        mSprites[i]->draw( origin );
    }
}

//! @brief  Fonction de récuperation d'un noeud <sprite> dans le XML de l'entité.
//! @brief  spriteNodeName Nom du noeud du sprite.
//! @return Pointeur vers le noeud <sprite>
//! @throw  CiException en cas d'échec.
XMLElement* cirion::Entity::getSpriteNode( const char* spriteName )
{
    XMLElement* entityNode;
    XMLElement* spriteNode;

    // Récuperation du noeud <entity>.
    entityNode = mXml.FirstChildElement( (const char*)"entity" );

    if( entityNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to get sprite node \""
            << spriteName
            << "\": Expected <entity> node.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // Récuperation du premier noeud <sprite>.
    spriteNode = entityNode->FirstChildElement( (const char*)"sprite" );

    if( spriteNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to get sprite node \""
            << spriteName
            << "\": Expected <sprite> node.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    while( (string)( spriteNode->Attribute( "name" ) ) != spriteName )
    {
        spriteNode = spriteNode->NextSiblingElement();

        if( spriteNode == NULL )
        {
            ostringstream oss;

            oss << "Unable to get sprite node \""
                << spriteName
                << "\": not found.";

            throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
        }
    }

    return spriteNode;
}
