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


#include "types/card/bidding.hpp"

namespace bridge::analyzer::types::card::bidding
{
    std::size_t hash_value(const card_bid& __card_bid)
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, __card_bid.c);
        boost::hash_combine(seed, __card_bid.l);

        return seed;
    }
}
