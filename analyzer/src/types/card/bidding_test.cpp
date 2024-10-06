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


#include <gtest/gtest.h>
#include "types/card/bidding.hpp"

using namespace bridge::analyzer::types::card::bidding;

class less_test
    : public testing::TestWithParam<std::pair<card_bid, card_bid>>
{};

TEST_P(less_test, less)
{
    std::pair tested = GetParam();

    ASSERT_NE(tested.first, tested.second);
    ASSERT_LT(tested.first, tested.second);
    ASSERT_GT(tested.second, tested.first);
}

INSTANTIATE_TEST_SUITE_P(
    different_color,
    less_test,

    testing::Values(
        std::make_pair(
            card_bid { color::club, 2 },
            card_bid { color::notrump, 2 }
        ),

        std::make_pair(
            card_bid { color::diamond, 5 },
            card_bid { color::heart, 5 }
        )
    )
);

INSTANTIATE_TEST_SUITE_P(
    same_color,
    less_test,

    testing::Values(
        std::make_pair(
            card_bid { color::club, 2 },
            card_bid { color::club, 3 }
        ),

        std::make_pair(
            card_bid { color::diamond, 5 },
            card_bid { color::diamond, 7 }
        )
    )
);

class equal_test
    : public testing::TestWithParam<std::pair<card_bid, card_bid>>
{};

TEST_P(equal_test, equal)
{
    std::pair tested = GetParam();
    ASSERT_EQ(tested.first, tested.second);
}

INSTANTIATE_TEST_SUITE_P(
    equal,
    equal_test,

    testing::Values(
        std::make_pair(
            card_bid { color::club, 2 },
            card_bid { color::club, 2 }
        ),

        std::make_pair(
            card_bid { color::diamond, 5 },
            card_bid { color::diamond, 5 }
        )
    )
);
