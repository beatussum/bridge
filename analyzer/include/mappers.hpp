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


#ifndef BRIDGE_ANALYZER_MAPPERS_HPP
#define BRIDGE_ANALYZER_MAPPERS_HPP

#include "types/raw/counted.hpp"

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::mappers
 */

/**
 * @brief This namespace describes mapper types
 */

namespace bridge::analyzer::mappers
{
    /**
     * @brief A function object allowing to substract two
     * \ref bridge::analyzer::types::raw::counted::trick
     */

    struct minus : std::minus<types::raw::counted::trick> {};
}

#endif // BRIDGE_ANALYZER_MAPPERS_HPP
