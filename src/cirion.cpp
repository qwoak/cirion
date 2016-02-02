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
 * @file    cirion.cpp
 * @version 0.2.3.2
 * @author  Jérémy S. "Qwoak"
 * @date    14 Janvier 2016
 * @brief   Coeur du moteur
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/config.hpp>
#include <Cirion/gameobject.hpp>
#include <Cirion/log.hpp>
#include <Cirion/texture.hpp>
#include <Cirion/timer.hpp>
#include <Cirion/world.hpp>

using namespace std;
using namespace cirion;

const char* gVersion = "0.3.1";
const char* gWorkingDir = "./Data";
const int gRendererWidth = 320;
const int gRendererHeight = 240;
Config gConfig;
bool gIsRunning;
Timer gRenderTimer;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Event gEvent;
vector<Texture*> gTextures;
vector<GameObject*> gGameObjects;
World gWorld;

//! @brief Procédure d'initialisation du moteur.
//! @throw CiException en cas d'échec.
void cirion::init()
{
    ostringstream oss;
    Uint32 windowFlags;
    Uint32 rendererFlags;

    oss << "Initializing Cirion Engine v"
        << gVersion;

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    // --- Chargement de la configuration. -------------------------------------
    try
    {
        gConfig.load( (const char*)"./Config.xml" );
    }

    catch( CiException const& e )
    {
        log( e );
    }

    // --- Initialisation de la lib. SDL2. -------------------------------------
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        oss.str("");

        oss << "SDL2 initialization failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Création de la fenêtre SDL2. ----------------------------------------
    
    windowFlags  = SDL_WINDOW_HIDDEN; 
    windowFlags |= gConfig.mIsFullscreen
                 ? SDL_WINDOW_FULLSCREEN_DESKTOP
                 : 0;

    gWindow = SDL_CreateWindow( "SDL2",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                gConfig.mWindowWidth,
                                gConfig.mWindowHeight,
                                windowFlags );

    if( gWindow == NULL )
    {
        oss.str("");

        oss << "Window creation failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Création du renderer. -----------------------------------------------
    
    rendererFlags  = 0;
    rendererFlags |= gConfig.mIsHwRenderEnabled
                   ? SDL_RENDERER_ACCELERATED
                   : 0;
    rendererFlags |= gConfig.mIsVsyncEnabled
                   ? SDL_RENDERER_PRESENTVSYNC
                   : 0;

    gRenderer = SDL_CreateRenderer( gWindow, -1, rendererFlags );

    if ( gRenderer == NULL )
    {
        oss.str("");

        oss << "SDL2 renderer creation failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    SDL_RenderSetLogicalSize( gRenderer,
                              gRendererWidth,
                              gRendererHeight );

    // --- Affichage de la fenêtre, nettoyage et actualisation du renderer. ----
    SDL_ShowWindow( gWindow );
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );
    SDL_RenderPresent( gRenderer );
}

//! @brief Procédure de traîtement des évenements.
void cirion::handleEvents()
{
    // Parcours de la liste des évenements en attentes
    while( SDL_PollEvent( &gEvent ) )
    {
        switch( gEvent.type )
        {
            case SDL_QUIT:
            gIsRunning = false;
            break;

            case SDL_KEYDOWN: 
            switch( gEvent.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                gIsRunning = false;
                break;
            }

            break;
        }

        // Traitement de l'évenement dans le monde
        gWorld.handleEvent( &gEvent );

        // Parcours de la liste des objets
        for( size_t i = 0; i != gGameObjects.size(); i++ )
        {
            // Traîtement de l'évenement dans l'objet
            gGameObjects[i]->handleEvent( &gEvent ); 
        }
    }
}

//! @brief Procédure de mise à jour des composantes du moteur.
void cirion::update( int timeStep )
{
    // Mise à jour du monde
    gWorld.update( timeStep );

    // Parcours de la lise des objets
    for( size_t i = 0; i != gGameObjects.size(); i++ )
    {
        // Mise à jour de l'objet
        gGameObjects[i]->update( timeStep );
    }
}

//! @brief Procédure de rendu.
void cirion::render()
{
    // Nettoyage du renderer
    SDL_RenderClear( gRenderer );

    // Dessin du monde
    gWorld.draw();

    // Parcours de la liste des objets
    for( size_t i = 0; i != gGameObjects.size(); i++ )
    {
        // Dessin de l'objet
        gGameObjects[i]->draw();
    }

    // Actualisation du renderer
    SDL_RenderPresent( gRenderer );
}

//! @brief Procédure de boucle principale.
void cirion::run()
{
    log( (const char*)"Entering main loop.", __PRETTY_FUNCTION__ );
    gIsRunning = true;
    gRenderTimer.start();

    // --- Boucle principale. --------------------------------------------------
    while( gIsRunning)
    {
        handleEvents();
        update( gRenderTimer.getTicks() );
        //cout << gRenderTimer.getTicks() << endl;
        gRenderTimer.reset();
        render();
        //SDL_Delay( 1 );
    }
}

//! @brief Procédure d'arrêt du moteur.
void cirion::quit()
{
    log( (const char*)"Exiting cirion ...", __PRETTY_FUNCTION__ );

    // Liberation des objets
    for( size_t i = 0; i != gGameObjects.size(); i++ )
    {
        delete gGameObjects[i];
    }

    gGameObjects.clear();

    // Liberation des textures
    for( size_t i = 0; i != gTextures.size(); i++ )
    {
        delete gTextures[i];
    }

    gTextures.clear();

    // Liberation des ressources de la lib. SDL2.
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    SDL_Quit();
}
