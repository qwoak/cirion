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
 * @version 0.2.1.2
 * @author  Jérémy S. "Qwoak"
 * @date    19 Janvier 2016
 * @brief   Manipulation des surfaces.
 */

#include <iostream>
#include <sstream>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/log.hpp>
#include <Cirion/surface.hpp> // R_MASK, G_MASK, B_MASK, A_MASK

using namespace std;

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
//! @throw CiException en cas d'échec.
void cirion::Surface::create( int width, int height )
{
    //! Un flux de chaîne pour le journal.
    ostringstream oss;
    //! La nouvelle surface crée.
    SDL_Surface*  surface = NULL;

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

    // --- Création d'une nouvelle surface. ------------------------------------
    surface = SDL_CreateRGBSurface( 0, width, height, 32, R_MASK, G_MASK,
        B_MASK, A_MASK );

    if ( surface == NULL )
    {
        oss << "Surface creation failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Définition de la couleur clé pour la transparence. ------------------
    SDL_SetColorKey( surface, SDL_TRUE, 0x00000000 );

    oss << "New "
        #ifdef DEBUG
        << surface->w
        << "x"
        << surface->h
        << " px "
        << SDL_GetPixelFormatName( surface->format->format )
        << " "
        #endif // DEBUG
        << "surface created.";

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );
    mSurface = surface;
}

//! @brief Procédure de création d'une surface optimisée à partir d'un bitmap.
//! @param filepath Chemin vers le fichier bitmap.
//! @throw CiException en cas d'échec.
void cirion::Surface::create( const char* filepath )
{
    //! Un flux de chaîne pour le journal.
    ostringstream oss;
    //! La surface crée à partir du fichier.
    SDL_Surface*  surface           = NULL;
    //! Le format des pixels de la surface convertie.
    Uint32        pixelFormat;
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
    pixelFormat = SDL_MasksToPixelFormatEnum( 32, R_MASK, G_MASK, B_MASK,
        A_MASK );

    optimized_surface = SDL_ConvertSurfaceFormat( surface, pixelFormat, 0 );

    if( optimized_surface == NULL )
    {
        oss << "Surface optimization failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    oss << "New "
        #ifdef DEBUG
        << optimized_surface->w
        << "x"
        << optimized_surface->h
        << " px "
        << SDL_GetPixelFormatName( optimized_surface->format->format )
        << " "
        #endif // DEBUG
        << "surface created from \""
        << filepath
        << "\".";

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    // --- Définition de la couleur clé pour la transparence. ------------------
    SDL_SetColorKey( optimized_surface, SDL_TRUE, 0x00000000 );

    mSurface = optimized_surface;
}

//! @brief Procédure de définition du mode de simulation de la transparence.
//! @param mode Le mode de simulation de la transparence.
//! @throw CiException en cas d'échec.
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
//! @throw CiException en cas d'échec.
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
//! @throw CiException en cas d'échec.
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
