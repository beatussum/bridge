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


#include "types/raw/counted.hpp"

namespace bridge::analyzer::types::raw::counted
{
    trick_unit& trick_unit::operator+=(const trick_unit& __rhs)
        { return *this = *this + __rhs; }

    trick_unit& trick_unit::operator-=(const trick_unit& __rhs)
        { return *this = *this - __rhs; }

    trick_unit trick_unit::operator-() const
    {
        trick_unit ret;

        for (const card::counted_card& c : *this) {
            ret.insert(-c);
        }

        return ret;
    }

    trick_unit operator+(const trick_unit& __lhs, const trick_unit& __rhs)
    {
        trick_unit ret = __lhs;

        for (const card::counted_card& c : __rhs) {
            if (!ret.insert(c).second) {
                ret.find(c)->n += c.n;
            }
        }

        return ret;
    }

    trick& trick::operator+=(const trick& __rhs)
        { return *this = *this + __rhs; }

    trick& trick::operator-=(const trick& __rhs)
        { return *this = *this - __rhs; }
}
