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


#ifndef BRIDGE_ANALYZER_TYPES_TRICK_RAW_HPP
#define BRIDGE_ANALYZER_TYPES_TRICK_RAW_HPP

#include "../card.hpp"
#include <vector>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::types::trick::raw
 */

/**
 * @brief This namespace describes different types related to \ref trick
 *
 * The types defined is this namespace are related to their associated types in
 * \ref bridge::analyzer::types::trick. These types describe outputs of the
 * neural network.
 */

namespace bridge::analyzer::types::trick::raw
{
    /**
     * @brief A trick unit
     */

    class trick_unit : public std::vector<card::card>
    {
    public:
        using std::vector<card::card>::vector;

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

#include "raw.ipp"

#endif // BRIDGE_ANALYZER_TYPES_TRICK_RAW_HPP
