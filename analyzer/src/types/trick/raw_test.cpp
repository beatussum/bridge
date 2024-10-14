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


#include "types/trick/raw.hpp"
#include <gtest/gtest.h>

using namespace bridge::analyzer::types::trick::raw;
using namespace bridge::analyzer::types::card;
using bridge::analyzer::core::to_string;

TEST(print_test, trick_unit)
{
    trick_unit input {
        playing::card { playing::color::club, playing::rank::ace },
        bidding::card_pass {},
        bidding::card_double {},
        bidding::card_bid { bidding::color::diamond, bidding::level(5) }
    };

    std::string_view expected =
        "trick_unit [ "
        "card { CA }, "
        "card_pass {}, "
        "card_redouble {}, "
        "card_bid { D5 } "
        "]";

    ASSERT_EQ(to_string(input), expected);
}

TEST(print_test, trick)
{
    trick input {
        trick_unit {
            playing::card { playing::color::club, playing::rank::ace },
            bidding::card_pass {},
            bidding::card_double {},
            bidding::card_bid { bidding::color::diamond, bidding::level(5) }
        },

        trick_unit {
            playing::card { playing::color::diamond, playing::rank::ace },
            bidding::card_pass {},
            bidding::card_double {},
            bidding::card_bid { bidding::color::club, bidding::level(6) }
        },

        trick_unit {
            playing::card { playing::color::heart, playing::rank::ace },
            bidding::card_pass {},
            bidding::card_double {},
            bidding::card_bid { bidding::color::diamond, bidding::level(6) }
        },

        trick_unit {
            playing::card { playing::color::spade, playing::rank::ace },
            bidding::card_pass {},
            bidding::card_double {},
            bidding::card_bid { bidding::color::diamond, bidding::level(6) }
        }
    };

    std::string_view expected =
        "trick [ "
        "north = trick_unit [ "
        "card { CA }, "
        "card_pass {}, "
        "card_redouble {}, "
        "card_bid { D5 } "
        "], "
        "west = trick_unit [ "
        "card { DA }, "
        "card_pass {}, "
        "card_redouble {}, "
        "card_bid { C6 } "
        "], "
        "south = trick_unit [ "
        "card { HA }, "
        "card_pass {}, "
        "card_redouble {}, "
        "card_bid { D6 } "
        "], "
        "east = trick_unit [ "
        "card { SA }, "
        "card_pass {}, "
        "card_redouble {}, "
        "card_bid { D6 } "
        "] "
        "]";

    ASSERT_EQ(to_string(input), expected);
}
