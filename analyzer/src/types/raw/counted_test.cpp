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


#include "types/raw/counted.hpp"
#include <gtest/gtest.h>

using namespace bridge::analyzer::types::raw::counted;
using namespace bridge::analyzer::types::card;
using bridge::analyzer::core::to_string;

TEST(trick_unit_test, unary_minus)
{
    trick_unit input { counted_card { 1, bidding::card_pass {} } };
    trick_unit expected { counted_card { -1, bidding::card_pass {} } };

    ASSERT_EQ(-input, expected);
}

TEST(trick_unit_substraction_test, lhs)
{
    trick_unit lhs { counted_card { 1, bidding::card_pass {} } };
    trick_unit rhs {};

    trick_unit expected { counted_card { 1, bidding::card_pass {} } };

    ASSERT_EQ(lhs - rhs, expected);
}

TEST(trick_unit_substraction_test, same)
{
    trick_unit lhs { counted_card { 1, bidding::card_pass {} } };
    trick_unit rhs { counted_card { 1, bidding::card_pass {} } };

    trick_unit expected { counted_card { 0, bidding::card_pass {} } };

    ASSERT_EQ(lhs - rhs, expected);
}

TEST(trick_unit_substraction_test, rhs)
{
    trick_unit lhs {};
    trick_unit rhs { counted_card { 1, bidding::card_pass {} } };

    trick_unit expected { counted_card { -1, bidding::card_pass {} } };

    ASSERT_EQ(lhs - rhs, expected);
}

TEST(print_test, trick_unit)
{
    trick_unit input {
        counted_card {
            1,
            playing::card { playing::color::club, playing::rank::ace }
        },

        counted_card { 3, bidding::card_pass {} },
        counted_card { 0, bidding::card_double {} },

        counted_card {
            5,
            bidding::card_bid { bidding::color::diamond, bidding::level(5) }
        }
    };

    std::string_view expected =
        "trick_unit [ "
        "counted_card { n = 1, card = card { CA } }, "
        "counted_card { n = 5, card = card_bid { D5 } }, "
        "counted_card { n = 3, card = card_pass {} }, "
        "counted_card { n = 0, card = card_redouble {} } "
        "]";

    ASSERT_EQ(to_string(input), expected);
}

TEST(print_test, trick)
{
    trick input {
        trick_unit {
            counted_card {
                1,
                playing::card { playing::color::club, playing::rank::ace }
            },

            counted_card { 3, bidding::card_pass {} },
            counted_card { 0, bidding::card_double {} },

            counted_card {
                5,
                bidding::card_bid { bidding::color::diamond, bidding::level(5) }
            }
        },

        trick_unit {
            counted_card {
                2,
                playing::card { playing::color::club, playing::rank::ace }
            },

            counted_card { 4, bidding::card_pass {} },
            counted_card { 1, bidding::card_double {} },

            counted_card {
                6,
                bidding::card_bid { bidding::color::diamond, bidding::level(5) }
            }
        },

        trick_unit {
            counted_card {
                5,
                playing::card { playing::color::club, playing::rank::ace }
            },

            counted_card { 7, bidding::card_pass {} },
            counted_card { 1, bidding::card_double {} },

            counted_card {
                9,
                bidding::card_bid { bidding::color::diamond, bidding::level(5) }
            }
        },

        trick_unit {
            counted_card {
                17,
                playing::card { playing::color::club, playing::rank::ace }
            },

            counted_card { 7, bidding::card_pass {} },
            counted_card { 1, bidding::card_double {} },

            counted_card {
                4,
                bidding::card_bid { bidding::color::diamond, bidding::level(5) }
            }
        }
    };

    std::string_view expected =
        "trick [ "
        "north = trick_unit [ "
        "counted_card { n = 1, card = card { CA } }, "
        "counted_card { n = 5, card = card_bid { D5 } }, "
        "counted_card { n = 3, card = card_pass {} }, "
        "counted_card { n = 0, card = card_redouble {} } "
        "], "
        "west = trick_unit [ "
        "counted_card { n = 2, card = card { CA } }, "
        "counted_card { n = 6, card = card_bid { D5 } }, "
        "counted_card { n = 4, card = card_pass {} }, "
        "counted_card { n = 1, card = card_redouble {} } "
        "], "
        "south = trick_unit [ "
        "counted_card { n = 5, card = card { CA } }, "
        "counted_card { n = 9, card = card_bid { D5 } }, "
        "counted_card { n = 7, card = card_pass {} }, "
        "counted_card { n = 1, card = card_redouble {} } "
        "], "
        "east = trick_unit [ "
        "counted_card { n = 17, card = card { CA } }, "
        "counted_card { n = 4, card = card_bid { D5 } }, "
        "counted_card { n = 7, card = card_pass {} }, "
        "counted_card { n = 1, card = card_redouble {} } "
        "] "
        "]";


    ASSERT_EQ(to_string(input), expected);
}
