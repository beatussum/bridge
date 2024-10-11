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


namespace bridge::analyzer::types::card::bidding
{
    constexpr level::level(underlying_type __level)
        : m_level(__level)
    {
        if ((__level < 1) || (__level > 7)) {
            throw std::domain_error("A level must be between 1 and 7");
        }
    }

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, color __value)
    {
        switch (__value) {
            case color::club:
                __os << 'C';
                break;

            case color::diamond:
                __os << 'D';
                break;

            case color::heart:
                __os << 'H';
                break;

            case color::spade:
                __os << 'S';
                break;

            case color::notrump:
                __os << 'N';
                break;

            default:
                __os << '?';
                break;
        }

        return __os;
    }

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value)
    {
        std::visit([&] (const auto& value) { __os << value; }, __value);
        return __os;
    }
}
