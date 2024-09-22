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
    bridge
    VERSION 0.9.0
    DESCRIPTION "A tool for capturing a filmed bridge game"
    HOMEPAGE_URL "https://github.com/beatussum/bridge/"
    LANGUAGES CXX
)

option(WITH_DOC "Enable building of documentation" OFF)

if (WITH_DOC)
    find_package(Doxygen REQUIRED)

    set(DOC_DIR "${CMAKE_BINARY_DIR}/doc/" CACHE PATH "The path where the documention is built")

    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_INLINE_INHERITED_MEMB YES)
    set(DOXYGEN_OUTPUT_DIRECTORY "${DOC_DIR}")
    set(DOXYGEN_WARN_LOGFILE "${DOC_DIR}/log")
    set(DOXYGEN_WARN_NO_PARAMDOC YES)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CompilerFlags)

find_package(Ccache MODULE)
enable_ccache()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_gcc_cxx_flags(
    -fmessage-length=75
    -fno-gnu-keywords
    -fno-operator-names
    -funsigned-char
    -pipe
    -Wall
    -Wconversion
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wfloat-equal
    -Wignored-qualifiers
    -Wimplicit-fallthrough=5
    -Wmissing-field-initializers
    -Wmissing-include-dirs
    -Wno-div-by-zero
    -Wnoexcept
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpedantic
    -Wsuggest-attribute=const
    -Wsuggest-attribute=noreturn
    -Wsuggest-attribute=pure
    -Wsuggest-final-methods
    -Wsuggest-final-types
    -Wsuggest-final-types
    -Wsuggest-override
    -Wsuggest-override
    -Wundef
    -Wuninitialized
)

add_subdirectory(analyzer)
