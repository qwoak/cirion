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
 * @file    texture.cpp
 * @version 0.4
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Manipulation des textures.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <Cirion/ciexception.hpp>
#include <Cirion/log.hpp>
#include <Cirion/surface.hpp>
#include <Cirion/texture.hpp>

using namespace std;
using namespace cirion;

extern char*            gWorkingDir; //!< cf cirion.cpp
extern SDL_Renderer*    gRenderer;    //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Texture.
cirion::Texture::Texture():
    mName   (NULL),
    mTexture(NULL)
{
}

//! @brief Déstructeur pour la classe Texture.
cirion::Texture::~Texture()
{
    if( mTexture != NULL )
    {
        ostringstream oss;

        SDL_DestroyTexture( mTexture );

        oss << "Texture \""
            << ( mName == NULL ? "" : mName )
            << "\" freed.";

        log( oss.str().c_str(), __PRETTY_FUNCTION__ );
        mTexture = NULL;
    }
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de création d'une texture à partir d'une surface.
//! @param surface La surface source.
//! @throw CiException
void cirion::Texture::create( Surface* surface )
{
    // --- SDL2 est-elle initialisée ? -----------------------------------------
    if ( !(SDL_WasInit(0) & SDL_INIT_VIDEO) )
    {
        throw CiException(
            "Texture creation failed: SDL2 video was not initialized.",
            __PRETTY_FUNCTION__
        );
    }

    // --- Destruction de l'ancienne texture, si elle existe. ------------------
    if( mTexture != NULL ){
        
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
    }

    // --- Création de la texture à partir de la surface. ----------------------
    mTexture = SDL_CreateTextureFromSurface( gRenderer,
                                             surface->getSdl2Surface() );
    
    if( mTexture == NULL )
    {
        ostringstream oss;

        oss << "Texture creation from surface failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    log( (char*)"New texture created from surface.", __PRETTY_FUNCTION__ );
}

//! @brief Procédure de création d'une texture à partir d'un bitmap.
//! @param name Le nom de la texture dans le répertoire des textures.
//! @throw CiException
void cirion::Texture::create( const char* name )
{
    Surface surface; //! La surface crée à partir du fichier.

    // --- SDL2 est-elle initialisée ? -----------------------------------------
    if ( !(SDL_WasInit(0) & SDL_INIT_VIDEO) )
    {
        throw CiException(
            "Texture creation failed: SDL2 video was not initialized.",
            __PRETTY_FUNCTION__
        );
    }

    // --- Destruction de l'ancienne texture, si elle existe. ------------------
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
    }

    // --- Création d'une surface depuis un bitmap. ----------------------------
    try
    {
        ostringstream filepath;

        filepath << gWorkingDir
                 << "/Textures/"
                 << name
                 << ".bmp";

        surface.create( filepath.str().c_str() );
    }

    catch( CiException const& e )
    {
        log( e );

        throw CiException( "Unable to processing texture creation.",
            __PRETTY_FUNCTION__ );
    }

    // --- Création de la texture. ---------------------------------------------
    mTexture = SDL_CreateTextureFromSurface( gRenderer,
                                             surface.getSdl2Surface() );

    if( mTexture == NULL )
    { 
        ostringstream oss; //!< Un flux de chaîne

        oss << "Texture creation from surface failed: \""
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    setName( name );

    log( (char*)"New texture created from surface.", __PRETTY_FUNCTION__ );
}

//! @brief Procédure de définition du mode de simulation de la transparence.
//! @param mode Le mode de simulation de la transparence.
//! @throw CiException
void cirion::Texture::setBlendMode( SDL_BlendMode mode )
{
    if( SDL_SetTextureBlendMode( mTexture, mode ) != 0 )
    {
        ostringstream oss;

        oss << "Unable to set sufrace blend mode:"
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }
}

//! @brief Procédure d'application de la modulation alpha.
//! @param alpha Quantité de transparence.
//! @throw CiException
void cirion::Texture::setAlphaMod( Uint8 alpha )
{
    if( SDL_SetTextureAlphaMod( mTexture, alpha ) != 0 )
    {
        ostringstream oss;

        oss << "Unable to set sufrace alpha modulation:"
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }
}

//! @brief Procédure d'application de la modulation RVB.
//! @param red Quantité de rouge.
//! @param green Quantité de vert.
//! @param blue Quantité de bleu.
//! @throw CiException
void cirion::Texture::setRgbMod( Uint8 red, Uint8 green, Uint8 blue )
{
    if( SDL_SetTextureColorMod( mTexture, red, green, blue ) != 0 )
    {
        ostringstream oss;

        oss << "Unable to set sufrace color modulation:"
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }
}

//! @brief Procédure d'attribution d'un nom à la texture.
//! @param name Le nouveau nom de la texture.
void cirion::Texture::setName( const char* name )
{
    mName = (char*)name;
}

//! @brief Fonction accesseur.
//! @return Le nom de la texture.
const char* cirion::Texture::getName()
{
    return mName;
}

//! @brief Fonction accesseur.
//! @return Pointeur vers une structure de texture définie par SDL2.
SDL_Texture* cirion::Texture::getSdl2Texture()
{
    return mTexture;
}

//! @brief Fonction accesseur.
//! @return La largeur de la texture, en pixels.
int cirion::Texture::getWidth()
{
    int width; //!< La largeur récupérée depuis la structure de texture.
    
    SDL_QueryTexture( mTexture, NULL, NULL, &width, NULL );
    return width;
}

//! @brief Fonction accesseur.
//! @return La hauteur de la texture, en pixels.
int cirion::Texture::getHeight()
{
    int height; //!< La hauteur récupérée depuis la structure de texture.
    
    SDL_QueryTexture( mTexture, NULL, NULL, NULL, &height );
    return height;
}
