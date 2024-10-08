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


#ifndef BRIDGE_ANALYZER_TYPES_TRICK_HPP
#define BRIDGE_ANALYZER_TYPES_TRICK_HPP

#include "card/playing.hpp"
#include "metadata.hpp"

#include <array>

/**
 * @file
 * @brief This namespace describes the trick type and its associated types
 */

namespace bridge::analyzer::types
{
    enum struct positioning;

    /**
     * @brief An aggregate describing a trick unit
     */

    struct trick_unit
    {
        card::playing::card c; ///< The card played by the associated player
        positioning p;         ///< The positioning of the associated player
    };

    /**
     * @brief An aggregate describing a trick
     */

    struct trick
    {
        /**
         * @brief The four units composing the trick
         *
         * These units are stored in the order in which they were played.
         */

        std::array<trick_unit, 4> units;

        metadata m; ///< The metadata of the trick
    };

    /**
     * @brief Equality operator for trick_unit
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    constexpr bool operator==(
        const trick_unit& __lhs,
        const trick_unit& __rhs
    ) noexcept
        { return (__lhs.c == __rhs.c) && (__lhs.p == __rhs.p); }

    /**
     * @brief Inequality operator for trick_unit
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    constexpr bool operator!=(
        const trick_unit& __lhs,
        const trick_unit& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Equality operator for trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(const trick& __lhs, const trick& __rhs) noexcept
        { return __lhs.units == __rhs.units; }

    /**
     * @brief Inequality operator for trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(const trick& __lhs, const trick& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a trick_unit to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick_unit& __value)
    {
        __os
            << "trick_unit { card = "
            << __value.c
            << ", positioning = "
            << __value.p
            << " }";

        return __os;
    }

    /**
     * @brief Inserts a trick to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick& __value)
    {
        __os
            << "trick { first = "
            << __value.units[0]
            << ", second = "
            << __value.units[1]
            << ", third = "
            << __value.units[2]
            << ", fourth = "
            << __value.units[3]
            << " }";

        return __os;
    }
}

#endif // BRIDGE_ANALYZER_TYPES_TRICK_HPP
