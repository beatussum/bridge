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


namespace bridge::analyzer::types::card::playing
{
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

            default:
                __os << '?';
                break;
        }

        return __os;
    }

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, rank __value)
    {
        switch (__value) {
            case rank::two:
            case rank::three:
            case rank::four:
            case rank::five:
            case rank::six:
            case rank::seven:
            case rank::eight:
            case rank::nine:
            case rank::ten:
                __os << std::to_string(static_cast<int>(__value));
                break;

            case rank::jack:
                __os << 'J';
                break;

            case rank::queen:
                __os << 'Q';
                break;

            case rank::king:
                __os << 'K';
                break;

            case rank::ace:
                __os << 'A';
                break;

            default:
                __os << "(undefined)";
                break;
        }

        return __os;
    }
}