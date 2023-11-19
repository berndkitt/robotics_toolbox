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
using ListFloat64 = std::vector<float64>;   ///< Alias for lists containing 64-bit floating point values.
using ListSInt64  = std::vector<sint64>;    ///< Alias for lists containing 64-bit signed integer values.
using ListUInt64  = std::vector<uint64>;    ///< Alias for lists containing 64-bit unsigned integer values.
using ListBoolean = std::vector<boolean>;   ///< Alias for lists containing boolean values.

// column vectors
using ColumnVectorFloat64    = Eigen::Matrix<float64, Eigen::Dynamic, 1>;   ///< Alias for Xx1 column vectors of 64-bit floating point values.
using ColumnVectorFloat64_2d = Eigen::Matrix<float64, 2, 1>;                ///< Alias for 2x1 column vectors of 64-bit floating point values.
using ColumnVectorFloat64_3d = Eigen::Matrix<float64, 3, 1>;                ///< Alias for 3x1 column vectors of 64-bit floating point values.
using ColumnVectorFloat64_4d = Eigen::Matrix<float64, 4, 1>;                ///< Alias for 4x1 column vectors of 64-bit floating point values.

// row vectors
using RowVectorFloat64    = Eigen::Matrix<float64, 1, Eigen::Dynamic>;  ///< Alias for 1xX row vectors of 64-bit floating point values.
using RowVectorFloat64_2d = Eigen::Matrix<float64, 1, 2>;               ///< Alias for 1x2 row vectors of 64-bit floating point values.
using RowVectorFloat64_3d = Eigen::Matrix<float64, 1, 3>;               ///< Alias for 1x3 row vectors of 64-bit floating point values.
using RowVectorFloat64_4d = Eigen::Matrix<float64, 1, 4>;               ///< Alias for 1x4 row vectors of 64-bit floating point values.

// lists of column vectors
using ListColumnVectorFloat64    = std::vector< ColumnVectorFloat64, Eigen::aligned_allocator<ColumnVectorFloat64> >;       ///< Alias for lists containing Xx1 column vectors of 64-bit floating point values.
using ListColumnVectorFloat64_2d = std::vector< ColumnVectorFloat64_2d, Eigen::aligned_allocator<ColumnVectorFloat64_2d> >; ///< Alias for lists containing 2x1 column vectors of 64-bit floating point values.
using ListColumnVectorFloat64_3d = std::vector< ColumnVectorFloat64_3d, Eigen::aligned_allocator<ColumnVectorFloat64_3d> >; ///< Alias for lists containing 3x1 column vectors of 64-bit floating point values.
using ListColumnVectorFloat64_4d = std::vector< ColumnVectorFloat64_4d, Eigen::aligned_allocator<ColumnVectorFloat64_4d> >; ///< Alias for lists containing 4x1 column vectors of 64-bit floating point values.

// lists of row vectors
using ListRowVectorFloat64    = std::vector< RowVectorFloat64, Eigen::aligned_allocator<RowVectorFloat64> >;        ///< Alias for lists containing 1xX row vectors of 64-bit floating point values.
using ListRowVectorFloat64_2d = std::vector< RowVectorFloat64_2d, Eigen::aligned_allocator<RowVectorFloat64_2d> >;  ///< Alias for lists containing 1x2 row vectors of 64-bit floating point values.
using ListRowVectorFloat64_3d = std::vector< RowVectorFloat64_3d, Eigen::aligned_allocator<RowVectorFloat64_3d> >;  ///< Alias for lists containing 1x3 row vectors of 64-bit floating point values.
using ListRowVectorFloat64_4d = std::vector< RowVectorFloat64_4d, Eigen::aligned_allocator<RowVectorFloat64_4d> >;  ///< Alias for lists containing 1x4 row vectors of 64-bit floating point values.

// general matrices
using MatrixFloat64 = Eigen::Matrix<float64, Eigen::Dynamic, Eigen::Dynamic>;   ///< Alias for general matrices of 64-bit floating point values.
using MatrixSInt64  = Eigen::Matrix<sint64, Eigen::Dynamic, Eigen::Dynamic>;    ///< Alias for general matrices of 64-bit signed integer values.
using MatrixUInt64  = Eigen::Matrix<uint64, Eigen::Dynamic, Eigen::Dynamic>;    ///< Alias for general matrices of 64-bit unsigned integer values.
using MatrixBoolean = Eigen::Matrix<boolean, Eigen::Dynamic, Eigen::Dynamic>;   ///< Alias for general matrices of boolean values.

// square matrices
using MatrixFloat64_2d = Eigen::Matrix<float64, 2, 2>;  ///< Alias for 2x2 square matrices of 64-bit floating point values.
using MatrixFloat64_3d = Eigen::Matrix<float64, 3, 3>;  ///< Alias for 3x3 square matrices of 64-bit floating point values.
using MatrixFloat64_4d = Eigen::Matrix<float64, 4, 4>;  ///< Alias for 4x4 square matrices of 64-bit floating point values.

// matrices
using MatrixFloat64_3x4 = Eigen::Matrix<float64, 3, 4>; ///< Alias for 3x4 matrices of 64 bit floating point values.

// lists of general matrices
using ListMatrixFloat64 = std::vector< MatrixFloat64, Eigen::aligned_allocator<MatrixFloat64> >;    ///< Alias for lists containing general matrices of 64-bit floating point values.
using ListMatrixSInt64  = std::vector< MatrixSInt64, Eigen::aligned_allocator<MatrixSInt64> >;      ///< Alias for lists containing general matrices of 64-bit signed integer values.
using ListMatrixUInt64  = std::vector< MatrixUInt64, Eigen::aligned_allocator<MatrixUInt64> >;      ///< Alias for lists containing general matrices of 64-bit unsigned integer values.
using ListMatrixBoolean = std::vector< MatrixBoolean, Eigen::aligned_allocator<MatrixBoolean> >;    ///< Alias for lists containing general matrices of boolean values.

// lists of matrices
using ListMatrixFloat64_4d = std::vector< MatrixFloat64_4d, Eigen::aligned_allocator<MatrixFloat64_4d> >;   ///< Alias for lists containing 4x4 square matrices of 64-bit floating point values.

#endif // GLOBALTYPESDERIVED_H
