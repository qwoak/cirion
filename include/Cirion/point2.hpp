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
 * @file    point2.hpp
 * @version 0.1.0.1
 * @author  Jérémy S. "Qwoak"
 * @date    13 Janvier 2016
 * @brief   Template pour représenter des coordonnées 2d.
 */

#ifndef POINT2_HPP
#define POINT2_HPP

#include <iostream>
#include <ostream>

namespace cirion
{
    /**
     * @class Point2 point2.hpp
     *
     * Une classe représentant un point dans un espace 2d
     */
    template <typename Type> class Point2
    {
    public:
        //! @brief Constructeur pour la classe Point2
        Point2() : mX(0), mY(0)
        {
        }

        //! @brief Constructeur pour la classe Point2
        //! @param x L'abscisse du point
        //! @param y L'ordonnée du point
        Point2( const Type& x, const Type& y ) : mX(x), mY(y)
        {
        }
        
        //! @brief Surcharge de l'opérateur d'addition
        //! @param rhs point 2d à additionner
        //! @return Un nouveau point résultant de l'opération
        Point2<Type> operator +( const Point2<Type>& rhs )
        {
            return Point2<Type>( mX + rhs.mX, mY + rhs.mY );
        }

        //! @brief Surcharge de l'opérateur de soustraction
        //! @param rhs point 2d à soustraire
        //! @return Un nouveau point résultant de l'opération
        Point2<Type> operator -( const Point2<Type>& rhs )
        {
            return Point2<Type>( mX - rhs.mX, mY - rhs.mY );
        }

        //! @brief Surcharge de l'opérateur de multiplication
        //! @param rhs point 2d à multiplier
        //! @return Un nouveau point résultant de l'opération
        Point2<Type> operator *( const Point2<Type>& rhs )
        {
            return Point2<Type>( mX * rhs.mX, mY * rhs.mY );
        }

        //! @brief Surcharge de l'opérateur de division
        //! @param rhs point 2d à diviser
        //! @return Un nouveau point résultant de l'opération
        Point2<Type> operator /( const Point2<Type>& rhs )
        {
            return Point2<Type>( mX / rhs.mX, mY / rhs.mY );
        }

        //! @brief Surcharge de l'opérateur d'affectation avec addition
        //! @param rhs point 2d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point2<Type>& operator +=( const Point2<Type>& rhs )
        {
            mX += rhs.mX;
            mY += rhs.mY;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec soustraction
        //! @param rhs point 2d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point2<Type>& operator -=( const Point2<Type>& rhs )
        {
            mX -= rhs.mX;
            mY -= rhs.mY;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec multiplication
        //! @param rhs point 2d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point2<Type>& operator *=( const Point2<Type>& rhs )
        {
            mX *= rhs.mX;
            mY *= rhs.mY;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec division
        //! @param rhs point 2d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point2<Type>& operator /=( const Point2<Type>& rhs )
        {
            mX /= rhs.mX;
            mY /= rhs.mY;
            return *this;
        }

        //! @brief Surcharge de l'opérateur de test d'égalité
        //! @param rhs point 2d à comparer
        //! @return Résultat de l'opération
        bool operator ==( const Point2<Type>& rhs )
        {
            return ( mX == rhs.mX ) && ( mY == rhs.mY );
        }

        //! @brief Surcharge de l'opérateur de test de différence
        //! @param rhs point 2d à comparer
        //! @return Résultat de l'opération
        bool operator !=( const Point2<Type>& rhs )
        {
            return ( mX != rhs.mX ) || ( mY != rhs.mY );
        }

        /** Abscisse du point */
        Type mX;
        /** Ordonnée du point */
        Type mY;
    };

    //! @brief Surcharge de l'opérateur d'affichage
    //! @param rhs point 2d à afficher
    //! @return Le nouveau flux modifié
    template <typename Type>
    std::ostream& operator <<( std::ostream& lhs, const Point2<Type>& rhs )
    {
        lhs << "(x:" << rhs.mX << "; y:" << rhs.mY << ")";
        return lhs;
    }

    // Définition des types construits sur le patron Point2
    typedef Point2<int>   Point2i;
    typedef Point2<float> Point2f;
}

#endif // POINT2_HPP
