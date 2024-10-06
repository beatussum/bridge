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
 * bridge::analyzer::types::card::bidding
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
     *
     * @note A variable of this type must have a value between 1 and 7;
     * otherwise, the behavior of the associated bid is undefined.
     */

    using level = std::uint_fast8_t;

    /**
     * @brief A bid
     */

    struct card_bid
    {
        color c; ///< The color of the bid
        level l; ///< The level of the bid
    };

    struct card_double {};   ///< A double
    struct card_pass {};     ///< A pass
    struct card_redouble {}; ///< A redouble
    struct card_stop {};     ///< A stop

    /**
     * @brief A bidding card
     */

    using card =
        std::variant<
            card_bid,
            card_double,
            card_pass,
            card_redouble,
            card_stop
        >;

    /**
     * @brief Inserts a color to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, color __value)
    {
        switch (__value) {
            case color::club:
                __os << 'C';
                break;

            case color::diamond:
                __os << 'D';
                break;

            case color::heart:
                __os << 'H';
                break;

            case color::spade:
                __os << 'S';
                break;

            case color::notrump:
                __os << 'N';
                break;

            default:
                __os << '?';
                break;
        }

        return __os;
    }

    /**
     * @brief Equality operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    constexpr bool operator==(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return (__lhs.c == __rhs.c) && (__lhs.l == __rhs.l); }

    /**
     * @brief Inequality operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    constexpr bool operator!=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Less-than operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is lesser than `rhs`
     */

    constexpr bool operator<(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
    {
        if (__lhs.c == __rhs.c) {
            return __lhs.l < __rhs.l;
        } else {
            return __lhs.c < __rhs.c;
        }
    }

    /**
     * @brief Greater-than operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is greater than `rhs`
     */

    constexpr bool operator>(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs == __rhs) && (__rhs < __lhs); }

    /**
     * @brief Less-equal operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is lesser than or equal to `rhs`
     */

    constexpr bool operator<=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return (__lhs == __rhs) || (__rhs < __lhs); }

    /**
     * @brief Greater-equal operator for card_bid
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is greater than or equal to `rhs`
     */

    constexpr bool operator>=(
        const card_bid& __lhs,
        const card_bid& __rhs
    ) noexcept
        { return !(__lhs < __rhs); }

    /**
     * @brief Inserts a card_bid to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card_bid& __value)
    {
        __os << "card_bid { " << __value.c << __value.l << " }";
        return __os;
    }

    /**
     * @brief Equality operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_double __lhs, card_double __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_double __lhs, card_double __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_double __lhs, card_double __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for card_double
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_double __lhs, card_double __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a card_double to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_double __value)
    {
        __os << "card_redouble {}";
        return __os;
    }

    /**
     * @brief Equality operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_pass __lhs, card_pass __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_pass __lhs, card_pass __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_pass __lhs, card_pass __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for card_pass
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_pass __lhs, card_pass __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a card_pass to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_pass __value)
    {
        __os << "card_pass {}";
        return __os;
    }

    /**
     * @brief Equality operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_redouble __lhs, card_redouble __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_redouble __lhs, card_redouble __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for card_redouble
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_redouble __lhs, card_redouble __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a card_redouble to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_redouble __value)
    {
        __os << "card_redouble {}";
        return __os;
    }

    /**
     * @brief Equality operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator==(card_stop __lhs, card_stop __rhs) noexcept
       { return true; }

    /**
     * @brief Inequality operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator!=(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Less-than operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator<(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Greater-than operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>(card_stop __lhs, card_stop __rhs) noexcept
        { return false; }

    /**
     * @brief Less-equal operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `true`
     */

    constexpr bool operator<=(card_stop __lhs, card_stop __rhs) noexcept
        { return true; }

    /**
     * @brief Greater-equal operator for card_stop
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return `false`
     */

    constexpr bool operator>=(card_stop __lhs, card_stop __rhs) noexcept
        { return true; }

    /**
     * @brief Inserts a card_stop to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, card_stop __value)
    {
        __os << "card_stop {}";
        return __os;
    }
}

#endif // BRIDGE_ANALYZER_TYPES_CARD_BIDDING_HPP
