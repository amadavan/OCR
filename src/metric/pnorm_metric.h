#ifndef OCR_METRIC_PNORM_H_
#define OCR_METRIC_PNORM_H_

#include "metric/metric.h"

namespace ocr {

/**
 * A p-norm metric class
 *
 * Defines a metric as the norm of vector space. Specifically, it designates the
 * p-norm as the metric space, which is mathematically expressed as the
 * following statement.
 * \f[
 * d(x,y) = \left( \Sigma_{i=1}^{n} | x_i |^p \right)^{\frac{1}{p}}
 * \f]
 */
class PNorm : public Metric {
public:
	/**
	 * Constructor for p-norm metric
	 *
	 * Designates the p for the p-norm metric to compute the distance. The value
	 * defaults to 2, representing the Euclidean norm.
	 *
	 * @param[in] p_value integer greater than 1 specifying norm
	 */
	PNorm(uint32_t p_value = 2);

	/**
	 * Compute distance between two column vectors
	 *
	 * Use armadillo norm function to calculate the distance between column
	 * vectors. The norm used is specified in the constructor. Assumes same
	 * size between vectors.
	 *
	 * @param[in] vec1 armadillo vector
	 * @param[in] vec2 armadillo vector
	 *
	 * @return double distance between input vectors
	 */
	double distance(const arma::vec &vec1, const arma::vec &vec2);

private:
	uint32_t p_value_;

};

}

#endif // OCR_METRIC_PNORM_H_