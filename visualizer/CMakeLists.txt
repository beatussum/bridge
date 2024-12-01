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
    visualizer
    VERSION 0.9.0
    DESCRIPTION "Component for visualizing a bridge game"
    HOMEPAGE_URL "https://github.com/beatussum/bridge/"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "cmake/")

set(
    VISUALIZER_HPP
    widgets/LoginDialog.hpp
)

list(TRANSFORM VISUALIZER_HPP PREPEND "include/")

set(
    VISUALIZER_CPP
    widgets/LoginDialog.cpp
    main.cpp
)

list(TRANSFORM VISUALIZER_CPP PREPEND "src/")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql Widgets)

qt6_standard_project_setup()
qt6_add_executable(visualizer "${VISUALIZER_CPP}")

target_link_libraries(
    visualizer

    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
        Qt6::Widgets
        analyzer
)

target_include_directories(visualizer PUBLIC "include/")

target_sources(
    visualizer

    PUBLIC
        FILE_SET HEADERS
        TYPE HEADERS
        FILES "${VISUALIZER_HPP}"
)

qt6_finalize_project()
