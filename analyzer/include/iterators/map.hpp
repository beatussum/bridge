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


#ifndef BRIDGE_ANALYZER_ITERATORS_MAP_HPP
#define BRIDGE_ANALYZER_ITERATORS_MAP_HPP

#include "core.hpp"

#include <functional>
#include <optional>

/**
 * @file
 *
 * @brief The base header of the namespace \ref bridge::analyzer::iterators::map
 */

/**
 * @brief This namespace describes different utilities related to \ref map
 */

namespace bridge::analyzer::iterators::map
{
    /**
     * @brief The map parameters used by \ref map_iterator
     *
     * @tparam Mapper The type of the mapper object
     */

    template <class Mapper>
    struct map_parameters
    {
        /**
         * @brief The mapper
         *
         * It is used to map the input values.
         */

        std::function<Mapper> mapper;
    };

    /**
     * @brief Class template argument deduction for \ref map_parameters
     *
     * This deduction handles function pointer.
     *
     * @tparam Output The output type
     * @tparam Input The input type
     */

    template <class Output, class Input>
    map_parameters(Output (*) (Input)) -> map_parameters<Output(Input)>;

    /**
     * @brief Class template argument deduction for \ref map_parameters
     *
     * This deduction handles callable types.
     *
     * @tparam Mapper The type of the mapper
     */

    template <class Mapper>
    map_parameters(Mapper)
        -> map_parameters<
            core::function_signature_t<decltype(&Mapper::operator())>
        >;

    /**
     * @brief An iterator allowing to map input values with a given tranformer
     *
     * @tparam Iterator The type of the inner iterator
     * @tparam Mapper The type of the mapper
     */

    template <class Iterator, class Mapper>
    class map_iterator;

    /**
     * @brief An iterator allowing to map input values with a given tranformer
     *
     * @tparam Iterator The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     */

    template <class Iterator, class Output, class Input>
    class map_iterator<Iterator, Output(Input)>
    {
        template <class It, class O, class In>
        friend constexpr bool operator==(
            const map_iterator<It, O(In)>&,
            const map_iterator<It, O(In)>&
        );

        template <class It, class O, class In>
        friend constexpr bool operator!=(
            const map_iterator<It, O(In)>&,
            const map_iterator<It, O(In)>&
        );

        template <class It, class O, class In>
        friend void swap(map_iterator<It, O(In)>&, map_iterator<It, O(In)>&);
    public:
        /**
         * @brief The type of the value returned by the difference between two
         * \ref map_iterator
         */

        using difference_type =
            typename std::iterator_traits<Iterator>::difference_type;

        /**
         * @brief The type of the pointer pointing to the value referenced by
         * the \ref map_iterator
         */

        using pointer = std::add_pointer_t<Output>;

        /**
         * @brief The type of the pointer referencing to the value referenced by
         * the \ref map_iterator
         */

        using reference = std::add_lvalue_reference_t<Output>;

        /**
         * @brief The type of the value referenced by the \ref map_iterator
         */

        using value_type = Output;

        /**
         * @brief The iterator category of the \ref map_iterator
         */

        using iterator_category = std::forward_iterator_tag;

        static_assert(
            std::conjunction_v<
                std::is_convertible<
                    typename std::iterator_traits<Iterator>::pointer,
                    std::add_pointer_t<Input>
                >,

                std::is_convertible<
                    typename std::iterator_traits<Iterator>::reference,
                    std::add_lvalue_reference_t<Input>
                >,

                std::is_convertible<
                    typename std::iterator_traits<Iterator>::value_type,
                    Input
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
         * @brief Default constructor of \ref map_iterator
         */

        constexpr map_iterator() = default;

        /**
         * @brief Destructor of \ref map_iterator
         */

        ~map_iterator() noexcept = default;

        /**
         * @brief Copy constructor of \ref map_iterator
         *
         * @param[in] __other The other \ref map_iterator to copy
         */

        constexpr map_iterator(const map_iterator& __other) = default;

        /**
         * @brief Move constructor of \ref map_iterator
         *
         * @param[in] __other The other \ref map_iterator to move
         */

        constexpr map_iterator(map_iterator&& __other) = default;

        /**
         * @brief Constructs a \ref map_iterator with its given parameters
         *
         * @param[in] __inner The inner iterator
         * @param[in] __parameters The parameters used for the mapping
         */

        constexpr map_iterator(
            Iterator&& __inner,
            map_parameters<Output(Input)> __parameters
        )
            : m_inner(std::forward<Iterator>(__inner))
            , m_parameters(std::move(__parameters))
            , m_cached()
        {}

        /**
         * @overload
         *
         * @brief Constructs a \ref map_iterator with its given parameters
         *
         * @tparam Mapper The type of the mapper
         * @param[in] __inner The inner iterator
         * @param[in] __mapper The mapper (see \ref map_parameters::mapper)
         */

        template <class Mapper>
        constexpr map_iterator(Iterator&& __inner, Mapper&& __mapper)
            : map_iterator(
                std::forward<Iterator>(__inner),
                map_parameters { std::forward<Mapper>(__mapper) }
            )
        {}
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref map_iterator
         */

        constexpr map_iterator& operator=(const map_iterator& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref map_iterator
         */

        constexpr map_iterator& operator=(map_iterator&& __rhs) = default;
    public:
        /**
         * @brief Pre-increment operator
         *
         * @return The new value of the \ref map_iterator
         */

        constexpr map_iterator& operator++();

        /**
         * @brief Post-increment operator
         *
         * @return The old value of the \ref map_iterator
         */

        constexpr map_iterator operator++(int);

        /**
         * @brief Dereference operator
         *
         * If the current \ref map_iterator has never been dereferenced, this
         * method updates the cached content by applying the suitable mapping;
         * otherwise, this operator only returns the cached value.
         *
         * @return The value of the dereferenced \ref map_iterator
         */

        constexpr reference operator*();

        /**
         * @brief Member access of pointer
         *
         * This method uses \ref operator*() and has, therefore, the same
         * behavior.
         *
         * @return A pointer to the member accessed
         */

        constexpr pointer operator->() { return &**this; }
    private:
        Iterator m_inner; ///< The inner iterator

        /**
         * @brief The parameters used for the mapping
         */

        map_parameters<Output(Input)> m_parameters;

        std::optional<Output> m_cached; ///< The cached last dereferenced value
    };

    /**
     * @brief Class template argument deduction for \ref map_iterator
     *
     * This deduction handles \ref map_parameters.
     *
     * @tparam The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     */

    template <class Iterator, class Output, class Input>
    map_iterator(Iterator, map_parameters<Output(Input)>)
        -> map_iterator<Iterator, Output(Input)>;

    /**
     * @brief Class template argument deduction for \ref map_iterator
     *
     * This deduction handles function pointer.
     *
     * @tparam The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     */

    template <class Iterator, class Output, class Input>
    map_iterator(Iterator, Output (*) (Input))
        -> map_iterator<Iterator, Output(Input)>;

    /**
     * @brief Class template argument deduction for \ref map_iterator
     *
     * This deduction handles callable types.
     *
     * @tparam The type of the inner iterator
     * @tparam Mapper The type of the mapper
     */

    template <class Iterator, class Mapper>
    map_iterator(Iterator, Mapper)
        -> map_iterator<
            Iterator,
            core::function_signature_t<decltype(&Mapper::operator())>
        >;

    /**
     * @brief Equality operator for \ref map_parameters
     *
     * @tparam Mapper The type of the mapper
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    template <class Mapper>
    constexpr bool operator==(
        const map_parameters<Mapper>& __lhs,
        const map_parameters<Mapper>& __rhs
    )
        { return __lhs.mapper == __rhs.mapper; }

    /**
     * @brief Inequality operator for \ref map_parameters
     *
     * @tparam Mapper The type of the mapper
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    template <class Mapper>
    constexpr bool operator!=(
        const map_parameters<Mapper>& __lhs,
        const map_parameters<Mapper>& __rhs
    )
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref map_parameters
     *
     * @tparam Mapper The type of the mapper
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    template <class Mapper>
    void swap(map_parameters<Mapper>& __lhs, map_parameters<Mapper>& __rhs)
        { swap(__lhs.mapper, __rhs.mapper); }

    /**
     * @brief Equality operator for \ref map_iterator
     *
     * @tparam Mapper The type of the mapper
     * @tparam Output The output type
     * @tparam Input The input type
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    template <class Iterator, class Output, class Input>
    constexpr bool operator==(
        const map_iterator<Iterator, Output(Input)>& __lhs,
        const map_iterator<Iterator, Output(Input)>& __rhs
    )
    {
        return
            (__lhs.m_inner == __rhs.m_inner) &&
            (__lhs.m_parameters == __rhs.m_parameters);
    }

    /**
     * @brief Inequality operator for \ref map_iterator
     *
     * @tparam Iterator The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    template <class Iterator, class Output, class Input>
    constexpr bool operator!=(
        const map_iterator<Iterator, Output(Input)>& __lhs,
        const map_iterator<Iterator, Output(Input)>& __rhs
    )
        { return !(__lhs == __rhs); }

    /**
     * @brief Swaps two \ref map_iterator
     *
     * @tparam Iterator The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     *
     * @param[in, out] __lhs The left hand side parameter
     * @param[in, out] __rhs The right hand side parameter
     */

    template <class Iterator, class Output, class Input>
    void swap(
        map_iterator<Iterator, Output(Input)>& __lhs,
        map_iterator<Iterator, Output(Input)>& __rhs
    );

    /**
     * @brief Constructs a \ref map_parameters
     *
     * @tparam Mapper The type of the mapper
     * @param[in] __mapper The mapper to use
     *
     * @return The constructed \ref map_parameters
     */

    template <class Mapper>
    auto map(Mapper&& __mapper)
        { return map_parameters { std::forward<Mapper>(__mapper) }; }

    /**
     * @brief Pipe operator for \ref map_iterator
     *
     * This operator aims to provides a convenient way to construct a
     * \ref map_iterator.
     *
     * @tparam Iterator The type of the inner iterator
     * @tparam Output The output type
     * @tparam Input The input type
     *
     * @param[in] __lhs The inner iterator
     * @param[in] __rhs The parameters used for the mapping
     *
     * @return The \ref map_iterator
     */

    template <class Iterator, class Output, class Input>
    constexpr map_iterator<Iterator, Output(Input)> operator|(
        Iterator&& __lhs,
        map_parameters<Output(Input)> __rhs
    )
    { return map_iterator(std::forward<Iterator>(__lhs), std::move(__rhs)); }
}

#include "map.ipp"

#endif // BRIDGE_ANALYZER_ITERATORS_MAP_HPP
