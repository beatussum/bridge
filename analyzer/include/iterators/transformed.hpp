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


#ifndef BRIDGE_ANALYZER_ITERATORS_TRANSFORMED_HPP
#define BRIDGE_ANALYZER_ITERATORS_TRANSFORMED_HPP

#include <opencv2/imgproc.hpp>
#include <type_traits>

/**
 * @file
 * @brief The base header of the namespace
 * bridge::analyzer::iterators::transformed
 */

/**
 * @brief This namespace describes different utilities related to
 * transformed_iterator
 */

namespace bridge::analyzer::iterators::transformed
{
    /**
     * @brief The transformation parameters used by transformed_iterator
     */

    struct transformed_parameters
    {
        double      angle;  ///< The angle used for the rotation
        cv::Point2f center; ///< The center used for the rotation
        cv::Rect    roi;    ///< The region of interest
        cv::Size    size;   ///< The size used for the resizing
    };

    /**
     * @brief An iterator allowing to preprocess the input data
     *
     * This iterator aims to provide a functional way to preprocess data before
     * to set as input of the artificial neural network.
     *
     * @tparam Iterator The inner iterator used to get the input
     */

    template <class Iterator>
    class transformed_iterator
    {
        template <class I>
        friend bool operator==(
            const transformed_iterator<I>&,
            const transformed_iterator<I>&
        );

        template <class I>
        friend bool operator!=(
            const transformed_iterator<I>&,
            const transformed_iterator<I>&
        );

        template <class I>
        friend void swap(transformed_iterator<I>&, transformed_iterator<I>&);
    public:
        /**
         * @brief The type of the value returned by the difference between two
         * transformed_iterator
         */

        using difference_type =
            typename std::iterator_traits<Iterator>::difference_type;

        /**
         * @brief The type of the pointer pointing to the value referenced by
         * the transformed_iterator
         */

        using pointer = const cv::Mat*;

        /**
         * @brief The type of the pointer referencing to the value referenced by
         * the transformed_iterator
         */

        using reference = const cv::Mat&;

        /**
         * @brief The type of the value referenced by the transformed_iterator
         */

        using value_type = cv::Mat;

        /**
         * @brief The iterator category of the transformed_iterator
         */

        using iterator_category = std::forward_iterator_tag;

        static_assert(
            std::conjunction_v<
                std::is_convertible<
                    typename std::iterator_traits<Iterator>::pointer,
                    pointer
                >,

                std::is_convertible<
                    typename std::iterator_traits<Iterator>::reference,
                    reference
                >,

                std::is_convertible<
                    typename std::iterator_traits<Iterator>::value_type,
                    value_type
                >,

                std::is_base_of<
                    iterator_category,
                    typename std::iterator_traits<Iterator>::iterator_category
                >
            >,

            "The inner iterator is not compatible"
        );
    public:
        /**
         * @brief Default constructor of transformed_iterator
         */

        transformed_iterator()
            : m_inner()
            , m_parameters {}
            , m_content()
            , m_need_update(true)
        {}

        /**
         * @brief Destructor of transformed_iterator
         */

        ~transformed_iterator() noexcept = default;

        /**
         * @brief Copy constructor of transformed_iterator
         *
         * @param[in] __iterator The iterator to copy
         */

        transformed_iterator(const transformed_iterator& __iterator)
            : m_inner(__iterator.m_inner)
            , m_parameters(__iterator.m_parameters)
            , m_content(__iterator.m_content.clone())
            , m_need_update(__iterator.m_need_update)
        {}

        /**
         * @brief Move constructor of transformed_iterator
         *
         * @param[in] __iterator The iterator to move
         */

        transformed_iterator(transformed_iterator&& __iterator) = default;

        /**
         * @brief Constructs a transformed_iterator with the given parameters
         *
         * @param[in] __inner The inner iterator
         * @param[in] __parameters The parameters used for the transformation
         */

        explicit transformed_iterator(
            Iterator&& __inner,
            transformed_parameters __parameters
        )
            : m_inner(std::forward<Iterator>(__inner))
            , m_parameters(std::move(__parameters))
            , m_content()
            , m_need_update(true)
        {}

        /**
         * @overload
         * @brief Constructs a transformed_iterator with the given parameters
         *
         * @param[in] __inner The inner iterator
         * @param[in] __angle The angle used for the rotation
         * @param[in] __center The center used for the rotation
         * @param[in] __roi The region of interest
         * @param[in] __size The size used for the resizing
         */

        explicit transformed_iterator(
            Iterator&& __inner,
            double __angle,
            cv::Point2f __center,
            cv::Rect __roi,
            cv::Size __size
        )
            : transformed_iterator(
                std::forward<Iterator>(__inner),

                transformed_parameters {
                    __angle,
                    std::move(__center),
                    std::move(__roi),
                    std::move(__size)
                }
            )
        {}
    public:
        /**
         * @brief Copy and move assignment operator
         *
         * @remark This operator uses the copy-and-swap idiom.
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned iterator
         */

        transformed_iterator& operator=(transformed_iterator __rhs);
    public:
        /**
         * @brief Pre-increment operator
         *
         * @return The new value of the transformed_iterator
         */

        transformed_iterator& operator++();

        /**
         * @brief Post-increment operator
         *
         * @return The old value of the transformed_iterator
         */

        transformed_iterator operator++(int);

        /**
         * @brief Dereference operator
         *
         * If the current transformed_iterator has never been dereferenced, this
         * method updates the cached content by applying the suitable
         * transformations; otherwise, this operator only returns the cached
         * value.
         *
         * @return The value of the dereferenced transformed_iterator
         */

        reference operator*();

        /**
         * @brief Member access of pointer
         *
         * This method uses operator*() and has, therefore, the same behavior.
         *
         * @return A pointer to the member accessed
         */

        pointer operator->() { return &**this; }
    private:
        Iterator m_inner; ///< The inner iterator

        /**
         * @brief The parameters used for the transformation
         */

        transformed_parameters m_parameters;

        value_type m_content; ///< The current cached transformed value
        bool m_need_update;   ///< If m_content needs to be updated
    };

    /**
     * @brief Equality operator for transformed_parameters
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(
        const transformed_parameters& __lhs,
        const transformed_parameters& __rhs
    )
    {
        return
            (__lhs.angle == __rhs.angle) &&
            (__lhs.center == __rhs.center) &&
            (__lhs.roi == __rhs.roi) &&
            (__lhs.size == __rhs.size);
    }

    /**
     * @brief Inequality operator for transformed_parameters
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator!=(
        const transformed_parameters& __lhs,
        const transformed_parameters& __rhs
    )
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two transformed_parameters
     *
     * @param[in] __lhs The left hand side parameter
     * @param[in] __rhs The right hand side parameter
     */

    void swap(
        transformed_parameters& __lhs,
        transformed_parameters& __rhs
    ) noexcept;

    /**
     * @brief Equality operator for transformed_iterator
     *
     * @tparam Iterator The inner iterator used to get the input
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    template <class Iterator>
    bool operator==(
        const transformed_iterator<Iterator>& __lhs,
        const transformed_iterator<Iterator>& __rhs
    )
    {
        return
            (__lhs.m_inner == __rhs.m_inner) &&
            (__lhs.m_parameters == __rhs.m_parameters);
    }

    /**
     * @brief Inequality operator for transformed_iterator
     *
     * @tparam Iterator The inner iterator used to get the input
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    template <class Iterator>
    bool operator!=(
        const transformed_iterator<Iterator>& __lhs,
        const transformed_iterator<Iterator>& __rhs
    )
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two transformed_iterator
     *
     * @tparam Iterator The inner iterator used to get the input
     *
     * @param[in] __lhs The left hand side parameter
     * @param[in] __rhs The right hand side parameter
     */

    template <class Iterator>
    void swap(
        transformed_iterator<Iterator>& __lhs,
        transformed_iterator<Iterator>& __rhs
    );

    /**
     * @brief Pipe operator for transformed_iterator
     *
     * This operator aims to provides a convenient way to construct a
     * transformed_iterator.
     *
     * @tparam Iterator The inner iterator used to get the input
     *
     * @param[in] __lhs The inner iterator
     * @param[in] __rhs The parameters used for the transformation
     *
     * @return The transformed_iterator
     */

    template <class Iterator>
    transformed_iterator<Iterator> operator|(
        Iterator&& __lhs,
        transformed_parameters __rhs
    )
    {
        return
            transformed_iterator(
                std::forward<Iterator>(__lhs),
                std::move(__rhs)
            );
    }

    /**
     * @brief A constructor for transformed_parameters
     *
     * @param[in] __angle The angle used for the rotation
     * @param[in] __center The center used for the rotation
     * @param[in] __roi The region of interest
     * @param[in] __size The size used for the resizing
     *
     * @return The constructed transformed_parameters
     */

    inline transformed_parameters transformed(
        double __angle,
        cv::Point2f __center,
        cv::Rect __roi,
        cv::Size __size
    )
        { return transformed_parameters { __angle, __center, __roi, __size }; }
}

#include "transformed.ipp"

#endif // BRIDGE_ANALYZER_ITERATORS_TRANSFORMED_HPP
