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


#ifndef BRIDGE_ANALYZER_TYPES_RAW_BOXED_HPP
#define BRIDGE_ANALYZER_TYPES_RAW_BOXED_HPP

#include "../card.hpp"

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::types::raw::boxed
 */

/**
 * @brief This namespace describes different types related to \ref trick
 *
 * The type defined in this namespace is related to its associated type
 * \ref bridge::analyzer::types::trick::trick. These types describe the purest
 * output of the neural network.
 */

namespace bridge::analyzer::types::raw::boxed
{
    /**
     * @brief A trick
     */

    class trick : public std::vector<card::boxed_card>
    {
        template <class Ostream>
        friend constexpr Ostream&& operator<<(Ostream&&, const trick&);
    private:
        /**
         * @brief The type of the base class
         */

        using base_type = std::vector<card::boxed_card>;
    public:
        using base_type::vector;

        /**
         * @brief Default constructor of \ref trick
         */

        trick() noexcept = default;

        /**
         * @brief Copy constructor of \ref trick
         *
         * @param[in] __other The other \ref trick to copy
         */

        trick(const trick& __other) = default;

        /**
         * @brief Move constructor of trick
         *
         * @param[in] __other The other \ref trick to move
         */

        trick(trick&& __other) = default;

        ~trick() = default; ///< Destructor of \ref trick
    public:
        using base_type::operator=;

        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref trick
         */

        trick& operator=(const trick& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref trick
         */

        trick& operator=(trick&& __rhs) noexcept = default;
    };

    /**
     * @brief Inserts a \ref trick to an output stream
     *
     * @tparam Ostream The type of \p __os
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick& __value);
}

#include "boxed.ipp"

#endif // BRIDGE_ANALYZER_TYPES_RAW_BOXED_HPP
