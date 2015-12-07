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
 * @version 0.1.7
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    06 Novembre 2015
 * @brief   Cirion Engine.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <Cirion/bubble.hpp>
#include <Cirion/ciexception.hpp>
#include <Cirion/cirion.hpp>
#include <Cirion/cmf.hpp>
#include <Cirion/config.hpp>
#include <Cirion/log.hpp>
#include <Cirion/object.hpp>
#include <Cirion/graphic.hpp>
#include <Cirion/surface.hpp>
#include <Cirion/texture.hpp>
#include <Cirion/timer.hpp>
#include <Cirion/world.hpp>
#include <Cirion/xmlerror.hpp>

using namespace std;
using namespace cirion;

bool             gRunning;             //!< Drapeau de mise en route
Config           gConfig;              //!< La configuration du moteur
char*            gWorkingDir;          //!< Chemin des ressources du jeu
int              gTimeStep;            //!< Le délai entre chaque nouvelle image.
SDL_Window*      gWindow      = NULL;  //!< Fenêtre SDL2
SDL_Renderer*    gRenderer    = NULL;  //!< Renderer SDL2
SDL_Event        gEvent;               //!< Evenements SDL2
vector<Texture*> gTextures;            //!< Vecteur de textures
vector<Object*>  gObjects;             //!< Vecteur d'objets à traîter
World            gWorld;               //!< Le monde

//! @brief Procédure d'initialisation du moteur.
//! @throw CiException
void cirion::init()
{
    ostringstream oss;
    int           windowWidth;  //!< La largeur de la fenêtre
    int           windowHeight; //!< La hauteur de la fenêtre
    Uint32        windowFlags;  //!< Les paramètres de la fenêtre

    oss << "Initializing Cirion Engine v"
        << CIRION_VERSION;

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    // --- Chargement de la configuration. -------------------------------------
    try
    {
        gConfig.load( (char*)"./Config.xml" );
    }

    catch( CiException const& e )
    {
        log( e );
    }

    /* Préconfiguration de la fenêtre SDL2 ... */
    if( gConfig.isFullscreen() )
    {
        /*  ... en mode plein-écran. */
        windowWidth  = gConfig.getFullscreenWidth();
        windowHeight = gConfig.getFullscreenHeight();
        windowFlags  = SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN;
    }

    else
    {
        /* ... en mode fenêtré. */
        windowWidth  = gConfig.getWindowWidth();
        windowHeight = gConfig.getWindowHeight();
        windowFlags  = SDL_WINDOW_HIDDEN;
    }

    // --- Initialisation de la lib. SDL2. -------------------------------------
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
        oss.str("");

        oss << "SDL2 initialization failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Création de la fenêtre SDL2. ----------------------------------------
    gWindow = SDL_CreateWindow( "SDL2",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                windowWidth,
                                windowHeight,
                                windowFlags );

    if( gWindow == NULL )
    {
        oss.str("");
        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Création du renderer. -----------------------------------------------
    gRenderer = SDL_CreateRenderer( gWindow, -1, 0 );
    cout << SDL_GetError() << endl << endl;

    if ( gRenderer == NULL )
    {
        oss.str("");

        oss << "SDL2 renderer creation failed: "
            << SDL_GetError();

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    SDL_RenderSetLogicalSize( gRenderer, RENDERER_WIDTH, RENDERER_HEIGHT );

    // --- Affichage de la fenêtre, nettoyage et actualisation du renderer. ----
    SDL_ShowWindow( gWindow );
    SDL_RenderClear( gRenderer );
    SDL_RenderPresent( gRenderer );

    // --- Go, go, go ! --------------------------------------------------------
    gRunning = true;
}

//! @brief
//! @param
void cirion::setWorkingDir( char* path )
{
    gWorkingDir = path;
}

//! @brief Procédure de gestion d'un évenement principal.
void cirion::handleEvents()
{
    /* Parcours de la liste des évenements en attentes */
    while( SDL_PollEvent( &gEvent ) )
    {
        switch( gEvent.type )
        {
            case SDL_QUIT:
            gRunning = false;
            break;

            case SDL_KEYDOWN: 
            switch( gEvent.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                gRunning = false;
                break;
            }

            break;
        }

        /* Traitement de l'évenement pour le monde */
        gWorld.handleEvent();

        /* Parcours de la liste des objets */
        for( size_t i = 0; i != gObjects.size(); i++ )
        {
            /* Traîtement de l'évenement pour l'objet */
            gObjects[i]->handleEvent(); 
        }
    }
}

void cirion::update()
{
    /* Mise à jour du monde */
    gWorld.update();

    /* Parcours de la lite des objets */
    for( size_t i = 0; i != gObjects.size(); i++ )
    {
        gObjects[i]->update();
    }
}

void cirion::render()
{
    /* Nettoyage du renderer */
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );

    /* Dessin du monde */
    gWorld.draw();

    /* Parcours de la liste des objets */
    for( size_t i = 0; i != gObjects.size(); i++ )
    {
        /* Dessin de l'objet */
        gObjects[i]->draw();
    }

    /* Actualisation du renderer */
    SDL_RenderPresent( gRenderer );
}

//! @brief Procédure de boucle principale.
void cirion::run()
{
    int previousTime;
    int currentTime( SDL_GetTicks() );
    int delay;

    log( (const char*)"Entering main loop.", __PRETTY_FUNCTION__ );

    // --- Boucle principale. --------------------------------------------------
    while( gRunning )
    {
    	previousTime = currentTime;
    	currentTime  = SDL_GetTicks();
    	gTimeStep    = currentTime - previousTime;

        handleEvents();
        update();
        render();

        delay = 1000 / gConfig.getFramerate() - (SDL_GetTicks() - currentTime);

        delay = delay < 0
              ? 0
              : delay;

        SDL_Delay( delay );
    }
}

//! @brief Procédure de sortie.
void cirion::quit()
{
    log( (const char*)"Exiting cirion ...", __PRETTY_FUNCTION__ );

    // --- Liberation des éléments du vecteur d'objets. ------------------------
    for( size_t i = 0; i != gObjects.size(); i++ )  { delete gObjects[i];  }
    gObjects.clear();

    // --- Liberation des éléments du vecteur de textures. ---------------------
    for( size_t i = 0; i != gTextures.size(); i++ ) { delete gTextures[i]; }
    gTextures.clear();

    /* Liberations  */
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    SDL_Quit();
}
