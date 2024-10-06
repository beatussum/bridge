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

class card_bid_less_test
    : public testing::TestWithParam<std::pair<card_bid, card_bid>>
{};

TEST_P(card_bid_less_test, less)
{
    const auto& [first, second] = GetParam();

    ASSERT_NE(first, second);
    ASSERT_LT(first, second);
    ASSERT_GT(second, first);
}

INSTANTIATE_TEST_SUITE_P(
    different_color,
    card_bid_less_test,

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
    card_bid_less_test,

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

class card_bid_equal_test
    : public testing::TestWithParam<std::pair<card_bid, card_bid>>
{};

TEST_P(card_bid_equal_test, equal)
{
    const auto& [lhs, rhs] = GetParam();
    ASSERT_EQ(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    equal,
    card_bid_equal_test,

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
