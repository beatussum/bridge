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


#include "mappers.hpp"

namespace bridge::analyzer::mappers
{
    namespace
    {
        void keep_positive(types::raw::counted::trick_unit& __counted)
        {
            for (const types::card::counted_card& c : __counted) {
                if (c.n <= 0) {
                    __counted.erase(c);
                }
            }
        }
    }

    void swap(box& __lhs, box& __rhs) noexcept
    {
        using std::swap;

        swap(__lhs.m_confidence, __rhs.m_confidence);
        swap(__lhs.m_mapper, __rhs.m_mapper);
        swap(__lhs.m_size, __rhs.m_size);
    }

    cv::Mat forward::operator()(const cv::Mat& __input)
    {
        m_net.setInput(__input);
        return m_net.forward();
    }

    types::raw::counted::trick positive::operator()(
        types::raw::counted::trick __counted
    ) const
    {
        keep_positive(__counted.north);
        keep_positive(__counted.west);
        keep_positive(__counted.south);
        keep_positive(__counted.east);

        return __counted;
    }

    void swap(unbox& __lhs, unbox& __rhs) noexcept
    {
        using std::swap;
        swap(__lhs.m_center, __rhs.m_center);
    }
}
