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

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::core
 */

/**
 * @brief This namespace describes various core utilities
 */

namespace bridge::analyzer::core
{
    /**
     * @brief The detail namespace of \ref bridge::analyzer::core
     *
     * @warning This namespace should never been used directly: it exists only
     * for implementation reason.
     */

    namespace details
    {
        /**
         * @brief Enable \ref bridge::analyzer::core::to_string() if supported
         *
         * @tparam T The type which could potentially be casted to std::string
         */

        template <class T>
        using enable_to_string =
            std::enable_if_t<
                std::is_same_v<
                    std::ostringstream&&,
                    decltype(std::ostringstream() << std::declval<T>())
                >,

                std::string
            >;

        /**
         * @brief Enable \ref bridge::analyzer::core::operator<<() if supported
         *
         * @tparam Ostream The output stream type
         * @tparam T The potentially iterable type
         */

        template <class Ostream, class T>
        using enable_iterable_formatted_output_function =
            std::enable_if_t<
                std::conjunction_v<
                    std::is_invocable_r<bool, decltype(&T::empty), const T&>,

                    std::is_invocable_r<
                        typename T::const_iterator,
                        decltype(&T::cend),
                        const T&
                    >,

                    std::is_invocable_r<
                        typename T::const_iterator,
                        decltype(&T::cbegin),
                        const T&
                    >,

                    std::is_same<
                        typename T::const_iterator&,
                        decltype(--std::declval<typename T::const_iterator>())
                    >,

                    std::is_invocable_r<
                        bool,
                        std::not_equal_to<typename T::const_iterator>,
                        const typename T::const_iterator&,
                        const typename T::const_iterator&
                    >,

                    std::is_same<
                        typename T::const_reference,
                        decltype(*std::declval<typename T::const_iterator>())
                    >
                >,

                Ostream&&
            >;
    }

    /**
     * @brief Cast a type to std::string
     *
     * @tparam T The type of the value to cast
     * @param[in] __value The value to cast
     * @return A std::string representing the type
     */

    template <class T>
    details::enable_to_string<T> to_string(const T& __value);

    /**
     * @brief The formatted output function for iterable types
     *
     * @tparam Ostream The output stream type
     * @tparam T The iterable type
     *
     * @param[in] __os The output stream
     * @param[in] __iterable The iterable
     *
     * @return The modified stream
     */

    template <class Ostream, class T>
    details::enable_iterable_formatted_output_function<Ostream, T>
    operator<<(Ostream&& __os, const T& __iterable);
}

#include "core.ipp"

#endif // BRIDGE_ANALYZER_CORE_HPP
