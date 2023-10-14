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
typedef std::vector<T_REAL>  T_ListReal;            ///< Typedef for lists containing floating point values.
typedef std::vector<T_SLONG> T_ListSignedLong;      ///< Typedef for lists containing signed long values.
typedef std::vector<T_ULONG> T_ListUnsignedLong;    ///< Typedef for lists containing unsigned long values.
typedef std::vector<T_BOOL>  T_ListBool;            ///< Typedef for lists containing boolean values.

// column vectors
typedef Eigen::Matrix<T_REAL, Eigen::Dynamic, 1> T_ColumnVectorReal;    ///< Typedef for Xx1 column vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 2, 1>              T_ColumnVectorReal2d;  ///< Typedef for 2x1 column vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 3, 1>              T_ColumnVectorReal3d;  ///< Typedef for 3x1 column vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 4, 1>              T_ColumnVectorReal4d;  ///< Typedef for 4x1 column vectors of floating point values.

// row vectors
typedef Eigen::Matrix<T_REAL, 1, Eigen::Dynamic> T_RowVectorReal;   ///< Typedef for 1xX row vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 1, 2>              T_RowVectorReal2d; ///< Typedef for 1x2 row vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 1, 3>              T_RowVectorReal3d; ///< Typedef for 1x3 row vectors of floating point values.
typedef Eigen::Matrix<T_REAL, 1, 4>              T_RowVectorReal4d; ///< Typedef for 1x4 row vectors of floating point values.

// lists of column vectors
typedef std::vector< T_ColumnVectorReal, Eigen::aligned_allocator<T_ColumnVectorReal> >     T_ListColumnVectorReal;     ///< Typedef for lists containing Xx1 column vectors of floating point values.
typedef std::vector< T_ColumnVectorReal2d, Eigen::aligned_allocator<T_ColumnVectorReal2d> > T_ListColumnVectorReal2d;   ///< Typedef for lists containing 2x1 column vectors of floating point values.
typedef std::vector< T_ColumnVectorReal3d, Eigen::aligned_allocator<T_ColumnVectorReal3d> > T_ListColumnVectorReal3d;   ///< Typedef for lists containing 3x1 column vectors of floating point values.
typedef std::vector< T_ColumnVectorReal4d, Eigen::aligned_allocator<T_ColumnVectorReal4d> > T_ListColumnVectorReal4d;   ///< Typedef for lists containing 4x1 column vectors of floating point values.

// lists of row vectors
typedef std::vector< T_RowVectorReal, Eigen::aligned_allocator<T_RowVectorReal> >     T_ListRowVectorReal;      ///< Typedef for lists containing 1xX row vectors of floating point values.
typedef std::vector< T_RowVectorReal2d, Eigen::aligned_allocator<T_RowVectorReal2d> > T_ListRowVectorReal2d;    ///< Typedef for lists containing 1x2 row vectors of floating point values.
typedef std::vector< T_RowVectorReal3d, Eigen::aligned_allocator<T_RowVectorReal3d> > T_ListRowVectorReal3d;    ///< Typedef for lists containing 1x3 row vectors of floating point values.
typedef std::vector< T_RowVectorReal4d, Eigen::aligned_allocator<T_RowVectorReal4d> > T_ListRowVectorReal4d;    ///< Typedef for lists containing 1x4 row vectors of floating point values.

// general matrices
typedef Eigen::Matrix<T_REAL, Eigen::Dynamic, Eigen::Dynamic>  T_MatrixReal;            ///< Typedef for general matrices of floating point values.
typedef Eigen::Matrix<T_SLONG, Eigen::Dynamic, Eigen::Dynamic> T_MatrixSignedLong;      ///< Typedef for general matrices of signed long values.
typedef Eigen::Matrix<T_ULONG, Eigen::Dynamic, Eigen::Dynamic> T_MatrixUnsignedLong;    ///< Typedef for general matrices of unsigned long values.
typedef Eigen::Matrix<T_BOOL, Eigen::Dynamic, Eigen::Dynamic>  T_MatrixBoolean;         ///< Typedef for general matrices of boolean values.

// square matrices
typedef Eigen::Matrix<T_REAL, 2, 2> T_MatrixReal2d; ///< Typedef for 2x2 square matrices of floating point values.
typedef Eigen::Matrix<T_REAL, 3, 3> T_MatrixReal3d; ///< Typedef for 3x3 square matrices of floating point values.
typedef Eigen::Matrix<T_REAL, 4, 4> T_MatrixReal4d; ///< Typedef for 4x4 square matrices of floating point values.

// matrices
typedef Eigen::Matrix<T_REAL, 3, 4> T_MatrixReal3x4;    ///< Typedef for 3x4 matrices of floating point values.

// lists of general matrices
typedef std::vector< T_MatrixReal, Eigen::aligned_allocator<T_MatrixReal> >                 T_ListMatrixReal;           ///< Typedef for lists containing general matrices of floating point values.
typedef std::vector< T_MatrixSignedLong, Eigen::aligned_allocator<T_MatrixSignedLong> >     T_ListMatrixSignedLong;     ///< Typedef for lists containing general matrices of signed long values.
typedef std::vector< T_MatrixUnsignedLong, Eigen::aligned_allocator<T_MatrixUnsignedLong> > T_ListMatrixUnsignedLong;   ///< Typedef for lists containing general matrices of unsigned long values.
typedef std::vector< T_MatrixBoolean, Eigen::aligned_allocator<T_MatrixBoolean> >           T_ListMatrixBoolean;        ///< Typedef for lists containing general matrices of boolean values.

// lists of matrices
typedef std::vector< T_MatrixReal4d, Eigen::aligned_allocator<T_MatrixReal4d> > T_ListMatrixReal4d; ///< Typedef for lists containing 4x4 square matrices of floating point values.

#endif // GLOBALTYPESDERIVED_H
