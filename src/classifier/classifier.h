#ifndef OCR_CLASSIFIER_CLASSIFIER_H_
#define OCR_CLASSIFIER_CLASSIFIER_H_

#include <armadillo>

#include "util/ocrtypes.h"

namespace ocr {

/**
 * Defines an interface for supervised-learning classifiers.
 *
 * Specifies the core methods required of supervised-learning classifiers.
 * The ClassifierInterface class defines methods to train the classifier with
 * a training dataset as well as methods to test the classifier against a
 * dataset of size one or more. The class also incorporates methods for
 * serialization.
 */
class ClassifierInterface {

protected:
	/**
	 * Base constructor for ClassifierInterface
	 *
	 * The empty constructor for ClassifierInterface is defined as protected
	 * to ensure that no unwitting developer accidently attempts to use it to
	 * to create an object.
	 */
	ClassifierInterface() {}

public:
	virtual ~ClassifierInterface() {}


	/**
	 * Trains the classifier given a dataset and known labels for the set
	 *
	 * Uses the known dataset and labels to generate the algorithm that will
	 * later be used to predict the values of unknown data. This method should
	 * be run prior to any testing methods (including test, test_batch...)
	 *
	 * @param[in] data_set nxm matrix with each entry in a column
	 * @param[in] label_set mx1 vector of data_set labels
	 */
	virtual void train( const arma::mat &data_set,
						const arma::Col<label_t> &label_set ) = 0;

	/**
	 * Predict the label of a single vector.
	 *
	 * Uses the trained algorithm to determine the label of a specified nx1
	 * vector where n is the number of elements in each dataset entry. This
	 * method assumes that the training method has already been completed.
	 *
	 * @param[in] predict_vector The nx1 vector, whose label is desired
	 *
	 * @return classification label (defined by type label_t) of the input
	 *   vector
	 *
	 */
	virtual label_t predict( const arma::vec &predict_vector ) = 0;

	/**
	 * Predict the labels of several vectors.
	 *
	 * Uses the trained algorithm to determine the label of each n-dimensional
	 * column vector in a nxm matrix of entries where each entry is stored in
	 * a column. This method assumes that the training method has already been
	 * completed.
	 *
	 * @param[in] test_mat nxm matrix with each entry in a column
	 *
	 * @return column vector of classification labels (defined by type label_t)
	 *   where each i-th entry corresponds to the i-th column of the input
	 */
	virtual label_t* test( const arma::mat &test_mat ) = 0;

	/**
	 * Determine the error rate for a given test set
	 *
	 * Computes the labels for a given dataset and compares to given known
	 * labels. The resulting comparison is used to determine the overall
	 * error rate of the algorithm for that dataset. This method assumes that
	 * the training method has already been completed.
	 *
	 * @param[in] test_mat nxm matrix with each entry in a column
	 * @param[in] true_labels mx1 column vector of true labels
	 * @param[out] predicted_labels mx1 column vector of predicted labels
	 *
	 * @return fractional error rate
	 */
	virtual double validate( const arma::mat &test_mat,
						const arma::Col<label_t> &true_labels,
						arma::Col<label_t> *predicted_labels = nullptr	) = 0;

	/**
	 * Serialization routine
	 *
	 * Serialize the algorithm to allow for the use of a trained algorithm 
	 * without the need to retrain at every usage. This will help prevent
	 * unnecessary training computations that can be very resource-intensive.
	 * Requires that training method has already been completed.
	 *
	 * @param[in] filename std::string name of file in which to store data
	 */
	 virtual void save( const std::string &filename ) = 0;

	/**
	 * Deserialization routine
	 *
	 * Load a trained algorithm from a file specified by the argument. This
	 * file should correspond to one output by the save routine of the same
	 * class. There are checks in place to ensure that only a file serialized
	 * by the class will be able to be loaded.
	 *
	 * @param[in] filename std::string name of file from which to load data
	 */
	virtual void load( const std::string &filename ) = 0;

};

}

#endif // OCR_CLASSIFIER_CLASSIFIER_H_