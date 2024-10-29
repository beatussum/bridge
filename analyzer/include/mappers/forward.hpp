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


#ifndef BRIDGE_ANALYZER_MAPPERS_FORWARD_HPP
#define BRIDGE_ANALYZER_MAPPERS_FORWARD_HPP

#include <opencv2/dnn/dnn.hpp>

/**
 * @file
 *
 * @brief The base header of the namespace
 * \ref bridge::analyzer::mappers::forward
 */

/**
 * @brief This namespace describes different utilities related to \ref forward
 */

namespace bridge::analyzer::mappers::forward
{
    /**
     * @brief A function object allowing to forward an input matrix to the
     * neural network
     */

    class forward
    {
    public:
        /**
         * @brief Default constructor of \ref forward
         */

        forward() = default;

        /**
         * @brief Destructor of \ref forward
         */

        ~forward() noexcept = default;

        /**
         * @brief Copy constructor of \ref forward
         *
         * @param[in] __other The \ref forward to copy
         */

        forward(const forward& __other) = default;

        /**
         * @brief Move constructor of \ref forward
         *
         * @param[in] __other The \ref forward to move
         */

        forward(forward&& __other) = default;
    public:
        /**
         * @brief Constructs a new \ref forward object specifying the underlying
         * ONNX file
         *
         * @param[in] __onnx_file The ONNX file to use
         */

        explicit forward(const cv::String& __onnx_file)
            : m_net(cv::dnn::readNetFromONNX(__onnx_file))
        {}
    public:
        /**
         * @brief Copy assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref forward
         */

        forward& operator=(const forward& __rhs) = default;

        /**
         * @brief Move assignment operator
         *
         * @param[in] __rhs The right hand side operand
         * @return A reference to the assigned \ref forward
         */

        forward& operator=(forward&& __rhs) = default;
    public:
        /**
         * @brief Applies forwardations to the input matrix
         *
         * @param[in] __input The input matrix to forward
         * @return The forwarded matrix
         */

        cv::Mat operator()(cv::InputArray __input);
    private:
        cv::dnn::Net m_net; ///< The OpenCV neural network
    };
}

#endif // BRIDGE_ANALYZER_MAPPERS_FORWARD_HPP
