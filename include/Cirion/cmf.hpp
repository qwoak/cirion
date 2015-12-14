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
 * @file    cmf.hpp
 * @version 0.1.1.2
 * @author  Jérémy S. "Qwoak" <qwoak11 at gmail dot com>
 * @date    01 Novembre 2015
 * @brief   Cirion Map Format
 */

#ifndef CMF_HPP
#define CMF_HPP

#include <fstream>
#include <vector>

namespace cirion
{
    /**
     * @class Cmf cmf.hpp
     *
     * Une classe pour manipuler le format de fichier de map Cirion.
     */
    class Cmf
    {
        public:
        /* +------------------------------------------------------------+
           ! Déclaration des constructeurs / déstructeurs.              !
           +------------------------------------------------------------+ */
        Cmf();
        ~Cmf();
        /* +------------------------------------------------------------+
           ! Déclaration des méthodes publiques.                        !
           +------------------------------------------------------------+ */
        void load( const char* name, bool testChecksum = true );
        void save( const char* filepath, bool overwrite = false );
        void clear();
        void setTile( int x, int y, unsigned char data );
        void setWidth( size_t width );
        void setHeight( size_t height );
        char* getBackgroundName();
        char* getTilesetName();
        unsigned char getTile( size_t i, size_t j );
        size_t getWidth();
        size_t getHeight();

        private:
        /* +------------------------------------------------------------+
           ! Déclaration des méthodes privées.                          !
           +------------------------------------------------------------+ */
        unsigned int computeChecksum( std::fstream* stream );
        /* +------------------------------------------------------------+
           ! Déclaration des attributs.                                 !
           +------------------------------------------------------------+ */
        unsigned int mMagic;    //!< L'octet magique
        unsigned int mChecksum; //!< Le checksum
        size_t mWidth;          //!< La largeur de la map en nombre de tuiles
        size_t mHeight;         //!< La hauteur de la map en nombre de tuiles
        char mBackground[16];   //!< Le nom de la texture de fond
        char mTileset[16];      //!< Le nom de la texture du tileset
        std::vector< std::vector<unsigned char> > mTiles; //!< Données.
    };
}

#endif
