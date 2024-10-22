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


#include "mappers/transform.hpp"

namespace bridge::analyzer::mappers::transform
{
    cv::Mat transform::operator()(const cv::Mat& __input)
    {
        cv::Mat ret;

        cv::warpAffine(
            __input,
            ret,
            cv::getRotationMatrix2D(m_center, m_angle, 1.),
            __input.size()
        );

        ret = cv::Mat(ret, m_roi);
        cv::resize(ret, ret, m_size);

        return ret;
    }

    void swap(transform& __lhs, transform& __rhs) noexcept
    {
        using std::swap;

        swap(__lhs.m_angle, __rhs.m_angle);
        swap(__lhs.m_center, __rhs.m_center);
        swap(__lhs.m_roi, __rhs.m_roi);
        swap(__lhs.m_size, __rhs.m_size);
    }
}
