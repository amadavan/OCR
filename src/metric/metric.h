#ifndef OCR_METRIC_METRIC_H_
#define OCR_METRIC_METRIC_H_

#include <armadillo>

namespace ocr {

/**
 * Defines an interface for metric spaces acting on vectors.
 *
 * Specifies the core methods required for defining a vector metric space. This
 * includes a distance function acting on two vectors. This is to make the
 * other component more generalizable.
 */
class Metric {
protected:
	/**
	 * Base constructor for Metric
	 *
	 * The empty constructor for Metric is defined as protected to ensure that
	 * no developer (me) unwittingly attempts to use it to to create an object.
	 */
	Metric() {}

public:
	virtual ~Metric() {}

	/**
	 * Compute distance between two column vectors
	 *
	 * Use armadillo norm functions to calculate the distance between column
	 * vectors. The norm used is specified in the constructor.
	 *
	 * @param[in] vec1 armadillo vector
	 * @param[in] vec2 armadillo vector
	 *
	 * @return double distance between input vectors
	 */
	virtual double distance(const arma::vec &vec1, const arma::vec &vec2) = 0;

};

}

#endif // OCR_METRIC_METRIC_H_