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
 * @file    sprite.cpp
 * @version 0.1
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    09 Decembre 2015
 * @brief   Manipulation des sprites.
 */

#include <sstream>
#include <tinyxml2.h>
#include <Cirion/ciexception.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/sprite.hpp>

using namespace std;
using namespace tinyxml2;

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Sprite.
cirion::Sprite::Sprite():
    mFrameIndex      (0    ),
    mCurrentAnimation(NULL ),
    mCollidable      (false)
{
    mHitbox.xRelative = 0;
    mHitbox.yRelative = 0;
    mHitbox.width     = 0;
    mHitbox.height    = 0;
}

//! @brief Déstructeur pour la classe Sprite.
cirion::Sprite::~Sprite()
{
}

/* +------------------------------------------------------------------------+
   ! Définition des méthodes publiques                                      !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de création d'un sprite.
//! @param *spriteNode Pointeur vers un noeud XML <sprite>.
void cirion::Sprite::create( XMLElement* spriteNode )
{
    XMLElement*     animationNode;
    XMLElement*     frameNode;
    XMLElement*     leftNode;
    XMLElement*     rightNode;
    Animation       animation;
    Frame           frame;

    if( spriteNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to fetch sprite data: "
            << "<sprite> node pointer is NULL.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // Récuperation du 1er noeud <animation>.
    animationNode = spriteNode->FirstChildElement( (const char*)"animation" );

    if( animationNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to fetch sprite data: "
            << "Expected at least one <animation> node.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Parcours de tous les noeuds <animation>. ----------------------------
    while( animationNode != NULL )
    {
        animation.frames.clear();

        // Récuperation du nom de l'animation.
        animation.name = animationNode->Attribute( "name" );

        // Récuperation du noeud <frame>.
        frameNode = animationNode->FirstChildElement( "frame" );

        if( frameNode == NULL )
        {
            ostringstream oss;

            oss << "Unable to fetch sprite data: "
                << "Expected at least one <frame> node.";

            throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
        }

        // --- Parcours de tous les noeuds <frame>. ----------------------------
        while( frameNode != NULL )
        {
            // Récuperation de la durée d'affichage de l'image.
            frame.duration = frameNode->IntAttribute( "duration" );

            // Récuperation du noeud <left>.
            leftNode = frameNode->FirstChildElement( "left" );

            if( leftNode == NULL )
            {
                ostringstream oss;

                oss << "Unable to fetch sprite data: "
                    << "Expected <left> node.";

                throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
            }

            // Récuperation des coordonnées sources du fragment gauche.
            frame.left.srcX = leftNode->IntAttribute( "src_x" );
            frame.left.srcY = leftNode->IntAttribute( "src_y" );

            // Récuperation du noeud <right>.
            rightNode = frameNode->FirstChildElement( "right" );

            if( rightNode == NULL )
            {
                ostringstream oss;

                oss << "Unable to fetch sprite data: "
                    << "Expected <right> node.";

                throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
            }

            // Récuperation des coordonnées sources du fragment droit.
            frame.right.srcX = rightNode->IntAttribute( "src_x" );
            frame.right.srcY = rightNode->IntAttribute( "src_y" );

            // Ajout de l'image dans l'animation.
            animation.frames.push_back( frame );

            // Noeud <frame> suivant.
            frameNode = frameNode->NextSiblingElement();
        }

        // Ajout de l'animation dans les animations du sprite.
        mAnimations.push_back( animation );

        // Noeud <animation> suivant.
        animationNode = animationNode->NextSiblingElement();
    }
}

//! @brief Procédure de test de collision d'un sprite.
//! @param *sprite Pointeur vers l'élement à collisionner avec le sprite.
//! @return Le résultat du test de collision.
//!     false: le sprite ne collisionne pas.
//!     true : le sprite collisionne.
bool cirion::Sprite::collide( Sprite* sprite )
{
    bool xCollide  = mHitbox.x >= sprite->getPosition().x
                                + sprite->getHitbox().xRelative
                  && mHitbox.x <= sprite->getPosition().x
                                + sprite->getHitbox().xRelative 
                                + sprite->getHitbox().width;

    bool yCollide  = mHitbox.y >= sprite->getPosition().y
                                + sprite->getHitbox().yRelative
                  && mHitbox.y <= sprite->getPosition().y
                                + sprite->getHitbox().yRelative 
                                + sprite->getHitbox().height;

    return xCollide & yCollide;
}

//! @brief Procédure de traîtement de l'évenement.
void cirion::Sprite::handleEvent( SDL_Event* event )
{
    //!< Il n'y a pas d'évenements à traiter pour l'objet Sprite.
}

//! @brief Procédure de mise à jour du sprite.
void cirion::Sprite::update( int timeStep )
{
    /**
     * Il n'y a pas de mises à jour à effectuer pour l'objet Sprite. En
     * principe, un Acteur met à jour les sprites qu'il contient.
     */
}

//! @brief Procédure de définition de l'animation utilisée par le sprite.
//! @param *name Nom de l'animation dans le vecteur d'animation du sprite.
//! @return CiException en cas d'échec.
void cirion::Sprite::setAnimation( const char* name )
{
    //! @todo: A implémenter.
}
