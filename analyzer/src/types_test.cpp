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


#include "types.hpp"
#include <gtest/gtest.h>

using namespace bridge::analyzer::types;
using bridge::analyzer::core::to_string;

TEST(print_test, auction)
{
    auction input {
        positioning::east,

        std::vector<card::bidding::card> {
            card::bidding::card_double {},
            card::bidding::card_pass {}
        },

        metadata::metadata()
    };

    std::string_view expected =
        "auction { "
        "first_player = east, "
        "bidding_card = [ "
        "card_redouble {}, "
        "card_pass {} "
        "] "
        "}";

    ASSERT_EQ(to_string(input), expected);
}
