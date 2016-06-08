#include "src/metric/pnorm_metric.h"


#include <exception>

#include <armadillo>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace ocr {
	class PNormMetricTests : public testing::Test {
	public:
		void SetUp() {

		}

		void TearDown() {

		}
	};

	TEST_F(PNormMetricTests, Constructor_EmptyParam_Valid) {
		EXPECT_NO_THROW({ocr::PNorm();});
	}

	TEST_F(PNormMetricTests, Constructor_PosNumberParam_Valid) {
		EXPECT_NO_THROW({ocr::PNorm(1);});
		EXPECT_NO_THROW({ocr::PNorm(2);});
	}

	TEST_F(PNormMetricTests, Constructor_ZeroParam_Invalid) {
		EXPECT_THROW({ocr::PNorm(0);}, std::invalid_argument);
	}

	TEST_F(PNormMetricTests, Distance_EuclideanParam_Test) {
		ocr::PNorm euclidean_metric = ocr::PNorm(2);
		EXPECT_EQ(0, euclidean_metric.distance({0,0,0},{0,0,0}));
		EXPECT_EQ(0, euclidean_metric.distance({1,1},{1,1}));
		EXPECT_EQ(2, euclidean_metric.distance({0,0,0,0},{1,1,1,1}));
		EXPECT_EQ(2, euclidean_metric.distance({1,0,1,0},{0,1,0,1}));
	}

	TEST_F(PNormMetricTests, Distance_ManhattanParam_Test) {
		ocr::PNorm manhattan_metric = ocr::PNorm(1);
		EXPECT_EQ(0, manhattan_metric.distance({0,0,0},{0,0,0}));
		EXPECT_EQ(0, manhattan_metric.distance({1,1},{1,1}));
		EXPECT_EQ(4, manhattan_metric.distance({0,0,0,0},{1,1,1,1}));
		EXPECT_EQ(4, manhattan_metric.distance({1,0,1,0},{0,1,0,1}));
	}

}