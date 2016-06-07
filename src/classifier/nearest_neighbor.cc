#include "classifier/nearest_neighbor.h"

ocr::NearestNeighbor::NearestNeighbor( const uint32_t distance_norm ) {
	this->distance_norm_int_ = distance_norm;
}

ocr::NearestNeighbor::NearestNeighbor( const std::string &distance_norm ) {
	// Check for valid arguments
	if ( distance_norm.compare("inf") != 0 &&
		 distance_norm.compare("-inf") != 0	) {
		throw std::invalid_argument("distance_norm must be 'inf' or 'inf'");
	}
	this->distance_norm_str_ = distance_norm;
	this->distance_norm_int_ = 0;
}
