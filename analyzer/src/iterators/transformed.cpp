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


#include "iterators/transformed.hpp"

namespace bridge::analyzer::iterators::transformed
{
    void swap(
        transformed_parameters& __lhs,
        transformed_parameters& __rhs
    ) noexcept
    {
        using std::swap;

        swap(__lhs.angle, __rhs.angle);
        swap(__lhs.center, __rhs.center);
        swap(__lhs.roi, __rhs.roi);
        swap(__lhs.size, __rhs.size);
    }
}
