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
        constexpr types::card::card bid_mapper(int __id)
        {
            using namespace types::card::bidding;

            switch (__id) {
                case 28:
                    return card_pass {};

                case 29:
                    return card_double {};

                case 30:
                    return card_redouble {};

                case 31:
                case 32:
                    return types::card::card {};

                default:
                    return
                        card_bid {
                            static_cast<color>(__id % 4),
                            level(static_cast<level::underlying_type>(__id / 4))
                        };
            }
        }

        void keep_positive(types::raw::counted::trick_unit& __counted)
        {
            for (const types::card::counted_card& c : __counted) {
                if (c.n <= 0) {
                    __counted.erase(c);
                }
            }
        }

        constexpr types::card::card play_mapper(int __id) noexcept
        {
            using namespace types::card::playing;

            card ret {};

            ret.c = static_cast<color>(__id % 4);

            switch (__id /= 4) {
                case 0:
                    ret.r = rank::ten;
                    break;

                case 9:
                    ret.r = rank::ace;
                    break;

                case 10:
                    ret.r = rank::jack;
                    break;

                case 11:
                    ret.r = rank::king;
                    break;

                case 12:
                    ret.r = rank::queen;
                    break;

                default:
                    ret.r = static_cast<rank>(__id + 1);
                    break;
            }

            return ret;
        }
    }

    void details::swap(box& __lhs, box& __rhs) noexcept
    {
        using std::swap;

        swap(__lhs.m_confidence, __rhs.m_confidence);
        swap(__lhs.m_mapper, __rhs.m_mapper);
        swap(__lhs.m_size, __rhs.m_size);
    }

    bid::bid(float __confidence)
        : box(__confidence, &bid_mapper, cv::Size2f(640.f, 640.f))
    {}

    cv::Mat forward::operator()(const cv::Mat& __input)
    {
        m_net.setInput(__input);
        return m_net.forward();
    }

    play::play(float __confidence)
        : box(__confidence, &play_mapper, cv::Size2f(416.f, 416.f))
    {}

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
