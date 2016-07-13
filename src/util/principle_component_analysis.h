#ifndef OCR_UTIL_PRINCIPLE_COMPONENT_ANALYSIS_H_
#define OCR_UTIL_PRINCIPLE_COMPONENT_ANALYSIS_H_

#include <float.h>

#include <cmath>

#include <armadillo>

#include "util/ocrtypes.h"

namespace ocr {

/**
 * A Principle Component Analysis (PCA) implementation.
 *
 * Defines an implementation of PCA with the ability to designate how the
 * projection is found and the reduced space.
 */
class PCA {
public:
	/**
	 * Default constructor for PCA uses automatic determination of dimensions
	 *
	 * Constructs the PCA object that will be used to determine the projections
	 * of the original dataset to and from the reduced subspace. By default, it
	 * determines the number of dimensions to retain based on analysis of the
	 * amounnt of variability measured.
	 */
	PCA();

	/**
	 * Constructor for PCA providing a set number of reduced dimensions
	 * 
	 * Constructs the PCA object with the number of dimensions to be included in
	 * the reduced subspace.
	 *
	 * @param[in] num_reduced_dimensions number of dimensions to include in
	 * reduced subspace
	 */
	PCA(int num_reduced_dimensions);

	/**
	 * Consutuctor for PCA providing percent variability
	 *
	 * Constructs the PCA object while specifying the total percentage of
	 * variability contained in the reduced subspace.
	 *
	 * @param[in] percent_variability percentage of original space's variability
	 * contained in reduced subspace
	 */
	PCA(double percent_variability);

	~PCA() {}

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
	void solve( const arma::mat &dataset );

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
	arma::mat project( const arma::mat &mat, bool reverse = false );

	/**
	 * Set the PCA to solve for a specified percent variability
	 *
	 * Specifies a floating point value of variability that will be included in
	 * the projection. This value represents a minimum bound and ensures that
	 * at least this much variability is included in the projection.
	 *
	 * @param[in] variability Minimum percent variability in projection
	 */
	void set_percent_variability(double variability);

	/**
	 * Returns the percent variability of the PCA solution or set-point
	 *
	 * Depending on the current state of the PCA solver, this can return two
	 * different values. The first is if the PCA has not yet been solved. If
	 * that is the case, this value will be the percent variability specified by
	 * the user if they wish to use the variability dimension select mode, or 
	 * the default value of 0. Alternatively, if the algorithm has been run,
	 * this will return the percent variability included in the data regardless 
	 * of algorithm used.
	 *
	 * @param[out] variability percentage variability included in PCA solution
	 */
	double get_percent_variability();

	/**
	 * Set the PCA to solve for a specified number of dimensions
	 *
	 * Defines a set number of dimensions to be included in the projection space
	 * and to be solved for in the PCA. In other words, the top dimensions
	 * eigenvectors will be included in the projection.
	 *
	 * @param[in] dimensions Number of dimensions to include in PCA projection
	 */
	void set_dimensions(uint32_t dimensions);

	/**
	 * Returns number of dimensions in PCA
	 *
	 * Depending on whether or not the solve function has been run, this can
	 * return two things. If solve was called and set_dimensions has not been 
	 * called since, this will return the number of dimensions that the solve
	 * function reduced the dataset to. If set_dimensions has been called or
	 * solve has not been called, this will return the value specified in the
	 * constructor or set_dimensions. If no value was set, it defaults to 0.
	 *
	 * @param[out] n_dimensions Number of dimensions in PCA
	 */
	uint32_t get_dimensions();

	/**
	 * Use Minka's MLE to determine number of dimensions
	 *
	 * When performing a solve, the algorithm will determine the appropriate
	 * number of dimensions by performing Minka's MLE that can be found here <a
	 * href="https://uwaterloo.ca/data-science/sites/ca.data-science/files/
	 * uploads/files/automatic-dimensionality-selection-from-scree-plot-use-of-
	 * profile-likelihood.pdf">here</a>.
	 */
	void set_auto_dimension();

private:
	/**
	 * Enumeration of different ways of determining PCA dimensions
	 *
	 * Enumerated type that acts as a switch between different ways of
	 * calculating the number of dimensions to be included in the PCA. These
	 * include AUTO which uses Minka's MLE method, NUM_DIMENSIONS which sets a
	 * number of dimensions, and PERCENT_VARIABILITY which defines a minimum
	 * variability bound to be included in the projection.
	 */
	enum Mode {
		AUTO,
		NUM_DIMENSIONS,
		PERCENT_VARIABILITY
	};

	arma::mat projection_matrix_; /// Matrix containing left-multiply projection
	uint32_t num_reduced_dimensions_; /// Number of dimensions
	double percent_variability_; // Percent variability
	Mode dimension_select_mode_; // Method of selecting number of dimensions

	/**
	 * Return number of dimensions using Minka's MLE
	 *
	 * Performs Minka's MLE estimation that can be found here <a href="https://uwaterloo.ca/data-science/sites/ca.data-science/files/uploads/files/automatic-dimensionality-selection-from-scree-plot-use-of-profile-likelihood.pdf">here</a>.
	 * Returns the Maximum Likelihood number of dimensions.
	 *
	 * @param[in] eigenvalues A list of eigenvalues in descending order
	 * @param[in] n_samples Number of samples in dataset
	 * @param[out] dimensions Maximum likelihood number of dimensions.
	 */
	size_t determine_dimensions(const arma::vec &eigenvalues,
			const size_t n_samples);

};

}

#endif // OCR_UTIL_PRINCIPLE_COMPONENT_ANALYSIS_H_