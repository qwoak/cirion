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
 * @version 0.3.2.1
 * @author  Jérémy S. "Qwoak"
 * @date    31 Janvier 2016
 * @brief   Manipulation des sprites.
 */

#include <sstream>
#include <tinyxml2.h>
#include <Cirion/ciexception.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/log.hpp>
#include <Cirion/point2.hpp>
#include <Cirion/sprite.hpp>

using namespace cirion;
using namespace std;
using namespace tinyxml2;

//! @brief Constructeur pour la classe Sprite.
cirion::Sprite::Sprite():
    mRelative( Point2f( 0.0f, 0.0f ) ),
    mCollidable( false ),
    mFacingRight( false ),
    mEleapsed( 0 ),
    mFrameIndex( 0 ),
    mAnimation( NULL )
{
    mHitbox.x = 0;
    mHitbox.y = 0;
    mHitbox.w = 0;
    mHitbox.h = 0;
}

//! @brief Déstructeur pour la classe Sprite.
cirion::Sprite::~Sprite()
{
}

//! @brief Procédure de création d'un sprite.
//! @param *spriteNode Pointeur vers un noeud XML <sprite>.
//! @throw CiException en cas d'échec.
void cirion::Sprite::create( XMLElement* spriteNode )
{
    // Si le sprite à déjà été crée ?

    XMLElement* hitboxNode;
    XMLElement* animationNode;
    XMLElement* frameNode;
    XMLElement* leftNode;
    XMLElement* rightNode;
    Animation   animation;
    Frame       frame;

    if( spriteNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to fetch sprite data: "
            << "Given <sprite> node is NULL.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    try
    {
        setTexture( spriteNode->Attribute( (const char*)"spritesheet" ) );
    }

    catch( CiException const& e )
    {
        log( e );

        throw CiException( (const char*)"Unable to process sprite creation.",
            __PRETTY_FUNCTION__ );
    }
    
    // Définition des dimensions du sprite.
    mSrc.w  = spriteNode->IntAttribute( (const char*)"src_w" );
    mSrc.h  = spriteNode->IntAttribute( (const char*)"src_h" );
    mDest.w = mSrc.w;
    mDest.h = mSrc.h;
    //cout << "mSrc.w = " << mSrc.w << endl
    //     << "mSrc.h = " << mSrc.h << endl;

    // Récuperation du noeud <hitbox>
    hitboxNode = spriteNode->FirstChildElement( (const char*)"hitbox" );

    if( hitboxNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to fetch sprite data: "
            << "Expected <hitbox> node.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    mHitbox.x = hitboxNode->IntAttribute( (const char*)"x" );
    mHitbox.y = hitboxNode->IntAttribute( (const char*)"y" );
    mHitbox.w = hitboxNode->IntAttribute( (const char*)"w" );
    mHitbox.h = hitboxNode->IntAttribute( (const char*)"h" );
    //cout << "mHitbox.x = " << mHitbox.x << endl
    //     << "mHitbox.y = " << mHitbox.y << endl
    //     << "mHitbox.w = " << mHitbox.w << endl
    //     << "mHitbox.h = " << mHitbox.h << endl;

    // Récuperation du 1er noeud <animation>.
    animationNode = spriteNode->FirstChildElement( (const char*)"animation" );

    if( animationNode == NULL )
    {
        ostringstream oss;

        oss << "Unable to fetch sprite data: "
            << "Expected <animation> node.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Parcours de tous les noeuds <animation>. ----------------------------
    while( animationNode != NULL )
    {
        animation.frames.clear();

        // Récuperation du nom de l'animation.
        animation.name = animationNode->Attribute( "name" );
        //cout << "animation.name = " << animation.name << endl;

        // Récuperation du noeud <frame>.
        frameNode = animationNode->FirstChildElement( "frame" );

        if( frameNode == NULL )
        {
            ostringstream oss;

            oss << "Unable to fetch sprite data: "
                << "Expected <frame> node.";

            throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
        }

        // --- Parcours de tous les noeuds <frame>. ----------------------------
        while( frameNode != NULL )
        {
            // Récuperation de la durée d'affichage de l'image.
            frame.duration = frameNode->IntAttribute( "duration" );
            //cout << "frame.duration = " << frame.duration << endl;

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
            frame.left.mX = leftNode->IntAttribute( "src_x" );
            frame.left.mY = leftNode->IntAttribute( "src_y" );
            //cout << "frame.left.mX = " << frame.left.mX << endl
            //     << "frame.left.mY = " << frame.left.mY << endl;

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
            frame.right.mX = rightNode->IntAttribute( "src_x" );
            frame.right.mY = rightNode->IntAttribute( "src_y" );
            //cout << "frame.right.mX = " << frame.right.mX << endl
            //     << "frame.right.mY = " << frame.right.mY << endl;

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
    if( !mCollidable ) { return false; }

    bool xCollide  = sprite->getPosition().mX >= sprite->getPosition().mX
                                               + sprite->getHitbox().x
                  && sprite->getPosition().mX <= sprite->getPosition().mX
                                               + sprite->getHitbox().x 
                                               + sprite->getHitbox().w;

    bool yCollide  = sprite->getPosition().mY >= sprite->getPosition().mY
                                               + sprite->getHitbox().y
                  && sprite->getPosition().mY <= sprite->getPosition().mY
                                               + sprite->getHitbox().y 
                                               + sprite->getHitbox().h;

    return xCollide & yCollide;
}

//! @brief Procédure de traîtement de l'évenement.
//! @param event Pointeur vers une structure d'évenements SDL2.
void cirion::Sprite::handleEvent( SDL_Event* event )
{
    // Il n'y a pas d'évenements à traiter pour l'objet Sprite.
}

//! @brief Procédure de mise à jour du sprite.
//! @param timeStep
void cirion::Sprite::update( int timeStep )
{
    if(    mAnimation->frames[mFrameIndex].duration != 0
        && mEleapsed + timeStep >= mAnimation->frames[mFrameIndex].duration )
    {
        // Màj timer
        mEleapsed = ( mEleapsed + timeStep ) 
                    % mAnimation->frames[mFrameIndex].duration;

        // Frame suivante
        mFrameIndex = ( mFrameIndex == mAnimation->frames.size() -1 )
                    ? 0
                    : mFrameIndex + 1;
    }

    else
    {
        // Màj timer
        mEleapsed += timeStep;
    }

    if( mAnimation != NULL )
    {
        // Si le sprite est orienté à droite
        if( mFacingRight )
        {
            // Màj src pour le sprite orienté à droite
            mSrc.x = mAnimation->frames[mFrameIndex].right.mX;
            mSrc.y = mAnimation->frames[mFrameIndex].right.mY;
        }

        // Le sprite est orienté a gauche
        else
        {
            // Màj src pour le sprite orienté à gauche
            mSrc.x = mAnimation->frames[mFrameIndex].left.mX;
            mSrc.y = mAnimation->frames[mFrameIndex].left.mY;
        }
    }

    //cout << mSrc.x << ", " << mSrc.y << endl;
}

//! @brief Procédure de déf. de la position du sprite relative à l'entité mère.
//! @param xRelative Différence en abscisse.
//! @param yRelative Différence en ordonnée.
void cirion::Sprite::setRelative( const Point2f& relative )
{
    mRelative = relative;
}

//! @brief Procédure de définition de l'orientation du sprite.
//! @param isFacingRight Indique si le sprite est orienté a droite.
void cirion::Sprite::setFacingRight( bool facingRight )
{
    mFacingRight = facingRight;
}

//! @brief Procédure de définition de l'animation utilisée par le sprite.
//! @param *name Nom de l'animation dans le vecteur d'animation du sprite.
//! @return CiException en cas d'échec.
void cirion::Sprite::setAnimation( const char* name )
{
    // Parcours du vecteur d'animations du sprite
    for( size_t i = 0; i != mAnimations.size(); i++ )
    {
        // Comparaison avec le nom de l'animation cherchée
        if( strcmp( mAnimations[i].name, name ) == 0 )
        {
            // Attribution de l'animation en cours
            mAnimation  = &mAnimations[i];
            mFrameIndex = 0;
            // On arrête tout
            return;
        }
    }

    // Si rien n'a été trouvé :
    ostringstream oss;

    oss << "Unable to set sprite animation \""
        << name
        <<"\" : Not found.";

    throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
}

//! @brief Fonction accesseur.
//! @return La position du sprite relative à l'entité mère.
Point2f cirion::Sprite::getRelative()
{
    return mRelative;
}

//! @brief Fonction accesseur.
//! @return La hitbox du sprite.
SDL_Rect cirion::Sprite::getHitbox()
{
    return mHitbox;
}

//! @brief Fonction accesseur.
//! @return L'orientation du sprite.
bool cirion::Sprite::isFacingRight()
{
    return mFacingRight;
}
