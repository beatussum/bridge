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


#ifndef BRIDGE_ANALYZER_TYPES_CARD_HPP
#define BRIDGE_ANALYZER_TYPES_CARD_HPP

#include "card/bidding.hpp"
#include "card/playing.hpp"

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::types::card
 */

/**
 * @brief This namespace describes different card types
 */

namespace bridge::analyzer::types::card
{
    /**
     * @brief A variant type representing a bidding or playing card
     */

    class card : public std::variant<bidding::card, playing::card>
    {
    private:
        /**
         * @brief The type of the base class
         */

        using base_type = std::variant<bidding::card, playing::card>;
    public:
        using base_type::variant;

        /**
         * @brief Default constructor of \ref card
         */

        constexpr card() noexcept = default;

        /**
         * @brief Copy constructor of \ref card
         *
         * @param[in] __other The other \ref card to copy
         */

        constexpr card(const card& __other) = default;

        /**
         * @brief Move constructor of \ref card
         *
         * @param[in] __other The other \ref card to move
         */

        constexpr card(card&& __other) noexcept = default;

        ~card() = default; ///< Destructor of \ref card
    public:
        using base_type::operator=;

        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref card
         */

        constexpr card& operator=(const card& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref card
         */

        constexpr card& operator=(card&& __rhs) noexcept = default;
    };

    /**
     * @brief A counted card
     */

    struct counted_card
    {
    public:
        /**
         * @brief The type used to count \ref card
         */

        using difference_type = std::int_fast8_t;
    public:
        mutable difference_type n; ///< The number of card
        card c;                    ///< The type of card
    };

    /**
     * @brief Inserts a \ref card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value);

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
     * @brief Equality operator between a \ref counted_card and a \ref card
     *
     * @param[in] __lhs The left hand side operand (the \ref card)
     * @param[in] __rhs The right hand side operand (the \ref counted_card)
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(
        const card& __lhs,
        const counted_card& __rhs
    ) noexcept
        { return __lhs == __rhs.c; }

    /**
     * @brief Inequality operator between a \ref counted_card and a \ref card
     *
     * @param[in] __lhs The left hand side operand (the \ref card)
     * @param[in] __rhs The right hand side operand (the \ref counted_card)
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(
        const card& __lhs,
        const counted_card& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Equality operator between a \ref counted_card and a \ref card
     *
     * @param[in] __lhs The left hand side operand (the \ref counted_card)
     * @param[in] __rhs The right hand side operand (the \ref card)
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(
        const counted_card& __lhs,
        const card& __rhs
    ) noexcept
        { return __rhs == __lhs; }

    /**
     * @brief Inequality operator between a \ref counted_card and a \ref card
     *
     * @param[in] __lhs The left hand side operand (the \ref counted_card)
     * @param[in] __rhs The right hand side operand (the \ref card)
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(
        const counted_card& __lhs,
        const card& __rhs
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

    std::size_t hash_value(const counted_card& __counted_card)
        { return boost::hash<card>()(__counted_card.c); }

    /**
     * @brief Inserts a \ref counted_card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const counted_card& __value);
}

#include "card.ipp"

#endif // BRIDGE_ANALYZER_TYPES_CARD_HPP
