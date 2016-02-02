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
 * @file    Point3.hpp
 * @version 0.1.0.1
 * @author  Jérémy S. "Qwoak"
 * @date    13 Janvier 2016
 * @brief   Template pour représenter des coordonnées 3d.
 */

#ifndef POINT3_HPP
#define POINT3_HPP

#include <iostream>
#include <ostream>

namespace cirion
{
    /**
     * @class Point3 point3.hpp
     *
     * Une classe représentant un point dans un espace 2d
     */
    template <typename Type> class Point3
    {
    public:
        //! @brief Constructeur pour la classe Point3
        Point3() : mX(0), mY(0), mZ(0)
        {
        }

        //! @brief Constructeur pour la classe Point3
        //! @param x L'abscisse du point
        //! @param y L'ordonnée du point
        //! @param z La profondeur du point
        Point3( const Type& x, const Type& y, const Type& z )
            : mX(x), mY(y), mZ(z)
        {
        }

        //! @brief Surcharge de l'opérateur d'addition
        //! @param rhs point 3d à additionner
        //! @return Un nouveau point résultant de l'opération
        Point3<Type> operator +( const Point3<Type>& rhs )
        {
            return Point3<Type>( mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ );
        }

        //! @brief Surcharge de l'opérateur de soustraction
        //! @param rhs point 3d à soustraire
        //! @return Un nouveau point résultant de l'opération
        Point3<Type> operator -( const Point3<Type>& rhs )
        {
            return Point3<Type>( mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ );
        }

        //! @brief Surcharge de l'opérateur de multiplication
        //! @param rhs point 3d à multiplier
        //! @return Un nouveau point résultant de l'opération
        Point3<Type> operator *( const Point3<Type>& rhs )
        {
            return Point3<Type>( mX * rhs.mX, mY * rhs.mY, mZ * rhs.mZ );
        }

        //! @brief Surcharge de l'opérateur de division
        //! @param rhs point 3d à diviser
        //! @return Un nouveau point résultant de l'opération
        Point3<Type> operator /( const Point3<Type>& rhs )
        {
            return Point3<Type>( mX / rhs.mX, mY / rhs.mY, mZ / rhs.mZ );
        }

        //! @brief Surcharge de l'opérateur d'affectation avec addition
        //! @param rhs point 3d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point3<Type>& operator +=( const Point3<Type>& rhs )
        {
            mX += rhs.mX;
            mY += rhs.mY;
            mZ += rhs.mZ;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec soustraction
        //! @param rhs point 3d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point3<Type>& operator -=( const Point3<Type>& rhs )
        {
            mX -= rhs.mX;
            mY -= rhs.mY;
            mZ -= rhs.mZ;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec multiplication
        //! @param rhs point 3d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point3<Type>& operator *=( const Point3<Type>& rhs )
        {
            mX *= rhs.mX;
            mY *= rhs.mY;
            mZ *= rhs.mZ;
            return *this;
        }

        //! @brief Surcharge de l'opérateur d'affectation avec division
        //! @param rhs point 3d à additionner
        //! @return Réference sur un nouveau point résultant de l'opération
        Point3<Type>& operator /=( const Point3<Type>& rhs )
        {
            mX /= rhs.mX;
            mY /= rhs.mY;
            mZ /= rhs.mZ;
            return *this;
        }

        //! @brief Surcharge de l'opérateur de test d'égalité
        //! @param rhs point 3d à comparer
        //! @return Résultat de l'opération
        bool operator ==( const Point3<Type>& rhs )
        {
            return ( mX == rhs.mX ) && ( mY == rhs.mY ) && ( mZ == rhs.mZ );
        }

        //! @brief Surcharge de l'opérateur de test de différence
        //! @param rhs point 3d à comparer
        //! @return Résultat de l'opération
        bool operator !=( const Point3<Type>& rhs )
        {
            return ( mX != rhs.mX ) || ( mY != rhs.mY ) || ( mZ != rhs.mZ );
        }

        /** Abscisse du point */
        Type mX;
        /** Ordonnée du point */
        Type mY;
        /** Profondeur du point */
        Type mZ;
    };

    /* +--------------------------------------------------------------------+
       ! Déclaration et définition des surcharges opérateurs comme          !
       ! fonctions                                                          !
       +--------------------------------------------------------------------+ */

    //! @brief Surcharge de l'opérateur d'affichage
    //! @param rhs point 3d à afficher
    //! @return Le nouveau flux modifié
    template <typename Type>
    std::ostream& operator <<( std::ostream& lhs, const Point3<Type>& rhs )
    {
        lhs << "(x:" << rhs.mX << "; y:" << rhs.mY << ")";
        return lhs;
    }

    // Définition des types construits sur le patron Point3
    typedef Point3<int>   Point3i;
    typedef Point3<float> Point3f;
}

#endif // POINT3_HPP
