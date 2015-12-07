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
 * @author  Jérémy S. "Qwoak" <qwoak11@gmail.com>
 * @date    08 Novembre 2015
 * @brief   Cirion Map Format
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include <Cirion/ciexception.hpp>
#include <Cirion/cmf.hpp>
#include <Cirion/log.hpp>

using namespace std;
using namespace cirion;

extern char* gWorkingDir; //!< cf cirion.cpp
 
/* +------------------------------------------------------------------------+
   ! Définitions des constructeurs / déstructeurs.                          !
   +------------------------------------------------------------------------+ */

//! @brief Constructeur pour la classe Cmf.
cirion::Cmf::Cmf()
{
    mMagic      = 0;
    mChecksum   = 0;
    mWidth      = 0;
    mHeight     = 0;

    memset( mBackground, 0x00, 16 );
    memset( mTileset,    0x00, 16 );
}

//! @brief Déstructeur pour la classe Cmf.
cirion::Cmf::~Cmf()
{
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes privées.                                      !
   +------------------------------------------------------------------------+ */

//! @brief Fonction de calcul de la somme de contrôle d'un fichier CMF.
//! @param file Flux vers le fichier.
//! @return La somme de contrôle calculée.
unsigned int cirion::Cmf::computeChecksum( fstream* file )
{
    /* L'algorithme suivant est basé sur le code de Reed-Solomon.
    Le but est de s'assurer que l'utilisateur ne fasse pas n'importe quoi
    et de vérifier l'intégrité du fichier.*/

    unsigned char byte;     //!< L'octet lu dans le fichier
    unsigned int  checksum; //!< Notre somme de contrôle
    
    /* La somme de contrôle est une valeur 32-bits obtenue par la combinaison
    de ces deux variables 16-bits: */

    unsigned short sum = 0;  //!< Somme de tous les octets
    unsigned short wsum = 0; //!< Somme pondérée de tous les octets

    /* Nous aurons également besoin de cette variable pour la pondération: */
    unsigned long count = 0; //!< Le nombre d'octet parcouru

    /* On place le curseur à la position 0x08, juste après les quatres octets
    magiques et les quatres octets de la somme de contrôle. */
    file->clear();
    file->seekg( 0x08 );

    /* On lit chaques octets à partir desquels nous allons mettre à jour la
    somme et la somme pondérée.*/
    while( !file->eof() )
    {
        file->read( (char*)&byte, sizeof(char) );
        count   ++;
        sum     += byte;
        wsum    += byte * count;
    }

    /* On combine ensuite les deux valeurs pour obtenir la somme de contrôle. */
    checksum = ( (unsigned int)(sum) << 16 )
             + wsum;

    #ifdef DEBUG

        ostringstream oss;

        oss << "Computed CMF checksum: 0x"
            << hex << setfill('0') << setw(8) << checksum;

        log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    #endif // DEBUG

    return checksum;
}

/* +------------------------------------------------------------------------+
   ! Définitions des méthodes publiques.                                    !
   +------------------------------------------------------------------------+ */

//! @brief Procédure de chargement d'un fichier CMF.
//! @param filepath Chemin vers le fichier.
//! @param test_checksum Indique si il faut vérifier la somme de contrôle.
//! @throw CiException
void cirion::Cmf::load( const char* name, bool testChecksum )
{
    ostringstream   oss;      //!< Un flux de chaîne pour le journal
    ostringstream   filepath; //!< Le chemin du fichier CMF
    fstream         file;     //!< Un flux de fichier
    unsigned char   buffer;   //!< Donnée singulière lue depuis le fichier

    oss << "Loading CMF \"" 
        << name
        << "\" ...";

    log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    // --- Construction du chemin du fichier. ----------------------------------
    filepath << gWorkingDir
             << "/Cmfs/"
             << name
             << ".cmf";

    // --- Ouverture du fichier. -----------------------------------------------
    file.open( filepath.str().c_str(), ios::binary | ios::in );

    if( !file.is_open() )
    {
        oss.str("");

        oss << "Unable to load CMF file \""
            << filepath.str()
            << "\": file not found.";

        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Lecture et test de l'octet magique. ---------------------------------
    file.read( (char*)&mMagic, sizeof(int) );

    if( mMagic != 0x00464D43 )
    {
        oss.str("");

        oss << "Unable to load CMF file \""
            << filepath.str()
            << "\": Wrong magic.";

        mMagic = 0;
        file.close();
        throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
    }

    // --- Lecture [et vérification] du checksum. ------------------------------
    file.read( (char*)&mChecksum, sizeof(int) );

    if( testChecksum )
    {
        unsigned int computed_checksum = computeChecksum( &file );

        /* Comparaison de la somme de contrôle calculée avec celle stockée dans
        le fichier. Si la valeur est différente: */
        if( computed_checksum != mChecksum )
        {
            oss.str("");

            file.close();

            oss << "Unable to load CMF file \""
                << filepath.str()
                << "\": Bad checksum.";

            throw CiException( oss.str().c_str(), __PRETTY_FUNCTION__ );
        }

        /* Ràz des flags (eof) et repositionnement du curseur pour la suite du
        chargement. */
        file.clear();
        file.seekg( 0x08 );
    }

    // --- Lecture du reste du header CMF. -------------------------------------
    file.read( (char*)&mWidth,  sizeof(int) );
    file.read( (char*)&mHeight, sizeof(int) );
    file.read( mBackground, 16 * sizeof(char) );
    file.read( mTileset,    16 * sizeof(char) );

    // --- Redimensionnement des vecteurs et lecture des entrées des tuiles. ---
    mTiles.resize( mHeight );

    for( size_t i = 0; i != mTiles.size(); i++ )
    {
        mTiles[i].resize( mWidth );

        for( size_t j = 0; j != mWidth; j++ )
        {
            file.read( (char*)&buffer, sizeof(char) );
            mTiles[i][j] = buffer;
        }
    }

    #ifdef DEBUG

        oss.str("");

        oss << "Width\t\t: "
            << dec << mWidth << endl

            << "Height\t\t: "
            << dec << mHeight << endl

            << "Background\t: \""
            << mBackground << "\"" << endl

            << "Tileset\t\t: \""
            << mTileset << "\"";

        log( oss.str().c_str(), __PRETTY_FUNCTION__ );

    #endif // DEBUG

    // --- Fermeture. ----------------------------------------------------------
    file.close();
}

//! @brief Procédure d'écriture d'un fichier CMF.
//! @param filepath Chemin vers le fichier.
//! @param test_checksum Indique si il faut écraser le fichier.
//! @throw CiException
void cirion::Cmf::save( const char* filepath, bool overwrite )
{
    fstream file; //!< Un flux de fichier

    // --- Doit-on tester l'existance du fichier ? -----------------------------
    if( !overwrite )
    {
        /* Ouverture du fichier. */
        file.open( filepath, ios::binary | ios::in );

        /* Test d'existance: le fichier existe. */
        if( file.is_open() )
        {
            file.close();
            throw CiException( (char*)"File exists.", __PRETTY_FUNCTION__ );
        }

        file.close();
    }

    // --- Ouverture du fichier. -----------------------------------------------
    file.open( filepath, ios::binary | ios::in | ios::out | ios::trunc );

    if( !file.is_open() )
    {
        throw CiException( (char*)"Unable to create output file.",
            __PRETTY_FUNCTION__ );
    }

    // --- Ecriture de l'en-tête CMF. ------------------------------------------
    file.write( (char*)&mMagic,    sizeof(int) );
    file.write( (char*)&mChecksum, sizeof(int) ); /* ! A recalculer ! */
    file.write( (char*)&mWidth,    sizeof(int) );
    file.write( (char*)&mHeight,   sizeof(int) );
    file.write( mBackground, 16 * sizeof(char) );
    file.write( mTileset,    16 * sizeof(char) );

    // --- Ecriture des entrées des tuiles. ------------------------------------
    for( size_t i = 0; i != mHeight; i++ )
    {
        for( size_t j = 0; j != mWidth; j++ )
        {
            file.write( (char*)&mTiles[i][j], sizeof(char) );
        }
    }

    // --- Mise à jour de la somme de contrôle. --------------------------------
    unsigned int computedChecksum = computeChecksum( &file );

    file.seekg( 0x04 );
    file.write( (char*)&computedChecksum, sizeof(int) );

    // --- Fermeture. ----------------------------------------------------------
    file.close();
}

//! @brief Procédure de vidage des vecteurs de données.
void cirion::Cmf::clear()
{
    for( size_t i = 0; i != mTiles.size() -1; i++ )
    {
        mTiles[i].clear();
    }

    mTiles.clear();
}

//! @brief Procédure de modification des vecteur de données.
//! @param x Colonne.
//! @param y Rangée.
//! @param tile Identifiant de la Tile.
void cirion::Cmf::setTile( int x, int y, unsigned char data )
{
    mTiles[y][x] = data;
}

//! @brief Procédure de redimensionnement des vecteurs de données.
//! @param w Largeur.
void cirion::Cmf::setWidth( size_t width )
{
    for( size_t i = 0; i != mTiles.size() -1; i++ )
    {
        mTiles[i].resize( width );
    }

    mWidth = width;
}

//! @brief Procédure de redimensionnement des vecteurs de données.
//! @param h Largeur.
void cirion::Cmf::setHeight( size_t height )
{
    mTiles.resize( height );
    mHeight = height;
}

//! @brief Fonction accesseur.
//! @return Nom du Background.
char* cirion::Cmf::getBackgroundName()
{
    return mBackground;
}

//! @brief Fonction accesseur.
//! @return Nom du Tileset.
char* cirion::Cmf::getTilesetName()
{
    return mTileset;
}

//! @brief Fonction accesseur.
//! @param i Colonne.
//! @param j Rangée.
//! @return Donnée de l'index des tuiles à l'emplacement i, j.
unsigned char cirion::Cmf::getTile( size_t i, size_t j )
{
    return mTiles[i][j];
}

//! @brief Fonction accesseur.
//! @return Largeur de l'index des tuiles.
size_t cirion::Cmf::getWidth()
{
    return mWidth;
}

//! @brief Fonction accesseur.
//! @return Hauteur de l'index des tuiles.
size_t cirion::Cmf::getHeight()
{
    return mHeight;
}
