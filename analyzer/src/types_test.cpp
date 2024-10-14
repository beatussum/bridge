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

TEST(print_test, game)
{
    game input {
        player { "Alice", "Guillaume", metadata::metadata() },
        player { "Baptiste", "Chabanol", metadata::metadata() },
        player { "Carmen", "Le Maner", metadata::metadata() },
        player { "Denis", "Kumar", metadata::metadata() },

        auction {
            positioning::east,

            std::vector<card::bidding::card> {
                card::bidding::card_double {},

                card::bidding::card_bid {
                    card::bidding::color::club,
                    card::bidding::level(5)
                }
            },

            metadata::metadata()
        },

        deal::deal {
            deal::deal_unit {
                card::playing::card {
                    card::playing::color::club,
                    card::playing::rank::two
                },

                card::playing::card {
                    card::playing::color::club,
                    card::playing::rank::three
                },
            },

            deal::deal_unit {
                card::playing::card {
                    card::playing::color::diamond,
                    card::playing::rank::two
                },

                card::playing::card {
                    card::playing::color::diamond,
                    card::playing::rank::three
                },
            },

            deal::deal_unit {
                card::playing::card {
                    card::playing::color::heart,
                    card::playing::rank::two
                },

                card::playing::card {
                    card::playing::color::heart,
                    card::playing::rank::three
                },
            },

            deal::deal_unit {
                card::playing::card {
                    card::playing::color::spade,
                    card::playing::rank::two
                },

                card::playing::card {
                    card::playing::color::spade,
                    card::playing::rank::three
                },
            },

            metadata::metadata()
        },

        std::vector<trick::trick> {
            trick::trick {
                std::array<trick::trick_unit, 4> {
                    trick::trick_unit {
                        card::playing::card {
                            card::playing::color::club,
                            card::playing::rank::two
                        },

                        positioning::north
                    },

                    trick::trick_unit {
                        card::playing::card {
                            card::playing::color::diamond,
                            card::playing::rank::two
                        },

                        positioning::west
                    },

                    trick::trick_unit {
                        card::playing::card {
                            card::playing::color::heart,
                            card::playing::rank::two
                        },

                        positioning::south
                    },

                    trick::trick_unit {
                        card::playing::card {
                            card::playing::color::spade,
                            card::playing::rank::two
                        },

                        positioning::east
                    }
                },

                metadata::metadata()
            },
        },

        metadata::metadata()
    };

    std::string_view expected =
        "game { "
        "north = player { first_name = Alice, last_name = Guillaume }, "
        "west = player { first_name = Baptiste, last_name = Chabanol }, "
        "south = player { first_name = Carmen, last_name = Le Maner }, "
        "east = player { first_name = Denis, last_name = Kumar }, "
        "auction = auction { "
        "first_player = east, "
        "bidding_card = [ "
        "card_redouble {}, "
        "card_bid { C5 } "
        "] "
        "}, "
        "deal = deal { "
        "north = deal_unit [ card { C2 }, card { C3 } ], "
        "west = deal_unit [ card { D2 }, card { D3 } ], "
        "south = deal_unit [ card { H2 }, card { H3 } ], "
        "east = deal_unit [ card { S2 }, card { S3 } ] }, "
        "tricks = [ "
        "trick { "
        "first = trick_unit { card = card { C2 }, positioning = north }, "
        "second = trick_unit { card = card { D2 }, positioning = west }, "
        "third = trick_unit { card = card { H2 }, positioning = south }, "
        "fourth = trick_unit { card = card { S2 }, positioning = east } "
        "} "
        "] "
        "}";

    ASSERT_EQ(to_string(input), expected);
}
