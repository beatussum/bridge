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


#ifndef BRIDGE_ANALYZER_TYPES_DEAL_HPP
#define BRIDGE_ANALYZER_TYPES_DEAL_HPP

#include "card/playing.hpp"
#include "core.hpp"
#include "metadata.hpp"

#include <vector>

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::types::deal
 */

/**
 * @brief This namespace describes the deal type and its associated types
 */

namespace bridge::analyzer::types::deal
{
    /**
     * @brief A deal unit
     */

    class deal_unit : public std::vector<card::playing::card>
    {
    public:
        using std::vector<card::playing::card>::vector;

        /**
         * @brief Default constructor of \ref deal_unit
         */

        deal_unit() noexcept = default;

        /**
         * @brief Copy constructor of \ref deal_unit
         *
         * @param[in] __other The other \ref deal_unit to copy
         */

        deal_unit(const deal_unit& __other) = default;

        /**
         * @brief Move constructor of \ref deal_unit
         *
         * @param[in] __other The other \ref deal_unit to move
         */

        deal_unit(deal_unit&& __other) = default;

        ~deal_unit() = default; ///< Destructor of \ref deal_unit
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref deal_unit
         */

        deal_unit& operator=(const deal_unit& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref deal_unit
         */

        deal_unit& operator=(deal_unit&& __rhs) noexcept = default;
    };

    /**
     * @brief An aggregate describing a deal
     */

    struct deal
    {
        deal_unit north; ///< The deal unit of the north player
        deal_unit west;  ///< The deal unit of the west player
        deal_unit south; ///< The deal unit of the south player
        deal_unit east;  ///< The deal unit of the north player

        metadata::metadata m; ///< The \ref metadata of the deal
    };

    /**
     * @brief Inserts a \ref deal_unit to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const deal_unit& __value);

    /**
     * @brief Equality operator for \ref deal
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const deal& __lhs, const deal& __rhs) noexcept
    {
        return
            (__lhs.north == __rhs.north) &&
            (__lhs.west == __rhs.west) &&
            (__lhs.south == __rhs.south) &&
            (__lhs.east == __rhs.east);
    }

    /**
     * @brief Inequality operator for \ref deal
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const deal& __lhs, const deal& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a \ref deal to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const deal& __value);
}

#include "deal.ipp"

#endif // BRIDGE_ANALYZER_TYPES_DEAL_HPP
