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


namespace bridge::analyzer::types
{
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

    template<class Ostream>
    Ostream&& operator<<(Ostream&& __os, const trick& __value)
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
