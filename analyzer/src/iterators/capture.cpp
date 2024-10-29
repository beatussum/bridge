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


#include "iterators/capture.hpp"

namespace bridge::analyzer::iterators::capture
{
    capture& capture::operator++()
    {
        if (!m_video_capture->grab()) {
            throw std::runtime_error("The next image cannot be grabbed");
        }

        m_cached.reset();

        return *this;
    }

    capture capture::operator++(int)
    {
        capture ret = *this;
        ++*this;
        return ret;
    }

    capture::reference capture::operator*()
    {
        if (!m_cached.has_value() && !m_video_capture->retrieve(*m_cached)) {
            throw std::runtime_error("The current image cannot be retrieved");
        }

        return *m_cached;
    }
}
