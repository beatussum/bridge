# Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.30.2)

project(
    analyzer
    VERSION 0.9.0
    DESCRIPTION "Component for video analysis of a bridge game"
    HOMEPAGE_URL "https://github.com/beatussum/bridge/"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "cmake/")

set(
    ANALYZER_PUBLIC_HPP
    mappers/transform.hpp
    types/card/bidding.hpp
    types/card/playing.hpp
    types/raw/uncounted.hpp
    types/card.hpp
    types/deal.hpp
    types/metadata.hpp
    types/raw.hpp
    types/trick.hpp
    core.hpp
    map.hpp
    mappers.hpp
    types.hpp
)

list(TRANSFORM ANALYZER_PUBLIC_HPP PREPEND "include/")

set(
    ANALYZER_PUBLIC_IPP
    types/card/bidding.ipp
    types/card/playing.ipp
    types/raw/uncounted.ipp
    types/card.ipp
    types/deal.ipp
    types/trick.ipp
    core.ipp
    map.ipp
    types.ipp
)

list(TRANSFORM ANALYZER_PUBLIC_IPP PREPEND "include/")

set(
    ANALYZER_CPP
    mappers/transform.cpp
    types/card/bidding.cpp
)

list(TRANSFORM ANALYZER_CPP PREPEND "src/")

find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS imgproc)
add_library(analyzer STATIC "${ANALYZER_CPP}")
target_link_libraries(analyzer PUBLIC Boost::boost opencv_imgproc)
target_include_directories(analyzer PUBLIC "include/")

target_sources(
    analyzer

    PUBLIC
        FILE_SET HEADERS
        TYPE HEADERS
        FILES "${ANALYZER_PUBLIC_HPP}" "${ANALYZER_PUBLIC_IPP}"
)

bridge_add_to_doc("${ANALYZER_PUBLIC_HPP}")

bridge_add_unit_tests(
    TESTS
        mappers/transform
        types/card/bidding
        types/card/playing
        types/raw/uncounted
        types/deal
        map
        types

    EXTRA_LIBS analyzer
)
