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


#include "core.hpp"

namespace bridge::analyzer::types::trick::raw
{
    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick_unit& __value)
    {
        using core::operator<<;

        __os << "trick_unit " << static_cast<std::vector<card::card>>(__value);
        return __os;
    }

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const trick& __value)
    {
        __os
            << "trick [ north = "
            << __value.north
            << ", west = "
            << __value.west
            << ", south = "
            << __value.south
            << ", east = "
            << __value.east
            << " ]";

        return __os;
    }
}
