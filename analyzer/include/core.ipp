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


namespace bridge::analyzer::core
{
    template <class T>
    std::string to_string(const T& __value)
    {
        std::ostringstream ss;
        return (ss << __value).str();
    }

    template <class Ostream, class T>
    details::enable_iterable_formatted_output_function<Ostream, T>
    operator<<(Ostream&& __os, const T& __iterable)
    {
        __os << '[';

        if (__iterable.empty()) {
            __os << ']';
        } else {
            __os << ' ';

            auto end = --__iterable.cend();

            for (auto i = __iterable.cbegin(); i != end; ++i) {
                __os << *i << ", ";
            }

            __os << *end << " ]";
        }

        return __os;
    }
}
