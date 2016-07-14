#include "util/principle_component_analysis.h"

ocr::PCA::PCA() {
	this->dimension_select_mode_ = AUTO;
}

ocr::PCA::PCA(int num_reduced_dimensions) {
	this->num_reduced_dimensions_ = num_reduced_dimensions;

	if ( num_reduced_dimensions <= 0 ) {
		this->dimension_select_mode_ = AUTO;
	}
	else {
		this->dimension_select_mode_ = NUM_DIMENSIONS;
	}
}

ocr::PCA::PCA(double percent_variability) {
	this->percent_variability_ = percent_variability;
	this->dimension_select_mode_ = PERCENT_VARIABILITY;
}

void ocr::PCA::solve( const arma::mat &dataset ) {

	size_t num_vars = dataset.n_rows;

	arma::mat dataset_mean = arma::mean(dataset,1);

	arma::mat dataset_0mean = dataset;
	dataset_0mean.each_col() -= dataset_mean;

	arma::mat M = arma::mat(num_vars, num_vars);
	arma::vec S = arma::vec(num_vars);
	arma::mat N = arma::mat(num_vars, num_vars);
	arma::svd_econ(M,S,N, dataset_0mean.t(), "right");
	arma::mat eigenvectors = N;
	arma::vec eigenvalues = arma::square(S)/num_vars;

	arma::vec percent_variability = arma::cumsum(eigenvalues)/arma::sum(eigenvalues);
	switch ( this->dimension_select_mode_ ) {
		case AUTO:
			this->num_reduced_dimensions_ =
				determine_dimensions(eigenvalues, dataset.n_cols);
		case NUM_DIMENSIONS:
			this->percent_variability_ =
				percent_variability[this->num_reduced_dimensions_-1];
			break;
		case PERCENT_VARIABILITY:
			arma::uvec dimension_index =
				find(percent_variability<=this->percent_variability_,1,"last");
			this->num_reduced_dimensions_ = dimension_index[0]+1;
			break;
	}

	this->projection_matrix_ = eigenvectors.cols(0, this->num_reduced_dimensions_-1).t();
	return;
}

arma::mat ocr::PCA::project( const arma::mat &dataset, bool reverse ) {

	if ( reverse ) {
		return this->projection_matrix_.t() * dataset;
	}
	else {
		return this->projection_matrix_ * dataset;
	}

}

void ocr::PCA::set_percent_variability(double variability) {
	this->percent_variability_ = variability;
	this->dimension_select_mode_ = PERCENT_VARIABILITY;
}

double ocr::PCA::get_percent_variability() {
	return this->percent_variability_;
}

void ocr::PCA::set_dimensions(uint32_t dimensions) {
	this->num_reduced_dimensions_ = dimensions;
	this->dimension_select_mode_ = NUM_DIMENSIONS;
}

uint32_t ocr::PCA::get_dimensions() {
	return this->num_reduced_dimensions_;
}

void ocr::PCA::set_auto_dimension() {
	this->dimension_select_mode_ = AUTO;
}

size_t ocr::PCA::determine_dimensions(const arma::vec &eigenvalues,
		const size_t n_samples) {
	const size_t d = eigenvalues.n_rows;
	const size_t N = n_samples;

	arma::vec likelihood = arma::vec(d);
	likelihood[0] = -DBL_MAX;

	for ( size_t k = 1; k < d; k++ ) {
		arma::vec eigenvalue_estimate = eigenvalues;
		eigenvalue_estimate.rows(k,d-1).each_row() =
				arma::rowvec({arma::mean(eigenvalue_estimate.rows(k,d-1))});

		size_t m = (size_t)(d*k - k*(k-1)/2.0);
		// size_t m = (size_t)(d*(d-1.)/2. - (d-k)*(d-k-1.)/2.);

		double pD = 1./2*k*log(2.) + (m+k)/2.*log(2*M_PI) - k/2.*log(N);

		for ( size_t i = 1; i <= k; i++ ) {
			double l = (d - i + 1.)/2;
			pD += lgamma(l) - l*log(M_PI) - N/2*log(eigenvalues[i-1]);
		}

		double v = 0;
		for ( size_t i = k+1; i <= d; i++ ) {
			v += eigenvalues[i-1];
		}
		v /= (d-k);
		pD -= N*(d-k)/2.*log(v);

		double log_det_Az = 0.;
		for ( size_t i = 1; i <= k; i++ ) {
			for ( size_t j = i+1; j <= d; j++ ) {
				log_det_Az += log(
					(1/eigenvalue_estimate[j-1] - 1/eigenvalue_estimate[i-1])
						* (eigenvalues[i-1] - eigenvalues[j-1])) + log(N);
			}
		}
		pD -= 1/2 * log_det_Az;

		likelihood[k] = pD;
	}

	return likelihood.index_max();
}