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
#include <gtest/gtest.h>

using namespace bridge::analyzer::types::raw::boxed;
using namespace bridge::analyzer::types::card;

TEST(print_test, trick)
{
    using bridge::analyzer::core::to_string;

    trick input {
        boxed_card { cv::Rect2f(0.f, 1.f, 2.f, 3.f), bidding::card_pass {} },
        boxed_card { cv::Rect2f(1.f, 2.f, 3.f, 4.f), bidding::card_pass {} }
    };

    std::string_view expected =
        "trick [ "
        "boxed_card { "
        "box = cv::Rect_<float> { x = 0, y = 1, width = 2, height = 3 }, "
        "card = card_pass {} "
        "}, "
        "boxed_card { "
        "box = cv::Rect_<float> { x = 1, y = 2, width = 3, height = 4 }, "
        "card = card_pass {} "
        "} "
        "]";

    ASSERT_EQ(to_string(input), expected);
}
