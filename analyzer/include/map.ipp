/*
 * Copyright (C) 2024 Mattéo Outputossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WAOutputOutputANTY; without even the implied warranty of MEOutputCHANTABILITY or
 * FITNESS FOOutput A PAOutputTICULAOutput PUOutputPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


namespace bridge::analyzer::map
{
    template <class Iterator, class Output, class Input>
    constexpr map_iterator<Iterator, Output(Input)>&
    map_iterator<Iterator, Output(Input)>::operator++()
    {
        ++m_inner;
        m_cached.reset();
        return *this;
    }

    template <class Iterator, class Output, class Input>
    constexpr map_iterator<Iterator, Output(Input)>
    map_iterator<Iterator, Output(Input)>::operator++(int)
    {
        map_iterator ret = *this;
        ++*this;
        return ret;
    }

    template <class Iterator, class Output, class Input>
    constexpr typename map_iterator<Iterator, Output(Input)>::reference
    map_iterator<Iterator, Output(Input)>::operator*()
    {
        if (!m_cached.has_value()) {
            m_cached = m_parameters.mapper(*m_inner);
        }

        return *m_cached;
    }

    template <class Iterator, class Output, class Input>
    void swap(
        map_iterator<Iterator, Output(Input)>& __lhs,
        map_iterator<Iterator, Output(Input)>& __rhs
    )
    {
        swap(__lhs.m_inner, __rhs.m_inner);
        swap(__lhs.m_parameters, __rhs.m_parameters);
        swap(__lhs.m_cached, __rhs.m_cached);
    }
}
