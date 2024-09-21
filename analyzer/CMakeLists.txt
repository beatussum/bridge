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

set(ANALYZER_CPP)
list(TRANSFORM ANALYZER_CPP PREPEND "src/")

set(
	ANALYZER_PUBLIC_HPP
	types/types.hpp
)

list(TRANSFORM ANALYZER_PUBLIC_HPP PREPEND "include/")

add_library(analyzer STATIC "${ANALYZER_CPP}")
target_include_directories(analyzer PUBLIC "include/")

target_sources(
	analyzer

	PUBLIC
		FILE_SET public_headers
		TYPE HEADERS
		FILES "${ANALYZER_PUBLIC_HPP}"
)
