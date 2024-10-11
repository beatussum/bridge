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


#ifndef BRIDGE_ANALYZER_CORE_HPP
#define BRIDGE_ANALYZER_CORE_HPP

namespace bridge::analyzer::core
{
    /**
     * @brief Cast a type to std::string
     *
     * @tparam T The type of the value to cast
     * @param[in] __value The value to cast
     * @return A std::string representing the type
     */

    template <class T>
    std::string to_string(const T& __value);
}

#include "core.ipp"

#endif // BRIDGE_ANALYZER_CORE_HPP
