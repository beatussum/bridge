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
    Ostream&& operator<<(Ostream&& __os, const player& __value)
    {
        __os
            << "player { first_name = "
            << __value.first_name
            << ", last_name = "
            << __value.last_name
            << " }";

        return __os;
    }

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, phase __value)
    {
        switch (__value) {
            case phase::bidding:
                __os << "bidding";
                break;

            case phase::card:
                __os << "card";
                break;

            default:
                __os << "(undefined)";
                break;
        }

        return __os;
    }

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, positioning __value)
    {
        switch (__value) {
            case positioning::north:
                __os << "north";
                break;

            case positioning::west:
                __os << "west";
                break;

            case positioning::south:
                __os << "south";
                break;

            case positioning::east:
                __os << "east";
                break;

            case positioning::none:
                __os << "none";
                break;

            default:
                __os << "(undefined)";
                break;
        }

        return __os;
    }

    template <class T>
    std::string to_string(const T& __value)
    {
        std::ostringstream ss;
        return (ss << __value).str();
    }
}