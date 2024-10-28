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
     * @brief A trick unit
     */

    class trick_unit
        : public boost::unordered_set<
            card::counted_card,
            boost::hash<void>,
            std::equal_to<>
        >
    {
        template <class Ostream>
        friend constexpr Ostream&& operator<<(Ostream&&, const trick_unit&);
    private:
        /**
         * @brief The type of the base class
         */

        using base_type =
            boost::unordered_set<
                card::counted_card,
                boost::hash<void>,
                std::equal_to<>
            >;
    public:
        using base_type::unordered_set;

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
        using base_type::operator=;

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
    public:
        /**
         * @brief Addition assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return The assigned \ref trick_unit added with \p __rhs
         */

        trick_unit& operator+=(const trick_unit& __rhs);

        /**
         * @brief Substraction assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return The assigned \ref trick_unit subtracted by \p __rhs
         */

        trick_unit& operator-=(const trick_unit& __rhs);
    public:
        /**
         * @brief Unary plus operator
         *
         * @return An unchanged object
         */

        trick_unit operator+() const
            { return *this; }

        /**
         * @brief Unary minus operator
         *
         * @return An object with all items negated
         */

        trick_unit operator-() const;
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
     * @brief Adds two \ref trick_unit
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return The addition of \p __lhs and \p __rhs
     */

    trick_unit operator+(const trick_unit& __lhs, const trick_unit& __rhs);

    /**
     * @brief Substracts two \ref trick_unit
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return The substraction of \p __lhs by \p __rhs
     */

    inline trick_unit operator-(const trick_unit& __lhs, const trick_unit& __rhs)
        { return __lhs + -__rhs; }

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
