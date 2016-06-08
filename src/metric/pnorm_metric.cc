#include "metric/pnorm_metric.h"

ocr::PNorm::PNorm(uint32_t p_value) {
	if ( p_value == 0 ) {
		throw std::invalid_argument("p_value must be positive");
	}

	this->p_value_ = p_value;
}

inline double ocr::PNorm::distance(const arma::vec &vec1, const arma::vec &vec2)
{
	return arma::norm(vec1 - vec2, this->p_value_);
}