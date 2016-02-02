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
 * @version 0.1.1.3
 * @author  Jérémy S. "Qwoak" 
 * @date    13 Janvier 2016
 * @brief   Crimson Map Format
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
     * Une classe pour manipuler le format de fichier de map Crimson.
     */
    class Cmf
    {
    public:
        Cmf();
        ~Cmf();
        void load( const char* name, bool testChecksum = true );
        void write( const char* filepath, bool overwrite = false );
        void clear();
        void setTile( int x, int y, unsigned char data );
        void setWidth( int width );
        void setHeight( int height );
        char* getBackgroundName();
        char* getTilesetName();
        unsigned char getTile( int x, int  );
        int getWidth();
        int getHeight();

    private:
        unsigned int computeChecksum( std::fstream* stream );

        /** L'octet magique */
        unsigned int mMagic;
        /** Le checksum */
        unsigned int mChecksum;
        /** La largeur de la map, en nombre de tuiles */
        int mWidth;
        /** La heuteur de la map, en nombre de tuiles */
        int mHeight;
        /** Le nom de la texture du background */
        char mBackground[16];
        /** Le nom de la texture du tileset */
        char mTileset[16];
        /** Le vecteur de l'index des tuiles */
        std::vector< std::vector<unsigned char> > mTiles;
    };
}

#endif
