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
 * @file    hiro.cpp
 * @version 0.1.2
 * @author  Jérémy S. "Qwoak"
 * @date    05 Février 2016
 * @brief   Personnage jouable.
 */

#include <iostream>
#include <bitset>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/hiro.hpp>
#include <Cirion/log.hpp>
#include <Cirion/point2.hpp>
#include <Cirion/sprite.hpp>

using namespace cirion;
using namespace std;

//const float gRunningMaxVelocity  = 0.1000f ; // Px / Ms
//const float gRunningVelocityStep = 0.0005f ; // Px / Ms

//! @brief Constructeur pour la classe Hiro.
cirion::Hiro::Hiro():
    mXVelocity( 0 ),
    mYVelocity( 0 ),
    mInputLeft( false ),
    mInputRight( false ),
    mStatusGoLeft( false ),
    mStatusGoRight( false )
{
}

//! @brief Déstructeur pour la classe Hiro.
cirion::Hiro::~Hiro()
{
}

//! @brief Procédure de création du personnage jouable.
//! @param entityName Nom de l'entité dans le répertoire des entitées.
//! @throw  CiException en cas d'échec.
void cirion::Hiro::create( const char* entityName )
{
    try
    {
        // Chargement de l'entité
        load( entityName );
        // Création, chargement et positionnement du sprite.
        mMainSprite = new Sprite();
        mMainSprite->create( getSpriteNode( (const char*)"main" ) );
        mMainSprite->setAnimation( (const char*)"standing" );
        //mMainSprite->setRelative( Point2f( -8.0f, -8.0f ) );
        // Envoi du sprite dans le vecteur des sprites de l'entité.
        mSprites.push_back( mMainSprite );
    }

    catch( CiException const& e )
    {
        log( e );

        throw CiException( (const char*)"Unable to process Hiro creation.",
            __PRETTY_FUNCTION__ );
    }
}

//! @brief procédure de traîtement de l'évenement.
//! @param event Pointeur vers une structure d'évenements SDL2.
void cirion::Hiro::handleEvent( SDL_Event* event )
{
    if( event == NULL ) { return; }

    switch( event->type )
    {
        case SDL_KEYDOWN:
        switch( event->key.keysym.sym )
        {
            // --- Touche de direction gauche enfoncée -------------------------
            case SDLK_q:
            if( !mInputLeft )
            {
                // Màj des entrées
                mInputLeft = true;
                // Màj du status
                mStatusGoLeft   = true;
                mStatusGoRight = false;
                // Màj de l'orientation du sprite
                mMainSprite->setAnimation( (const char*)"running" );
                mMainSprite->setFacingRight( false );
            }

            break;

            // --- Touche de direction droite enfoncée -------------------------
            case SDLK_d:
            if( !mInputRight )
            {
                // Màj des entrées
                mInputRight = true;
                // Màj du status
                mStatusGoRight = true;
                mStatusGoLeft  = false;
                // Màj du sprite
                mMainSprite->setAnimation( (const char*)"running" );
                mMainSprite->setFacingRight( true );
            }

            break;
        }

        break;

        case SDL_KEYUP:
        switch( event->key.keysym.sym )
        {
            // --- Touche de direction gauche relachée -------------------------
            case SDLK_q:
            if( mInputLeft )
            { 
                mInputLeft    = false;
                mStatusGoLeft = false;
   
                if( mInputRight )
                {
                    mStatusGoRight = true;
                    mMainSprite->setFacingRight( true );
                }
   
                else
                {
                    mMainSprite->setAnimation( (const char*)"standing" );
                }
            }

            break;

            // --- Touche de direction droite relachée -------------------------
            case SDLK_d:

            if( mInputRight )
            {
                mInputRight    = false;
                mStatusGoRight = false;

                if( mInputLeft )
                {
                    mStatusGoLeft = true;
                    mMainSprite->setFacingRight( false );
                }

                else
                {
                    mMainSprite->setAnimation( (const char*)"standing" );
                }
            }

            break;
        }
    
        break;
    }
}

//! @brief Procédure de mise à jour du personnage jouable.
//! @param dt
void cirion::Hiro::update( int dt, void* data )
{
    if( data != NULL )
    {
        cirion::World* world = (cirion::World*)(data);
    }

    if( mStatusGoLeft )
    {
        if( mXVelocity > -HIRO_XVELOCITY_MAX )
        {
            mXVelocity -= HIRO_XVELOCITY_STEP * dt;
            mXVelocity  = mXVelocity < -HIRO_XVELOCITY_MAX
                        ? -HIRO_XVELOCITY_MAX
                        : mXVelocity;
        }
    }

    else
    {
        if( mXVelocity < 0 )
        {
            mXVelocity += HIRO_XVELOCITY_STEP * dt;
            mXVelocity  = mXVelocity > 0
                        ? 0
                        : mXVelocity;
        }
    }

    if( mStatusGoRight )
    {
        if( mXVelocity < HIRO_XVELOCITY_MAX )
        {
            mXVelocity += HIRO_XVELOCITY_STEP * dt;
            mXVelocity  = mXVelocity > HIRO_XVELOCITY_MAX
                        ? HIRO_XVELOCITY_MAX
                        : mXVelocity;
        }
    }

    else
    {
        if( mXVelocity > 0 )
        {
            mXVelocity -= HIRO_XVELOCITY_STEP * dt;
            mXVelocity  = mXVelocity < 0
                        ? 0
                        : mXVelocity;
        }
    }

    mPosition.mX += mXVelocity * dt;

    // Mise à jour du sprite
    mMainSprite->update( dt );
}
