/*
 * Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef BRIDGE_ANALYZER_CORE_CV_HPP
#define BRIDGE_ANALYZER_CORE_CV_HPP

/**
 * @file
 * @brief The base header of \ref cv for bridge
 */

/**
 * @brief Some overloads and specializations of OpenCV entities
 */

namespace cv
{
    template <typename>
    struct Rect_;

    /**
     * @brief Inserts a `cv::Rect_` to an output stream
     *
     * @tparam Ostream The type of \p __os
     * @tparam T The underlying type of the rectangle
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream, class T>
    constexpr Ostream&& operator<<(Ostream&& __os, const Rect_<T>& __value);
}

#include "cv.ipp"

#endif // BRIDGE_ANALYZER_CORE_CV_HPP
