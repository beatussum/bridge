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


#include "mappers/transform.hpp"
#include <gtest/gtest.h>

#include "map.hpp"

using namespace bridge::analyzer::mappers::transform;
using namespace bridge::analyzer::map;

namespace cv
{
    void PrintTo(const cv::Mat& __mat, std::ostream* __os)
    {
        *__os << "\n\n" << __mat << '\n';
    }
}

bool mat_equal(const cv::Mat& __lhs, const cv::Mat& __rhs)
{
    return
        std::equal(
            __lhs.begin<uchar>(),
            __lhs.end<uchar>(),
            __rhs.begin<uchar>()
        );
}

class resizing_test : public testing::Test
{
public:
    using value_type = std::array<cv::Mat, 4>;
public:
    resizing_test()
        : input {
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0))
        }
    {
        for (cv::Mat& m : input) {
            m.at<uchar>(1, 1) = 254; // OOOO
            m.at<uchar>(1, 2) = 254; // OXXO
            m.at<uchar>(2, 1) = 254; // OXXO
            m.at<uchar>(2, 2) = 254; // OOOO
        }
    }
protected:
    value_type input;
};

TEST_F(resizing_test, down)
{
    cv::Mat expected(2, 2, CV_8UC1);

    expected.at<uchar>(0, 0) = 64;
    expected.at<uchar>(0, 1) = 64;
    expected.at<uchar>(1, 0) = 64;
    expected.at<uchar>(1, 1) = 64;

    auto it =
        input.cbegin()

        | map(
            transform(
                0.,
                cv::Point2f(0.f, 0.f),
                cv::Rect(0, 0, 4, 4),
                cv::Size(2, 2)
            )
        );

    ASSERT_PRED2(mat_equal, *it, expected);
}

TEST_F(resizing_test, up)
{
    cv::Mat expected(5, 5, CV_8UC1, cv::Scalar(0));

    expected.at<uchar>(1, 1) = 125;
    expected.at<uchar>(1, 3) = 125;
    expected.at<uchar>(3, 1) = 125;
    expected.at<uchar>(3, 3) = 125;

    expected.at<uchar>(1, 2) = 178;
    expected.at<uchar>(2, 1) = 178;
    expected.at<uchar>(2, 3) = 178;
    expected.at<uchar>(3, 2) = 178;

    expected.at<uchar>(2, 2) = 254;

    auto it =
        input.cbegin()

        | map(
            transform(
                0.,
                cv::Point2f(0.f, 0.f),
                cv::Rect(0, 0, 4, 4),
                cv::Size(5, 5)
            )
        );

    ASSERT_PRED2(mat_equal, *it, expected);
}

class rotation_test
    : public testing::TestWithParam<
        std::tuple<
            double,
            cv::Point2f,
            cv::Rect,
            cv::Point
        >
    >
{
public:
    using value_type = std::array<cv::Mat, 4>;
public:
    rotation_test()
        : input {
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0x00)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0x00)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0x00)),
            cv::Mat(4, 4, CV_8UC1, cv::Scalar(0x00))
        }
    {
        input[0].at<uchar>(1, 1) = 0xff; // OOOO
        input[0].at<uchar>(1, 2) = 0x00; // OXOO
        input[0].at<uchar>(2, 1) = 0xff; // OXXO
        input[0].at<uchar>(2, 2) = 0xff; // OOOO

        input[1].at<uchar>(1, 1) = 0x00; // OOOO
        input[1].at<uchar>(1, 2) = 0xff; // OOXO
        input[1].at<uchar>(2, 1) = 0xff; // OXXO
        input[1].at<uchar>(2, 2) = 0xff; // OOOO

        input[2].at<uchar>(1, 1) = 0xff; // OOOO
        input[2].at<uchar>(1, 2) = 0xff; // OXXO
        input[2].at<uchar>(2, 1) = 0x00; // OOXO
        input[2].at<uchar>(2, 2) = 0xff; // OOOO

        input[3].at<uchar>(1, 1) = 0xff; // OOOO
        input[3].at<uchar>(1, 2) = 0xff; // OXXO
        input[3].at<uchar>(2, 1) = 0xff; // OXOO
        input[3].at<uchar>(2, 2) = 0x00; // OOOO
    }
protected:
    value_type input;
};

TEST_P(rotation_test, identity)
{
    double angle;
    cv::Point2f center;
    std::tie(angle, center, std::ignore, std::ignore) = GetParam();

    cv::Rect roi(0, 0, 4, 4);

    auto it =
        input.cbegin() |
        map(transform(angle, center, roi, roi.size())) |
        map(transform(-angle, center, roi, roi.size()));

    for (const cv::Mat& m : input) {
        EXPECT_PRED2(mat_equal, *it, m);
        ++it;
    }
}

TEST_P(rotation_test, rotate)
{
    const auto& [angle, center, roi, selected_top_left] = GetParam();

    cv::Rect selected(selected_top_left, roi.size());
    auto it = input.cbegin() | map(transform(angle, center, roi, roi.size()));

    for (value_type::size_type i = 0; i != 4; ++i) {
        value_type::size_type index =
            ((static_cast<value_type::size_type>(angle) / 90) + i) % 4;

        EXPECT_PRED2(mat_equal, *it, cv::Mat(input[index], selected));
        ++it;
    }
}

INSTANTIATE_TEST_SUITE_P(
    centered_rotation,
    rotation_test,

    testing::Combine(
        testing::Values(0., 90., 180., 270., 360.),
        testing::Values(cv::Point2f(1.5f, 1.5f)),
        testing::Values(cv::Rect(0, 0, 4, 4)),
        testing::Values(cv::Point(0, 0))
    )
);

INSTANTIATE_TEST_SUITE_P(
    rotation,
    rotation_test,

    testing::Values(
        std::make_tuple(
            0.,
            cv::Point2f(1.f, 1.f),
            cv::Rect(1, 1, 2, 2),
            cv::Point(1, 1)
        ),

        std::make_tuple(
            90.,
            cv::Point2f(1.f, 1.f),
            cv::Rect(1, 0, 2, 2),
            cv::Point(1, 1)
        ),

        std::make_tuple(
            180.,
            cv::Point2f(1.f, 1.f),
            cv::Rect(0, 0, 2, 2),
            cv::Point(1, 1)
        ),

        std::make_tuple(
            270.,
            cv::Point2f(1.f, 1.f),
            cv::Rect(0, 1, 2, 2),
            cv::Point(1, 1)
        ),

        std::make_tuple(
            360.,
            cv::Point2f(1.f, 1.f),
            cv::Rect(1, 1, 2, 2),
            cv::Point(1, 1)
        )
    )
);
