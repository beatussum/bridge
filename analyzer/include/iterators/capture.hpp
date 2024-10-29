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


#ifndef BRIDGE_ANALYZER_ITERATORS_CAPTURE_HPP
#define BRIDGE_ANALYZER_ITERATORS_CAPTURE_HPP

#include <opencv2/videoio.hpp>
#include <optional>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::iterators::capture
 */

/**
 * @brief This namespace describes different utilities related to \ref capture
 */

namespace bridge::analyzer::iterators::capture
{
    struct iterated_tag {}; ///< A dispatch type used by \ref operator|()

    /**
     * @brief An iterator allowing to iterate over the frames of a
     * `cv::VideoCapture`
     */

    class capture
    {
        friend inline bool operator==(const capture&, const capture&);
        friend inline void swap(capture&, capture&);
        friend capture operator|(cv::VideoCapture, iterated_tag);
    public:
        /**
         * @brief The type of the value returned by the difference between two
         * \ref capture
         */

        using difference_type = std::ptrdiff_t;

        /**
         * @brief The type of the pointer pointing to the value referenced by
         * the \ref capture
         */

        using pointer = const cv::Mat*;

        /**
         * @brief The type of the pointer referencing to the value referenced by
         * the \ref capture
         */

        using reference = const cv::Mat&;

        /**
         * @brief The type of the value referenced by the \ref capture
         */

        using value_type = cv::Mat;

        /**
         * @brief The iterator category of the \ref capture
         */

        using iterator_category = std::forward_iterator_tag;
    public:
        /**
         * @brief Default constructor of \ref capture
         */

        capture() = default;

        /**
         * @brief Destructor of \ref capture
         */

        ~capture() = default;

        /**
         * @brief Copy constructor of \ref capture
         *
         * @param[in] __other The other \ref capture to copy
         */

        capture(const capture& __other) = default;

        /**
         * @brief Move constructor of \ref capture
         *
         * @param[in] __other The other \ref capture to move
         */

        capture(capture&& __other) = default;
    private:
        explicit capture(cv::VideoCapture __video_capture)
            : m_video_capture(
                std::make_shared<cv::VideoCapture>(std::move(__video_capture))
            )
            , m_cached()
        { ++*this; }
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref capture
         */

        capture& operator=(const capture& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref capture
         */

        capture& operator=(capture&& __rhs) = default;
    public:
        /**
         * @brief Pre-increment operator
         *
         * @return The new value of the \ref capture
         */

        capture& operator++();

        /**
         * @brief Post-increment operator
         *
         * @return The old value of the \ref capture
         */

        capture operator++(int);

        /**
         * @brief Dereference operator
         *
         * If the current \ref capture has never been dereferenced, this method
         * updates the cached content by applying the suitable mapping;
         * otherwise, this operator only returns the cached value.
         *
         * @return The value of the dereferenced \ref capture
         */

        reference operator*();

        /**
         * @brief Member access of pointer
         *
         * This method uses \ref operator*() and has, therefore, the same
         * behavior.
         *
         * @return A pointer to the member accessed
         */

        pointer operator->() { return &**this; }
    private:
        /**
         * @brief The member used to get images
         */

        std::shared_ptr<cv::VideoCapture> m_video_capture;

        std::optional<cv::Mat> m_cached; ///< The cached last dereferenced value
    };

    /**
     * @brief Equality operator for \ref capture
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const capture& __lhs, const capture& __rhs)
        { return __lhs.m_video_capture == __rhs.m_video_capture; }

    /**
     * @brief Inequality operator for \ref capture
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const capture& __lhs, const capture& __rhs)
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref capture
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    inline void swap(capture& __lhs, capture& __rhs)
        { std::swap(__lhs.m_video_capture, __rhs.m_video_capture); }

    /**
     * @brief Constructs a \ref iterated_tag
     *
     * This functions allows an intuitive interface to iterate over a
     * `cv::VideoCapture`.
     *
     * @return A \ref iterated_tag instance
     */

    constexpr iterated_tag iterated() noexcept
        { return iterated_tag {}; }

    /**
     * @brief Pipe operator for \ref capture
     *
     * This operator aims to provides a convenient way to construct a
     * \ref capture.
     *
     * @param[in] __lhs The input `cv::VideoCapture`
     * @return The \ref capture
     */

    inline capture operator|(cv::VideoCapture __lhs, iterated_tag)
        { return capture(std::move(__lhs)); }
}

#endif // BRIDGE_ANALYZER_ITERATORS_CAPTURE_HPP
