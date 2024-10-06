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


#ifndef BRIDGE_ANALYZER_CORE_HPP
#define BRIDGE_ANALYZER_CORE_HPP

#include <sstream>

/**
 * @file
 * @brief This header describes core utilities used by the analyzer
 */

/**
 * @brief This namespace contains all core utilities used by the analyzer
 */

namespace bridge::analyzer::core
{
    /**
     * @brief _Details_ namespace of bridge::analyzer::core
     *
     * @caution This namespace exists for implementation reasons. It should
     * never be used by users of bridge::analyzer::core.
     */

    namespace details
    {
        /**
         * @brief A SFINAE alias to conditionnaly enable to_string()
         *
         * This alias causes a substitution failure if the type T does not have
         * its output operator defined.
         *
         * @tparam[in] T The type tested
         */

        template <class T>
        using enable_to_string_t =
            std::enable_if_t<
                std::is_same_v<
                    decltype(std::ostringstream() << std::declval<T>()),
                    std::ostringstream&&
                >,

                std::string
            >;
    }

    /**
     * @brief Cast a type to std::string
     *
     * @param[in] __value The type to cast
     * @return A std::string representing the type
     */

    template <class T>
    details::enable_to_string_t<T> to_string(T&& __value)
    {
        std::ostringstream ss;
        return (ss << __value).str();
    }
}

#endif // BRIDGE_ANALYZER_CORE_HPP
