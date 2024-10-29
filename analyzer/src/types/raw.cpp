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


#include "types/raw/boxed.hpp"
#include "types/raw.hpp"
#include "types.hpp"

#include <opencv2/imgproc.hpp>

namespace bridge::analyzer::types::raw
{
    namespace
    {
        void add_to_uncounted_trick(
            uncounted::trick& __uncounted,
            positioning __pos,
            card::card __card
        )
        {
            switch (__pos) {
                case positioning::north:
                    __uncounted.north.push_back(std::move(__card));
                    break;

                case positioning::west:
                    __uncounted.west.push_back(std::move(__card));
                    break;

                case positioning::south:
                    __uncounted.south.push_back(std::move(__card));
                    break;

                case positioning::east:
                    __uncounted.east.push_back(std::move(__card));
                    break;

                default:
                    break;
            }
        }

        positioning get_positioning_from_center(
            const cv::Point2f& __center,
            cv::Point2f __point
        )
        {
            __point -= __center;

            bool x = cv::Point2f(1.f, 1.f).dot(__point) > 0.f;
            bool y = cv::Point2f(-1.f, 1.f).dot(__point) > 0.f;

            if (x && y) {
                return positioning::north;
            } else if (!x && y) {
                return positioning::west;
            } else if (!x && !y) {
                return positioning::south;
            } else {
                return positioning::east;
            }
        }

        cv::Point2f get_rect_center(const cv::Rect2f& __rect)
        {
            cv::Point2f ret = __rect.tl();

            ret.x += __rect.width / 2.f;
            ret.y += __rect.height / 2.f;

            return ret;
        }
    }

    counted::trick_unit count(const uncounted::trick_unit& __uncounted)
    {
        counted::trick_unit ret;

        for (card::card c : __uncounted) {
            ++ret.insert(card::counted_card { 0, std::move(c) }).first->n;
        }

        return ret;
    }

    uncounted::trick unbox(
        const cv::Point2f& __center,
        const boxed::trick& __boxed
    )
    {
        uncounted::trick ret;

        if (__boxed.size() == 1) {
            card::boxed_card c = __boxed.front();

            add_to_uncounted_trick(
                ret,

                get_positioning_from_center(
                    __center,
                    get_rect_center(c.box)
                ),

                std::move(c.c)
            );
        } else {
            std::vector<cv::Point2f> centers;

            centers.reserve(__boxed.size());

            for (const card::boxed_card& c : __boxed) {
                centers.push_back(get_rect_center(c.box));
            }

            cv::Point2f bounding_rect_center =
                get_rect_center(cv::boundingRect(centers));

            auto i = centers.cbegin();

            for (const card::boxed_card& c : __boxed) {
                add_to_uncounted_trick(
                    ret,
                    get_positioning_from_center(bounding_rect_center, *i),
                    c.c
                );

                ++i;
            }
        }

        return ret;
    }
}
