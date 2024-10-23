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

#include <boost/container_hash/hash.hpp>

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

    namespace details {}

    namespace details
    {
        /**
         * @brief Enable \ref bridge::analyzer::core::to_string() if supported
         *
         * @tparam T The type which could potentially be casted to std::string
         */

        template <class T>
        using enable_to_string =
            std::is_same<
                std::ostringstream&&,
                decltype(std::ostringstream() << std::declval<T>())
            >;
    }

    template <class T>
    std::enable_if_t<details::enable_to_string<T>::value, std::string>
    to_string(const T&);

    namespace details
    {
        /**
         * @brief Enables \ref bridge::analyzer::core::hash_value() if supported
         *
         * @tparam T The type which could potentially be hashed by
         * \ref bridge::analyzer::core::hash_value()
         */

        template <class T>
        using enable_hash_value =
            std::conjunction<
                std::is_empty<T>,
                std::is_pod<T>,

                std::is_same<
                    decltype(to_string(std::declval<T>())),
                    std::string
                >
            >;

        /**
         * @brief Enable \ref bridge::analyzer::core::operator<<() if supported
         *
         * @tparam T The potentially iterable type
         */

        template <class T>
        using enable_iterable_formatted_output_function =
            std::conjunction<
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
            >;
    }

    /**
     * @brief Determines the function signature of a callable type
     *
     * @tparam F The callable type
     */

    template <class F>
    struct function_signature;

    /// @cond PRIVATE

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) & noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) && noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const & noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const && noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) volatile noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) volatile & noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) volatile && noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const volatile noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const volatile & noexcept(nx)>
        { using type = R(Args...); };

    template <class R, class T, bool nx, class... Args>
    struct function_signature<R (T::*) (Args...) const volatile && noexcept(nx)>
        { using type = R(Args...); };

    /// @endcond

    /**
     * @brief The function signature of a callable type
     *
     * @tparam F The callable type
     */

    template <class F>
    using function_signature_t = typename function_signature<F>::type;

    /**
     * @brief Hashes an input
     *
     * This overload aims to provide a convenient way to hash empty types
     * `std::string`-castable.
     *
     * @remark This function is an overload of a Boost-provided function.
     *
     * @tparam T The type of the input to hash
     * @param[in] __input The input to hash
     * @return The hashed input
     */

    template <class T>
    std::enable_if_t<details::enable_hash_value<T>::value, std::size_t>
    hash_value(T __input)
        { return boost::hash<std::string>()(to_string(__input)); }

    /**
     * @brief Casts a type to std::string
     *
     * @tparam T The type of the value to cast
     * @param[in] __value The value to cast
     * @return A std::string representing the type
     */

    template <class T>
    std::enable_if_t<details::enable_to_string<T>::value, std::string>
    to_string(const T& __value);

    /**
     * @brief Inserts an iterable type to an output stream
     *
     * @tparam Ostream The output stream type
     * @tparam T The iterable type
     *
     * @param[in] __os The output stream
     * @param[in] __iterable The iterable
     *
     * @return The modified output stream
     */

    template <class Ostream, class T>
    std::enable_if_t<
        details::enable_iterable_formatted_output_function<T>::value,
        Ostream&&
    >
    operator<<(Ostream&& __os, const T& __iterable);
}

#include "core.ipp"

#endif // BRIDGE_ANALYZER_CORE_HPP
