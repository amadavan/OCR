#ifndef OCR_PARSER_NIST_PARSER_H_
#define OCR_PARSER_NIST_PARSER_H_

#include <fstream>

#include <armadillo>

#include "util/ocrtypes.h"
#include "util/utilities.h"

namespace ocr {
	namespace mnist {

		/**
		 * Parse MNIST images from file
		 *
		 * Creates a matrix of images from the MNIST dataset file that is
		 * input to the function. Each image entry is stored in a single
		 * column of the output matrix.
		 *
		 * @param[in] filename input string filename from which to read images
		 *
		 * @return matrix of images in designated file
		 */
		arma::mat parse_images(const std::string &filename);

		/**
		 * Parse MNIST labels from file
		 *
		 * Creates a column vector of labels as read from the specified MNIST
		 * label dataset. Each i-th entry corresponds to the i-th column of
		 * the matrix from parse_images.
		 *
		 * @param[in] filename input string filename from which to read labels
		 *
		 * @return column vector of labels in designated file
		 */
		arma::Col<label_t> parse_labels(const std::string &filename);

	}
}

#endif // OCR_PARSER_NIST_PARSER_H_