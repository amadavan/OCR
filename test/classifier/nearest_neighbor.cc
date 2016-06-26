#include "src/classifier/nearest_neighbor.h"

#include <exception>

#include <armadillo>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace ocr {
	class NearestNeighborTests : public testing::Test {
	public:
		void SetUp() {

		}

		void TearDown() {

		}
	};

	TEST_F(NearestNeighborTests, Constructor_Empty_Valid) {
		EXPECT_NO_THROW({ocr::NearestNeighbor();});
	}

	TEST_F(NearestNeighborTests, Constructor_PNorm_Valid) {
		EXPECT_NO_THROW({ocr::NearestNeighbor(PNorm());});
	}

	TEST_F(NearestNeighborTests, Constructor_StrParam_Invalid) {
		EXPECT_THROW({ocr::NearestNeighbor("");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("i");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("in");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("asdf");}, std::invalid_argument);
	}

	TEST_F(NearestNeighborTests, Train_) {
		ocr::NearestNeighbor nn = ocr::NearestNeighbor();
	}

}