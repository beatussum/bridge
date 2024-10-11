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


namespace bridge::analyzer::types::deal
{
    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const deal_unit& __value)
    {
        __os << "deal_unit [";

        if (__value.empty()) {
            __os << ']';
        } else {
            __os << ' ';

            auto end = __value.cend() - 1;

            for (auto i = __value.cbegin(); i < end; ++i) {
                __os << *i << ", ";
            }

            __os << __value.back() << " ]";
        }

        return __os;
    }

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const deal& __value)
    {
        __os
            << "deal { north = "
            << __value.north
            << ", west = "
            << __value.west
            << ", south = "
            << __value.south
            << ", east = "
            << __value.east
            << " }";

        return __os;
    }
}
