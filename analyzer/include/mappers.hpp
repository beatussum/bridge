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


#ifndef BRIDGE_ANALYZER_MAPPERS_HPP
#define BRIDGE_ANALYZER_MAPPERS_HPP

#include "types/raw.hpp"
#include <opencv2/dnn/dnn.hpp>

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::mappers
 */

/**
 * @brief This namespace describes mapper types
 */

namespace bridge::analyzer::mappers
{
    /**
     * @brief A function object allowing to create a blob from a input image
     */

    struct blob
    {
        /**
         * @brief Creates a blob from a input image
         *
         * @param[in] __image The input image
         * @return A 4-dimensional matrix with NCHW dimensions order
         */

        cv::Mat operator()(const cv::Mat& __image) const
            { return cv::dnn::blobFromImage(__image); }
    };

    /**
     * @brief A function object allowing to cast a
     * \ref bridge::analyzer::types::raw::uncounted::trick to a
     * \ref bridge::analyzer::types::raw::counted::trick
     */

    struct count
    {
        /**
         * @brief casts a \ref bridge::analyzer::types::raw::uncounted::trick to
         * a \ref bridge::analyzer::types::raw::counted::trick
         *
         * @param[in] __uncounted The
         * \ref bridge::analyzer::types::raw::uncounted::trick to cast
         *
         * @return The casted \ref bridge::analyzer::types::raw::counted::trick
         */

        types::raw::counted::trick operator()(
            const types::raw::uncounted::trick& __uncounted
        ) const
            { return types::raw::count(__uncounted); }
    };

    /**
     * @brief A function object allowing to forward an input matrix to the
     * neural network
     */

    class forward
    {
    public:
        /**
         * @brief Default constructor of \ref forward
         */

        forward() = default;

        /**
         * @brief Destructor of \ref forward
         */

        ~forward() noexcept = default;

        /**
         * @brief Copy constructor of \ref forward
         *
         * @param[in] __other The \ref forward to copy
         */

        forward(const forward& __other) = default;

        /**
         * @brief Move constructor of \ref forward
         *
         * @param[in] __other The \ref forward to move
         */

        forward(forward&& __other) = default;
    public:
        /**
         * @brief Constructs a new \ref forward object specifying the underlying
         * ONNX file
         *
         * @param[in] __onnx_file The ONNX file to use
         */

        explicit forward(const cv::String& __onnx_file)
            : m_net(cv::dnn::readNetFromONNX(__onnx_file))
        {}
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref forward
         */

        forward& operator=(const forward& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref forward
         */

        forward& operator=(forward&& __rhs) = default;
    public:
        /**
         * @brief Applies forwardations to the input matrix
         *
         * @param[in] __input The input matrix to forward
         * @return The forwarded matrix
         */

        cv::Mat operator()(const cv::Mat& __input);
    private:
        cv::dnn::Net m_net; ///< The OpenCV neural network
    };

    /**
     * @brief A function object allowing to substract two
     * \ref bridge::analyzer::types::raw::counted::trick
     */

    struct minus : std::minus<types::raw::counted::trick> {};

    /**
     * @brief A function object allowing to keep only positive
     * \ref bridge::analyzer::types::raw::counted::trick
     */

    struct positive
    {
        /**
         * @brief Keeps only positive
         * \ref bridge::analyzer::types::raw::counted::trick
         *
         * @param[in] __counted The trick to filter
         *
         * @return A \ref bridge::analyzer::types::raw::counted::trick without
         * negative \ref bridge::analyzer::types::card::counted_card::n
         */

        types::raw::counted::trick operator()(
            types::raw::counted::trick __counted
        ) const;
    };

    /**
     * @brief A function object allowing to cast a
     * \ref types::raw::boxed::trick to a \ref types::raw::uncounted::trick
     */

    class unbox
    {
        friend bool operator==(const unbox&, const unbox&);
        friend void swap(unbox&, unbox&) noexcept;
    public:
        /**
         * @brief Default constructor of \ref unbox
         */

        unbox() = default;

        /**
         * @brief Destructor of \ref unbox
         */

        ~unbox() noexcept = default;

        /**
         * @brief Copy constructor of \ref unbox
         *
         * @param[in] __other The \ref unbox to copy
         */

        unbox(const unbox& __other) = default;

        /**
         * @brief Move constructor of \ref unbox
         *
         * @param[in] __other The \ref unbox to move
         */

        unbox(unbox&& __other) = default;
    public:
        /**
         * @brief Constructs a new \ref unbox with its center specified
         *
         * @param[in] __center The center used for the call of
         * \ref types::raw::unbox()
         */

        explicit unbox(cv::Point2f __center)
            : m_center(std::move(__center))
        {}
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref unbox
         */

        unbox& operator=(const unbox& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref unbox
         */

        unbox& operator=(unbox&& __rhs) = default;
    public:
        /**
         * @brief Cast a \ref types::raw::boxed::trick to a
         * \ref types::raw::uncounted::trick
         *
         * @param[in] __boxed The \ref types::raw::boxed::trick to cast
         * @return The casted \ref types::raw::uncounted::trick
         *
         * @see types::raw::unbox()
         */

        types::raw::uncounted::trick operator()(
            const types::raw::boxed::trick& __boxed
        ) const
            { return types::raw::unbox(m_center, __boxed); }
    private:
        /**
         * @brief The center used for the call of \ref types::raw::unbox()
         */

        cv::Point2f m_center;
    };

    /**
     * @brief Equality operator for \ref blob
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(const blob& __lhs, const blob& __rhs) noexcept
        { return true; }

    /**
     * @brief Inequality operator for \ref blob
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(const blob& __lhs, const blob& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref blob
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    constexpr void swap(blob& __lhs, blob& __rhs) noexcept
        {}

    /**
     * @brief Equality operator for \ref count
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(const count& __lhs, const count& __rhs) noexcept
        { return true; }

    /**
     * @brief Inequality operator for \ref count
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(const count& __lhs, const count& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref count
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    constexpr void swap(count& __lhs, count& __rhs) noexcept
        {}

    /**
     * @brief Equality operator for \ref minus
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(const minus& __lhs, const minus& __rhs) noexcept
        { return true; }

    /**
     * @brief Inequality operator for \ref minus
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(const minus& __lhs, const minus& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref minus
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    constexpr void swap(minus& __lhs, minus& __rhs) noexcept
        {}

    /**
     * @brief Equality operator for \ref positive
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(
        const positive& __lhs,
        const positive& __rhs
    ) noexcept
        { return true; }

    /**
     * @brief Inequality operator for \ref positive
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(
        const positive& __lhs,
        const positive& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref positive
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    constexpr void swap(positive& __lhs, positive& __rhs) noexcept
        {}

    /**
     * @brief Equality operator for \ref unbox
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const unbox& __lhs, const unbox& __rhs)
        { return __lhs.m_center == __rhs.m_center; }

    /**
     * @brief Inequality operator for \ref unbox
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const unbox& __lhs, const unbox& __rhs)
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref unbox
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    void swap(unbox& __lhs, unbox& __rhs) noexcept;
}

#endif // BRIDGE_ANALYZER_MAPPERS_HPP
