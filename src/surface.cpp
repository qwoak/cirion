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
 * @file    surface.cpp
 * @version 0.2
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Manipulation des surfaces.
 */

#include <iostream>
#include <sstream>
#include <Cirion/ciexception.hpp>
#include <Cirion/log.hpp>
#include <Cirion/surface.hpp>

using namespace std;

extern SDL_Window* gWindow; //!< cf cirion.cpp

/* +------------------------------------------------------------------------+
   ! Définition des constructeurs / déstructeurs.                           !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Surface.
cirion::Surface::Surface()
{
    mSurface = NULL;
}

//! @brief Déstructeur pour la classe Surface.
cirion::Surface::~Surface()
{
    if( mSurface != NULL )
    {
        SDL_FreeSurface( mSurface );

        log( (char*)"Surface freed.", __PRETTY_FUNCTION__ );
        mSurface = NULL;
    }
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes.                                              !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de création d'une surface vide.
//! @param width Largeur de la nouvelle surface en pixels.
//! @param height Hauteur de la nouvelle surface en pixels.
//! @throw CiException
void cirion::Surface::create( int width, int height )
{
    //! Un flux de chaîne pour le journal.
    ostringstream oss;
    //! La nouvelle surface crée.
    SDL_Surface*  surface = NULL;
    //! Le format d'affichage actuel pour l'optimisation.
    Uint8         bitsPerPixels;
    //! Le masque RGBA.
    Uint32        rmask,
                  gmask,
                  bmask,
                  amask;

    // --- SDL2 est-elle initialisée ? -----------------------------------------
    if ( !(SDL_WasInit(0) & SDL_INIT_VIDEO) )
    {
        throw CiException(
            "Surface creation failed: SDL2 video was not initialized.",
            __PRETTY_FUNCTION__
        );
    }

    // --- Définition du masque ------------------------------------------------
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    // --- Libération de l'ancienne surface, si elle existe. -------------------
    if( mSurface != NULL )
    {
        SDL_FreeSurface( mSurface );
    }

    // --- Récuperation du format d'affichage. ---------------------------------
    bitsPerPixels = SDL_GetWindowSurface( gWindow )->format->BitsPerPixel;

    // --- Création d'une nouvelle surface optimisée. --------------------------
    surface = SDL_CreateRGBSurface( 0, width, height, bitsPerPixels, rmask,
        gmask, bmask, amask );

    if ( surface == NULL )
    {
        oss << "Surface creation failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    oss << "New "
        << surface->w
        << "*"
        << surface->h
        << " @ "
        << (unsigned int)surface->format->BitsPerPixel
        << "bpp surface created.";

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );
    mSurface = surface;
}

//! @brief Procédure de création d'une surface optimisée à partir d'un bitmap.
//! @param filepath Chemin vers le fichier bitmap.
//! @throw CiException
void cirion::Surface::create( const char* filepath )
{
    //! Un flux de chaîne pour le journal.
    ostringstream oss;
    //! La surface crée à partir du fichier.
    SDL_Surface*  surface           = NULL;
    //! La surface optimisée pour le format d'affichage courrant.
    SDL_Surface*  optimized_surface = NULL;

    // --- SDL2 est-elle initialisée ? -----------------------------------------
    if ( !(SDL_WasInit(0) & SDL_INIT_VIDEO) )
    {
        throw CiException(
            "Surface creation failed: SDL2 video was not initialized.",
            __PRETTY_FUNCTION__
        );
    }

    // --- Libération de l'ancienne surface, si elle existe. -------------------
    if( mSurface != NULL )
    {
        SDL_FreeSurface( mSurface );
    }

    // --- Création d'une surface à partir d'un bitmap. ------------------------
    surface = SDL_LoadBMP( filepath );

    if( surface == NULL )
    {
        oss << "Surface creation from bitmap failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Création d'une surface optimisée. -----------------------------------
    optimized_surface = SDL_ConvertSurface(

        surface,
        SDL_GetWindowSurface( gWindow )->format,
        0
    );

    if( optimized_surface == NULL )
    {
        oss << "Surface optimization failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    oss << "New "
        << optimized_surface->w
        << "*"
        << optimized_surface->h
        << "px @ "
        << (unsigned int)optimized_surface->format->BitsPerPixel
        << "bpp surface created from \""
        << filepath
        << "\".";

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    // --- Définition de la couleur clé pour la transparence. ------------------
    SDL_SetColorKey( optimized_surface, SDL_TRUE, 0x00000000 );

    mSurface = optimized_surface;
}

//! @brief Procédure de définition du mode de simulation de la transparence.
//! @param mode Le mode de simulation de la transparence.
//! @throw CiException
void cirion::Surface::setBlendMode( SDL_BlendMode mode )
{
    if( SDL_SetSurfaceBlendMode( mSurface, mode ) != 0 )
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
void cirion::Surface::setAlphaMod( Uint8 alpha )
{
    if( SDL_SetSurfaceAlphaMod( mSurface, alpha ) != 0 )
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
void cirion::Surface::setRgbMod( Uint8 red, Uint8 green, Uint8 blue )
{
    if( SDL_SetSurfaceColorMod( mSurface, red, green, blue ) != 0 )
    {
        ostringstream oss;

        oss << "Unable to set sufrace color modulation:"
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }
}

//! @brief Fonction accesseur.
//! @return Pointeur vers une structure de surface SDL2.
SDL_Surface* cirion::Surface::getSdl2Surface()
{
    return mSurface;
}

//! @brief Fonction accesseur.
//! @return La largeur de la surface, en pixels.
int cirion::Surface::getWidth()
{
    return mSurface->w;
}

//! @brief Fonction accesseur.
//! @return La hauteur de la surface, en pixels.
int cirion::Surface::getHeight()
{
    return mSurface->h;
}
