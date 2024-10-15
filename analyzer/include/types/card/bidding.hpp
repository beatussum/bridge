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


#ifndef BRIDGE_ANALYZER_TYPES_CARD_BIDDING_HPP
#define BRIDGE_ANALYZER_TYPES_CARD_BIDDING_HPP

#include <cstdint>
#include <variant>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::types::card::bidding
 */

/**
 * @brief This namespace describes the bidding card type and its associated
 * types
 */

namespace bridge::analyzer::types::card::bidding
{
    /**
     * @brief The color of a bid
     */

    enum struct color
    {
        club,    ///< A club
        diamond, ///< A diamond
        heart,   ///< A heart
        spade,   ///< A spade
        notrump  ///< A notrump
    };

    /**
     * @brief The level of a bid
     */

    class level
    {
        template <class Ostream>
        friend constexpr Ostream&& operator<<(Ostream&&, const level&);
    public:
        /**
         * @brief The underlying type of a \ref level
         */

        using underlying_type = std::uint_fast8_t;
    public:
        /**
         * @brief Default constructor of \ref level
         */

        constexpr level() noexcept
            : m_level(1)
        {}

        /**
         * @brief Copy constructor of \ref level
         *
         * @param[in] __other The other \ref level to copy
         */

        constexpr level(const level& __other) noexcept = default;

        /**
         * @brief Move constructor of \ref level
         *
         * @param[in] __other The other \ref level to move
         */

        constexpr level(level&& __other) noexcept = default;

        ~level() noexcept = default; ///< Destructor of \ref level
    public:
        /**
         * @brief Constructs a \ref level from an integer
         *
         * @param[in] __level The \ref level value (must be between 1 and 7)
         * @throw std::domain_error If \p __level is not between 1 and 7
         */

        explicit constexpr level(underlying_type __level);

        /**
         * @brief Casts a \ref level to an integer
         *
         * @return A \ref level as an integer
         */

        constexpr operator underlying_type() const noexcept { return m_level; }
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref level
         */

        constexpr level& operator=(const level& __rhs) noexcept = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref level
         */

        constexpr level& operator=(level&& __rhs) noexcept = default;
    private:
        underlying_type m_level; ///< The value of a \ref level
    };

    /**
     * @brief A bid
     */

    struct card_bid
    {
        color c; ///< The \ref color of the bid
        level l; ///< The \ref level of the bid
    };

    struct card_double {};   ///< A double
    struct card_pass {};     ///< A pass
    struct card_redouble {}; ///< A redouble
    struct card_stop {};     ///< A stop

    /**
     * @brief A bidding card
     */

    class card :
        public std::variant<
            card_bid,
            card_double,
            card_pass,
            card_redouble,
            card_stop
        >
    {
    public:
        using std::variant<
            card_bid,
            card_double,
            card_pass,
            card_redouble,
            card_stop
        >::variant;

        /**
         * @brief Default constructor of \ref card
         */

        constexpr card() noexcept = default;

        /**
         * @brief Copy constructor of \ref card
         *
         * @param[in] __other The other \ref card to copy
         */

        constexpr card(const card& __other) = default;

        /**
         * @brief Move constructor of \ref card
         *
         * @param[in] __other The other \ref card to move
         */

        constexpr card(card&& __other) noexcept = default;

        ~card() = default; ///< Destructor of \ref card
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref card
         */

        constexpr card& operator=(const card& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref card
         */

        constexpr card& operator=(card&& __rhs) noexcept = default;
    };

    /**
     * @brief Inserts a \ref color to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, color __value);

    /**
     * @brief Inserts a \ref level to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const level& __value)
        { return __os << static_cast<unsigned int>(__value.m_level), __os; }

    /**
     * @brief A user-defined literal for \ref level
     *
     * @param[in] __level The value of the \ref level
     * @return A \ref level corresponding to the given value
     * @throw std::domain_error If the \ref level is not between 1 and 7
     */

    constexpr level operator ""_lvl(unsigned long long __level)
        { return level(static_cast<level::underlying_type>(__level)); }

    /**
     * @brief Equality operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return (__lhs.c == __rhs.c) && (__lhs.l == __rhs.l); }

    /**
     * @brief Inequality operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Less-than operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is lesser than \p __rhs
     */

    constexpr bool operator<(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
    {
        return
            (__lhs.c == __rhs.c) ?
            (__lhs.l < __rhs.l) :
            (__lhs.c < __rhs.c);
    }

    /**
     * @brief Greater-than operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is greater than \p __rhs
     */

    constexpr bool operator>(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs == __rhs) && (__rhs < __lhs); }

    /**
     * @brief Less-equal operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is lesser than or equal to \p __rhs
     */

    constexpr bool operator<=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return (__lhs == __rhs) || (__rhs < __lhs); }

    /**
     * @brief Greater-equal operator for \ref card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is greater than or equal to \p __rhs
     */

    constexpr bool operator>=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs < __rhs); }

    /**
     * @brief Inserts a \ref card_bid to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card_bid& __value)
    {
        return __os << "card_bid { " << __value.c << __value.l << " }", __os;
    }

    /**
     * @brief Equality operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_double __lhs, card_double __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_double __lhs, card_double __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for \ref card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_double __lhs, card_double __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a \ref card_double to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_double __value)
        { return __os << "card_redouble {}", __os; }

    /**
     * @brief Equality operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_pass __lhs, card_pass __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_pass __lhs, card_pass __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for \ref card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_pass __lhs, card_pass __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a \ref card_pass to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_pass __value)
        { return __os << "card_pass {}", __os; }

    /**
     * @brief Equality operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_redouble __lhs, card_redouble __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for \ref card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a \ref card_redouble to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_redouble __value)
        { return __os << "card_redouble {}", __os; }

    /**
     * @brief Equality operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_stop __lhs, card_stop __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_stop __lhs, card_stop __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for \ref card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_stop __lhs, card_stop __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a \ref card_stop to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_stop __value)
        { return __os << "card_stop {}", __os; }

    /**
     * @brief Inserts a \ref card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value);
}

#include "bidding.ipp"

#endif // BRIDGE_ANALYZER_TYPES_CARD_BIDDING_HPP
