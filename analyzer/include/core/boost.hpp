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


#ifndef BRIDGE_ANALYZER_CORE_BOOST_HPP
#define BRIDGE_ANALYZER_CORE_BOOST_HPP

#include <boost/container_hash/hash.hpp>

/**
 * @file
 * @brief The base header of \ref boost for bridge
 */

/**
 * @brief Some overloads and specializations of Boost entities
 */

namespace boost
{
    /**
     * @brief A transparent hasher using Boost-provided hash library
     */

    template <>
    struct hash<void>
    {
    public:
        /**
         * @brief Sets the hasher as transparent
         */

        using is_transparent = std::true_type;
    public:
        /**
         * @brief Hash the given value
         *
         * This function transparently calls the right `hash_value()` overload
         * corresponding to the given type using ADL.
         *
         * @tparam U The type of the value to hash
         * @param[in] __value The value to hash
         *
         * @return A hashed \p __value
         */

        template<class U>
        std::size_t operator()(U&& __value) const
            { return hash_value(std::forward<U>(__value)); }
    };
}

#endif // BRIDGE_ANALYZER_CORE_BOOST_HPP
