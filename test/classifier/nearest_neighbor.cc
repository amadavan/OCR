#include "src/classifier/nearest_neighbor.h"

#include <exception>

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

	TEST_F(NearestNeighborTests, Constructor_PosNumberParam_Valid) {
		EXPECT_NO_THROW({ocr::NearestNeighbor();});
		EXPECT_NO_THROW({ocr::NearestNeighbor(1);});
		EXPECT_NO_THROW({ocr::NearestNeighbor(2);});
	}

	TEST_F(NearestNeighborTests, Constructor_StrParam_Valid) {
		EXPECT_NO_THROW({ocr::NearestNeighbor("inf");});
		EXPECT_NO_THROW({ocr::NearestNeighbor("-inf");});
	}

	TEST_F(NearestNeighborTests, Constructor_StrParam_Invalid) {
		EXPECT_THROW({ocr::NearestNeighbor("");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("i");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("in");}, std::invalid_argument);
		EXPECT_THROW({ocr::NearestNeighbor("asdf");}, std::invalid_argument);
	}

}