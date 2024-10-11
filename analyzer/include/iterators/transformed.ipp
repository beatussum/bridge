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


namespace bridge::analyzer::iterators::transformed
{
    template <class Iterator>
    transformed_iterator<Iterator>&
    transformed_iterator<Iterator>::operator=(transformed_iterator __rhs)
    {
        swap(*this, __rhs);
        return *this;
    }

    template <class Iterator>
    transformed_iterator<Iterator>& transformed_iterator<Iterator>::operator++()
    {
        ++m_inner;
        m_need_update = true;
        return *this;
    }

    template <class Iterator>
    transformed_iterator<Iterator>
    transformed_iterator<Iterator>::operator++(int)
    {
        transformed_iterator ret = *this;
        ++*this;
        return ret;
    }

    template <class Iterator>
    typename transformed_iterator<Iterator>::reference
    transformed_iterator<Iterator>::operator*()
    {
        if (m_need_update) {
            m_content = m_inner->clone();

            cv::warpAffine(
                m_content,
                m_content,

                cv::getRotationMatrix2D(
                    m_parameters.center,
                    m_parameters.angle,
                    1.
                ),

                m_content.size()
            );

            m_content = cv::Mat(m_content, m_parameters.roi);
            cv::resize(m_content, m_content, m_parameters.size);

            m_need_update = false;
        }

        return m_content;
    }

    template <class Iterator>
    void swap(
        transformed_iterator<Iterator>& __lhs,
        transformed_iterator<Iterator>& __rhs
    )
    {
        using std::swap;

        swap(__lhs.m_inner, __rhs.m_inner);
        swap(__lhs.m_parameters, __rhs.m_parameters);
        swap(__lhs.m_content, __rhs.m_content);
        swap(__lhs.m_need_update, __rhs.m_need_update);
    }
}
