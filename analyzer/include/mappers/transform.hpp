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


#ifndef BRIDGE_ANALYZER_MAPPERS_TRANSFORM_HPP
#define BRIDGE_ANALYZER_MAPPERS_TRANSFORM_HPP

#include <opencv2/imgproc.hpp>
#include <type_traits>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::mappers::transform
 */

/**
 * @brief This namespace describes different utilities related to
 * \ref transform
 */

namespace bridge::analyzer::mappers::transform
{
    /**
     * @brief A function object allowing to preprocess the input data
     *
     * This function object aims to provide a functional way to preprocess data
     * before to set as input of the artificial neural network.
     */

    class transform
    {
        friend bool operator==(const transform&, const transform&);
        friend bool operator!=(const transform&, const transform&);
        friend void swap(transform&, transform&) noexcept;
    public:
        /**
         * @brief Default constructor of \ref transform
         */

        transform() = default;

        /**
         * @brief Destructor of \ref transform
         */

        ~transform() noexcept = default;

        /**
         * @brief Copy constructor of \ref transform
         *
         * @param[in] __other The \ref transform to copy
         */

        transform(const transform& __other) = default;

        /**
         * @brief Move constructor of \ref transform
         *
         * @param[in] __other The \ref transform to move
         */

        transform(transform&& __other) = default;

        /**
         * @brief Constructs a \ref transform with the given parameters
         *
         * @param[in] __angle The angle used for the rotation
         * @param[in] __center The center used for the rotation
         * @param[in] __roi The region of interest
         * @param[in] __size The size used for the resizing
         */

        explicit transform(
            double __angle,
            cv::Point2f __center,
            cv::Rect __roi,
            cv::Size __size
        )
            : m_angle(__angle)
            , m_center(std::move(__center))
            , m_roi(std::move(__roi))
            , m_size(std::move(__size))
        {}
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref transform
         */

        transform& operator=(const transform& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref transform
         */

        transform& operator=(transform&& __rhs) = default;
    public:
        /**
         * @brief Applies transformations to the input matrix
         *
         * @param[in] __input The input matrix to transform
         * @return The transformed matrix
         */

        cv::Mat operator()(const cv::Mat& __input);
    private:
        double m_angle;       ///< The angle used for the rotation
        cv::Point2f m_center; ///< The center used for the rotation
        cv::Rect m_roi;       ///< The region of interest
        cv::Size m_size;      ///< The size used for the resizing
    };

    /**
     * @brief Equality operator for \ref transform
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const transform& __lhs, const transform& __rhs)
    {
        return
            (__lhs.m_angle == __rhs.m_angle) &&
            (__lhs.m_center == __rhs.m_center) &&
            (__lhs.m_roi == __rhs.m_roi) &&
            (__lhs.m_size == __rhs.m_size);
    }

    /**
     * @brief Inequality operator for \ref transform
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const transform& __lhs, const transform& __rhs)
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref transform
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    void swap(transform& __lhs, transform& __rhs) noexcept;
}

#endif // BRIDGE_ANALYZER_MAPPERS_TRANSFORM_HPP
