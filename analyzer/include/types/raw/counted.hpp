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


#ifndef BRIDGE_ANALYZER_TYPES_COUNTED_HPP
#define BRIDGE_ANALYZER_TYPES_COUNTED_HPP

#include "../card.hpp"
#include "core/boost.hpp"

#include <boost/unordered/unordered_set.hpp>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::types::raw::counted
 */

/**
 * @brief This namespace describes different types related to \ref trick
 *
 * The types defined is this namespace are related to their associated types in
 * \ref bridge::analyzer::types::trick. These types describe outputs of the
 * neural network.
 *
 * Unlike \ref bridge::analyzer::types::raw::uncounted, the types describes
 * in this namespace are counted.
 */

namespace bridge::analyzer::types::raw::counted
{
    /**
     * @brief The detail namespace of \ref bridge::analyzer::types::raw::counted
     *
     * @warning This namespace should never been used directly: it exists only
     * for implementation reason.
     */

    namespace details
    {
        /**
         * @brief A counted card
         *
         * This structure aims to provide an interface allowing to modify \ref n
         * even if the object is constant. Indeed, this structure is intended to
         * be used as key in an associative container; therefore, accessing to
         * its members is read-only. However, comparison and hashing is only
         * determined with \ref c and \ref n could be altered anyway.
         */

        struct counted_card : card::counted_card
        {
        public:
            /**
             * @brief Constructs a \ref counted_card from a
             * \ref card::counted_card
             *
             * This constructor aims to make \ref counted_card transparent.
             *
             * @param[in] __counted_card The \ref card::counted_card
             */

            constexpr counted_card(
                const card::counted_card& __counted_card
            ) noexcept
                : card::counted_card(__counted_card)
            {}
        public:
            /**
             * @brief Get the \ref n object as a mutable reference
             *
             * @return A mutable reference to \ref n
             */

            constexpr difference_type& get_n() const noexcept
                { return const_cast<difference_type&>(n); }
        };

        /**
         * @brief Equality operator for \ref counted_card
         *
         * @param[in] __lhs The left hand side operand
         * @param[in] __rhs The right hand side operand
         *
         * @return If \p __lhs is equal to \p __rhs
         */

        constexpr bool operator==(
            const counted_card& __lhs,
            const counted_card& __rhs
        ) noexcept
            { return __lhs.c == __rhs.c; }

        /**
         * @brief Inequality operator for \ref counted_card
         *
         * @param[in] __lhs The left hand side operand
         * @param[in] __rhs The right hand side operand
         *
         * @return If \p __lhs is different from \p __rhs
         */

        constexpr bool operator!=(
            const counted_card& __lhs,
            const counted_card& __rhs
        ) noexcept
            { return !(__lhs == __rhs); }

        /**
         * @brief Equality operator between \ref counted_card and
         * \ref card::card
         *
         * @param[in] __lhs The left hand side operand (the \ref counted_card)
         * @param[in] __rhs The right hand side operand (the \ref card::card)
         *
         * @return If \p __lhs is equal to \p __rhs
         */

        constexpr bool operator==(
            const counted_card& __lhs,
            const card::card& __rhs
        ) noexcept
            { return __lhs.c == __rhs; }

        /**
         * @brief Inequality operator between \ref counted_card and
         * \ref card::card
         *
         * @param[in] __lhs The left hand side operand (the \ref counted_card)
         * @param[in] __rhs The right hand side operand (the \ref card::card)
         *
         * @return If \p __lhs is different from \p __rhs
         */

        constexpr bool operator!=(
            const counted_card& __lhs,
            const card::card& __rhs
        ) noexcept
            { return !(__lhs == __rhs); }

        /**
         * @brief Equality operator between \ref counted_card and
         * \ref card::card
         *
         * @param[in] __lhs The left hand side operand (the \ref card::card)
         * @param[in] __rhs The right hand side operand (the \ref counted_card)
         *
         * @return If \p __lhs is equal to \p __rhs
         */

        constexpr bool operator==(
            const card::card& __lhs,
            const counted_card& __rhs
        ) noexcept
            { return __rhs == __lhs; }

        /**
         * @brief Inequality operator between \ref counted_card and
         * \ref card::card
         *
         * @param[in] __lhs The left hand side operand (the \ref card::card)
         * @param[in] __rhs The right hand side operand (the \ref counted_card)
         *
         * @return If \p __lhs is different from \p __rhs
         */

        constexpr bool operator!=(
            const card::card& __lhs,
            const counted_card& __rhs
        ) noexcept
            { return !(__lhs == __rhs); }

        /**
         * @brief Hashes a \ref counted_card
         *
         * @remark This function is an overload of a Boost-provided function.
         *
         * @param[in] __counted_card The \ref counted_card to hash
         * @return The hashed \ref counted_card
         */

        inline std::size_t hash_value(const counted_card& __counted_card)
            { return boost::hash<card::card>()(__counted_card.c); }
    }

    /**
     * @brief A trick unit
     */

    class trick_unit
        : public boost::unordered_set<
            details::counted_card,
            boost::hash<void>,
            std::equal_to<>
        >
    {
    public:
        using boost::unordered_set<
            details::counted_card,
            boost::hash<void>,
            std::equal_to<>
        >::unordered_set;

        /**
         * @brief Default constructor of \ref trick_unit
         */

        trick_unit() noexcept = default;

        /**
         * @brief Copy constructor of \ref trick_unit
         *
         * @param[in] __other The other \ref trick_unit to copy
         */

        trick_unit(const trick_unit& __other) = default;

        /**
         * @brief Move constructor of trick_unit
         *
         * @param[in] __other The other \ref trick_unit to move
         */

        trick_unit(trick_unit&& __other) = default;

        ~trick_unit() = default; ///< Destructor of \ref trick_unit
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref trick_unit
         */

        trick_unit& operator=(const trick_unit& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref trick_unit
         */

        trick_unit& operator=(trick_unit&& __rhs) noexcept = default;
    };

    /**
     * @brief A trick
     */

    struct trick
    {
        trick_unit north; ///< North's cards on the table
        trick_unit west;  ///< West's cards on the table
        trick_unit south; ///< South's cards on the table
        trick_unit east;  ///< East's cards on the table
    };

    /**
     * @brief Inserts a \ref trick_unit to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick_unit& __value);

    /**
     * @brief Equality operator for \ref trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const trick& __lhs, const trick& __rhs) noexcept
    {
        return
            (__lhs.north == __rhs.north) &&
            (__lhs.west == __rhs.west) &&
            (__lhs.south == __rhs.south) &&
            (__lhs.east == __rhs.east);
    }

    /**
     * @brief Inequality operator for \ref trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const trick& __lhs, const trick& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a \ref trick to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick& __value);
}

#include "counted.ipp"

#endif // BRIDGE_ANALYZER_TYPES_COUNTED_HPP
