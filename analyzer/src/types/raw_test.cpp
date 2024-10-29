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


#include "types/raw.hpp"
#include <gtest/gtest.h>

using namespace bridge::analyzer::types::card;
using namespace bridge::analyzer::types::raw;

TEST(count_test, basic)
{
    uncounted::trick input {
        uncounted::trick_unit {
            bidding::card_double {},
            bidding::card_double {}
        },

        uncounted::trick_unit {},
        uncounted::trick_unit { bidding::card_pass {} },
        uncounted::trick_unit { bidding::card_stop {} }
    };

    counted::trick expected {
        counted::trick_unit { counted_card { 2, bidding::card_double {} } },
        counted::trick_unit {},
        counted::trick_unit { counted_card { 1, bidding::card_pass {} } },
        counted::trick_unit { counted_card { 1, bidding::card_stop {} } }
    };

    ASSERT_EQ(count(input), expected);
}

TEST(unbox_test, basic)
{
    boxed::trick input {
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_double {} },
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_double {} },

        boxed_card { cv::Rect2f(-10.f, 0.f, 1.f, 1.f), bidding::card_pass {} },

        boxed_card {
            cv::Rect2f(-10.f, -10.f, 1.f, 1.f),
            bidding::card_double {}
        },

        boxed_card { cv::Rect2f(10.f, 5.f, 1.f, 1.f), bidding::card_stop {} },
        boxed_card { cv::Rect2f(10.f, 0.f, 1.f, 1.f), bidding::card_stop {} }
    };

    uncounted::trick expected {
        uncounted::trick_unit {
            bidding::card_double {},
            bidding::card_double {}
        },

        uncounted::trick_unit { bidding::card_pass {} },
        uncounted::trick_unit { bidding::card_double {} },

        uncounted::trick_unit {
            bidding::card_stop {},
            bidding::card_stop {}
        }
    };

    ASSERT_EQ(unbox(cv::Point2f(0.f, 0.f), input), expected);
}

TEST(unbox_test, one)
{
    boxed::trick input {
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_double {} }
    };

    uncounted::trick expected {
        uncounted::trick_unit { bidding::card_double {} },
        uncounted::trick_unit {},
        uncounted::trick_unit {},
        uncounted::trick_unit {}
    };

    ASSERT_EQ(unbox(cv::Point2f(0.f, 0.f), input), expected);
}

TEST(unbox_test, same)
{
    boxed::trick input {
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_double {} },
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_double {} },
        boxed_card { cv::Rect2f(0.f, 10.f, 1.f, 1.f), bidding::card_pass {} }
    };

    uncounted::trick expected {
        uncounted::trick_unit {
            bidding::card_double {},
            bidding::card_double {},
            bidding::card_pass {}
        },

        uncounted::trick_unit {},
        uncounted::trick_unit {},
        uncounted::trick_unit {}
    };

    ASSERT_EQ(unbox(cv::Point2f(0.f, 0.f), input), expected);
}
