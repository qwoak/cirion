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
 * @version 0.5
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    27 Novembre 2015
 * @brief   Manipulation des textures.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring> // memcpy()
#include <Cirion/ciexception.hpp>
#include <Cirion/log.hpp>
#include <Cirion/surface.hpp>
#include <Cirion/texture.hpp>

using namespace std;
using namespace cirion;

extern char*         gWorkingDir; //!< cf cirion.cpp
extern SDL_Window*   gWindow;     //!< cf cirion.cpp
extern SDL_Renderer* gRenderer;   //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Texture.
cirion::Texture::Texture():
    mName   (NULL),
    mTexture(NULL),
    mPixels (NULL),
    mPitch  (0)
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
   ! Définitions des méthodes publiques.                                    !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de création d'une texture.
//! @param *surface La surface source.
//! @throw CiException en cas d'échec.
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
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
    }

    // --- Création d'une texture streamable à partir de la surface. -----------
    mTexture = SDL_CreateTexture( gRenderer,
                                  surface->getSdl2Surface()->format->format,
                                  SDL_TEXTUREACCESS_STREAMING,
                                  surface->getSdl2Surface()->w,
                                  surface->getSdl2Surface()->h );

    if( mTexture == NULL )
    {
        ostringstream oss;

        oss << "Texture creation from surface failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Verouillage de la texture pour manipulations. -----------------------
    try
    { 
        lock();
    }

    catch( CiException const& e )
    {
        log( e );
    }

    // --- Copie des pixels de la surface dans la texture. ---------------------
    memcpy( mPixels, 
            surface->getSdl2Surface()->pixels, 
            surface->getSdl2Surface()->pitch * 
            surface->getSdl2Surface()->h );

    // --- Application du pixel transparent. -----------------------------------

    /* Le pointeur vers les données des pixels vérouilés en écriture. */
    Uint32* pixels = (Uint32*)mPixels;

    /* Le nombre de pixels de la texture: c'est le nombre d'octet dans une ligne
    divisé par le nombre d'octet dans un pixels multiplié par la hauteur de la
    texture. */
    size_t pixelCount = mPitch / 4 * this->getHeight();

    /* Le color key corespond à la couleur à remplacer par le pixel
    transparent. */
    Uint32 colorKey = SDL_MapRGBA(
        surface->getSdl2Surface()->format, // Format des pixels de la surface.
        0x00,                              // Quantité de rouge.
        0x00,                              // Quantité de vert.
        0x00,                              // Quantité de bleu.
        0xFF                               // Quantité alpha.
    );

    /* Le pixel transparent */
    Uint32 transparent = SDL_MapRGBA(
        surface->getSdl2Surface()->format, // Format des pixels de la surface.
        0x00,                              // Quantité de rouge.
        0x00,                              // Quantité de vert.
        0x00,                              // Quantité de bleu.
        0x00                               // Quantité alpha.
    );

    // Parcours des pixels de la texture.
    for( size_t i = 0; i != pixelCount; i++ )
    {
        // Si le pixel correspond au color key, ...
        if( pixels[i] == colorKey )
        {
            // ... remplacement du pixel.
            pixels[i] = transparent;
        }
    }

    // --- Déverouillage de la texture. ----------------------------------------
    unlock();
    setBlendMode( SDL_BLENDMODE_BLEND );

    log( (char*)"New texture created from surface.", __PRETTY_FUNCTION__ );
}

//! @brief Procédure de création d'une texture.
//! @param Le nom de la texture dans le répertoire des textures.
//! @throw CiException en cas d'échec.
void cirion::Texture::create( const char* name )
{
    ostringstream filepath; //!< Le chemin du bitmap.
    Surface       surface;  //!< La surface chargée avec le bitmap.

    // --- Construction du chemin du bitmap. -----------------------------------
    filepath << gWorkingDir
             << "/Textures/"
             << name
             << ".bmp";

    // --- Création de la surface à partir du bitmap. --------------------------
    try
    {
        surface.create( filepath.str().c_str() );
    }

    catch( CiException const& e )
    {
        log( e );

        throw CiException( "Unable to process texture creation.",
            __PRETTY_FUNCTION__ );
    }

    // --- Création de la texture à partir de la surface. ----------------------
    try
    {
        create( &surface );
    }

    catch( CiException const& e )
    {
        throw e;
    }

    // --- Définition du nom de la texture. ------------------------------------
    setName( name );
}

//! @brief Procédure de vérouillage de la texture pour l'accès en écriture.
//! @throw CiException en cas d'échec.
void cirion::Texture::lock()
{
    if( mPixels != NULL )
    {
        ostringstream oss;

        oss << "Texture \""
            << mName
            << "\" is already locked !";

        log( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    else
    {
        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
        {
            ostringstream oss;

            oss << "Unable to lock texture \""
                << mName
                << "\":"
                << SDL_GetError();

            throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
        }
    }
}

//! @breif Procédure de dévérouillage de la texture.
//! @throw CiException en cas d'échec.
void cirion::Texture::unlock()
{
    if( mPixels == NULL )
    {
        ostringstream oss;

        oss << "Texture \""
            << mName
            << "\" is already unlocked !";

        log( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    else
    {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }
}

//! @brief Procédure de définition du mode de simulation de la transparence.
//! @param mode Le mode de simulation de la transparence.
//! @throw CiException en cas d'échec.
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
//! @throw CiException en cas d'échec.
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
//! @throw CiException en cas d'échec.
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

//! @brief Fonction accesseur.
//! @return Pointeur vers les pixels vérouillés de la texture.
void* cirion::Texture::getPixels()
{
    return mPixels; 
}

//! @brief Fonction accesseur.
//! @return La longueur en octet d'une rangée de pixels vérouillés.
int cirion::Texture::getPitch()
{
    return mPitch;
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes privées.                                      !
   +------------------------------------------------------------------------+ */

//! @brief Procédure d'attribution d'un nom à la texture.
//! @param name Le nouveau nom de la texture.
void cirion::Texture::setName( const char* name )
{
    mName = (char*)name;
}
