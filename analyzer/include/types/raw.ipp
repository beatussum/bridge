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


#include <opencv2/core/mat.hpp>

namespace bridge::analyzer::types::raw
{
    template <class Mapper>
    boxed::trick box(
        float __confidence,
        const Mapper& __mapper,
        const cv::Size2f& __size,
        const cv::Mat& __mat
    )
    {
        boxed::trick ret;

        cv::MatSize size = __mat.size;

        for (int k = 0; k != size[2]; ++k) {
            auto m = std::make_pair<int, float>(-1, -1.f);

            for (int j = 4; j != size[1]; ++j) {
                auto current = __mat.at<float>(0, j, k);

                if (current > m.second) {
                    m = std::make_pair(j, current);
                }
            }

            if (m.second > __confidence) {
                ret.push_back(
                    card::boxed_card {
                        cv::Rect2f(
                            __mat.at<float>(0, 0, k) * __size.width,
                            __mat.at<float>(0, 1, k) * __size.height,
                            __mat.at<float>(0, 2, k) * __size.width,
                            __mat.at<float>(0, 3, k) * __size.height
                        ),

                        __mapper(m.first - 4)
                    }
                );
            }
        }

        return ret;
    }
}
