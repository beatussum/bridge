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

#include "types/deal.hpp"
#include "core.hpp"

using namespace bridge::analyzer::types::deal;
using bridge::analyzer::core::to_string;

TEST(deal_unit_print_test, basic)
{
    using namespace bridge::analyzer::types::card::playing;

    deal_unit tested {
        card { color::club, rank::two },
        card { color::club, rank::three },
        card { color::club, rank::four },
        card { color::club, rank::five },
        card { color::club, rank::six },
        card { color::club, rank::seven },
        card { color::club, rank::eight },
        card { color::club, rank::nine },
        card { color::club, rank::ten },
        card { color::club, rank::jack },
        card { color::club, rank::queen },
        card { color::club, rank::king },
        card { color::club, rank::ace }
    };

    std::string_view expected =
        "deal_unit [ "
        "card { C2 }, "
        "card { C3 }, "
        "card { C4 }, "
        "card { C5 }, "
        "card { C6 }, "
        "card { C7 }, "
        "card { C8 }, "
        "card { C9 }, "
        "card { C10 }, "
        "card { CJ }, "
        "card { CQ }, "
        "card { CK }, "
        "card { CA } "
        "]";

    ASSERT_EQ(to_string(tested), expected);
}

TEST(deal_unit_print_test, empty)
{
    ASSERT_EQ(to_string(deal_unit {}), "deal_unit []");
}

TEST(deal_equal_test, equal)
{
    deal tested;
    ASSERT_EQ(tested, tested);
}

TEST(deal_print_test, empty)
{
    std::string_view expected =
        "deal { "
        "north = deal_unit [], "
        "west = deal_unit [], "
        "south = deal_unit [], "
        "east = deal_unit [] "
        "}";

    ASSERT_EQ(to_string(deal {}), expected);
}
