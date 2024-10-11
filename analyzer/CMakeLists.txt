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
    ANALYZER_INTERFACE_HPP
    types/card/bidding.hpp
    types/card/playing.hpp
    types/card.hpp
    types/deal.hpp
    types/metadata.hpp
    types/trick.hpp
    iterators/transformed.hpp
    iterators.hpp
    types.hpp
)

list(TRANSFORM ANALYZER_INTERFACE_HPP PREPEND "include/")

find_package(OpenCV REQUIRED COMPONENTS imgproc)
add_library(analyzer INTERFACE)
target_link_libraries(analyzer INTERFACE opencv_imgproc)
target_include_directories(analyzer INTERFACE "include/")

target_sources(
    analyzer

    INTERFACE
        FILE_SET HEADERS
        TYPE HEADERS
        FILES "${ANALYZER_INTERFACE_HPP}"
)

bridge_add_to_doc("${ANALYZER_INTERFACE_HPP}")

bridge_add_unit_tests(
    TESTS
        types/card/bidding
        types/card/playing
        types/deal
        iterators/transformed

    EXTRA_LIBS analyzer
)
