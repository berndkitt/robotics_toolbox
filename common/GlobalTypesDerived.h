///////////////////////////////////////////////////////////////////////////////
/// \file GlobalTypesDerived.h
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2023

Authors: Bernd Kitt (b.kitt@berndkitt.de)

The Robotics Toolbox is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3 of the License,
or any later version.

The Robotics Toolbox is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with
the Robotics Toolbox. If not, see https://www.gnu.org/licenses/.
*/

#ifndef GLOBALTYPESDERIVED_H
#define GLOBALTYPESDERIVED_H

#include <Eigen/Dense>
#include <Eigen/StdVector>

#include <GlobalTypesBase.h>

// lists
using T_ListReal         = std::vector<T_REAL>;     ///< Alias for lists containing floating point values.
using T_ListSignedLong   = std::vector<T_SLONG>;    ///< Alias for lists containing signed long values.
using T_ListUnsignedLong = std::vector<T_ULONG>;    ///< Alias for lists containing unsigned long values.
using T_ListBool         = std::vector<T_BOOL>;     ///< Alias for lists containing boolean values.

// column vectors
using T_ColumnVectorReal   = Eigen::Matrix<T_REAL, Eigen::Dynamic, 1>;  ///< Alias for Xx1 column vectors of floating point values.
using T_ColumnVectorReal2d = Eigen::Matrix<T_REAL, 2, 1>;               ///< Alias for 2x1 column vectors of floating point values.
using T_ColumnVectorReal3d = Eigen::Matrix<T_REAL, 3, 1>;               ///< Alias for 3x1 column vectors of floating point values.
using T_ColumnVectorReal4d = Eigen::Matrix<T_REAL, 4, 1>;               ///< Alias for 4x1 column vectors of floating point values.

// row vectors
using T_RowVectorReal   = Eigen::Matrix<T_REAL, 1, Eigen::Dynamic>; ///< Alias for 1xX row vectors of floating point values.
using T_RowVectorReal2d = Eigen::Matrix<T_REAL, 1, 2>;              ///< Alias for 1x2 row vectors of floating point values.
using T_RowVectorReal3d = Eigen::Matrix<T_REAL, 1, 3>;              ///< Alias for 1x3 row vectors of floating point values.
using T_RowVectorReal4d = Eigen::Matrix<T_REAL, 1, 4>;              ///< Alias for 1x4 row vectors of floating point values.

// lists of column vectors
using T_ListColumnVectorReal   = std::vector< T_ColumnVectorReal, Eigen::aligned_allocator<T_ColumnVectorReal> >;       ///< Alias for lists containing Xx1 column vectors of floating point values.
using T_ListColumnVectorReal2d = std::vector< T_ColumnVectorReal2d, Eigen::aligned_allocator<T_ColumnVectorReal2d> >;   ///< Alias for lists containing 2x1 column vectors of floating point values.
using T_ListColumnVectorReal3d = std::vector< T_ColumnVectorReal3d, Eigen::aligned_allocator<T_ColumnVectorReal3d> >;   ///< Alias for lists containing 3x1 column vectors of floating point values.
using T_ListColumnVectorReal4d = std::vector< T_ColumnVectorReal4d, Eigen::aligned_allocator<T_ColumnVectorReal4d> >;   ///< Alias for lists containing 4x1 column vectors of floating point values.

// lists of row vectors
using T_ListRowVectorReal   = std::vector< T_RowVectorReal, Eigen::aligned_allocator<T_RowVectorReal> >;        ///< Alias for lists containing 1xX row vectors of floating point values.
using T_ListRowVectorReal2d = std::vector< T_RowVectorReal2d, Eigen::aligned_allocator<T_RowVectorReal2d> >;    ///< Alias for lists containing 1x2 row vectors of floating point values.
using T_ListRowVectorReal3d = std::vector< T_RowVectorReal3d, Eigen::aligned_allocator<T_RowVectorReal3d> >;    ///< Alias for lists containing 1x3 row vectors of floating point values.
using T_ListRowVectorReal4d = std::vector< T_RowVectorReal4d, Eigen::aligned_allocator<T_RowVectorReal4d> >;    ///< Alias for lists containing 1x4 row vectors of floating point values.

// general matrices
using T_MatrixReal         = Eigen::Matrix<T_REAL, Eigen::Dynamic, Eigen::Dynamic>;     ///< Alias for general matrices of floating point values.
using T_MatrixSignedLong   = Eigen::Matrix<T_SLONG, Eigen::Dynamic, Eigen::Dynamic>;    ///< Alias for general matrices of signed long values.
using T_MatrixUnsignedLong = Eigen::Matrix<T_ULONG, Eigen::Dynamic, Eigen::Dynamic>;    ///< Alias for general matrices of unsigned long values.
using T_MatrixBoolean      = Eigen::Matrix<T_BOOL, Eigen::Dynamic, Eigen::Dynamic>;     ///< Alias for general matrices of boolean values.

// square matrices
using T_MatrixReal2d = Eigen::Matrix<T_REAL, 2, 2>; ///< Alias for 2x2 square matrices of floating point values.
using T_MatrixReal3d = Eigen::Matrix<T_REAL, 3, 3>; ///< Alias for 3x3 square matrices of floating point values.
using T_MatrixReal4d = Eigen::Matrix<T_REAL, 4, 4>; ///< Alias for 4x4 square matrices of floating point values.

// matrices
using T_MatrixReal3x4 = Eigen::Matrix<T_REAL, 3, 4>;    ///< Alias for 3x4 matrices of floating point values.

// lists of general matrices
using T_ListMatrixReal         = std::vector< T_MatrixReal, Eigen::aligned_allocator<T_MatrixReal> >;                   ///< Alias for lists containing general matrices of floating point values.
using T_ListMatrixSignedLong   = std::vector< T_MatrixSignedLong, Eigen::aligned_allocator<T_MatrixSignedLong> >;       ///< Alias for lists containing general matrices of signed long values.
using T_ListMatrixUnsignedLong = std::vector< T_MatrixUnsignedLong, Eigen::aligned_allocator<T_MatrixUnsignedLong> >;   ///< Alias for lists containing general matrices of unsigned long values.
using T_ListMatrixBoolean      = std::vector< T_MatrixBoolean, Eigen::aligned_allocator<T_MatrixBoolean> >;             ///< Alias for lists containing general matrices of boolean values.

// lists of matrices
using T_ListMatrixReal4d = std::vector< T_MatrixReal4d, Eigen::aligned_allocator<T_MatrixReal4d> >; ///< Alias for lists containing 4x4 square matrices of floating point values.

#endif // GLOBALTYPESDERIVED_H
