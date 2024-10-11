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
 * @brief The base header of the namespace bridge::analyzer::types::card
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
    public:
        using std::variant<bidding::card, playing::card>::variant;

        constexpr card() noexcept = default; ///< Default constructor of card

        /**
         * @brief Copy constructor of card
         *
         * @param[in] __other The other card to copy
         */

        constexpr card(const card& __other) = default;

        /**
         * @brief Move constructor of card
         *
         * @param[in] __other The other card to move
         */

        constexpr card(card&& __other) noexcept = default;

        ~card() = default; ///< Destructor of card
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned card
         */

        constexpr card& operator=(const card& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned card
         */

        constexpr card& operator=(card&& __rhs) noexcept = default;
    };

    /**
     * @brief Inserts a card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value);
}

#include "card.ipp"

#endif // BRIDGE_ANALYZER_TYPES_CARD_HPP
