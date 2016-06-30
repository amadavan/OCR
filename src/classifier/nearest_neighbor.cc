#include "classifier/nearest_neighbor.h"

ocr::NearestNeighbor::NearestNeighbor( ocr::Metric *metric ) {
	this->metric_ = metric;
}

void ocr::NearestNeighbor::train( const arma::mat &training_set,
	const arma::Col<ocr::label_t> &training_labels) {

	this->training_set_ = training_set;
	this->training_labels_ = training_labels;
}

ocr::label_t ocr::NearestNeighbor::predict( const arma::vec &predict_vector ) {

	double distance = 0;
	double minimum_distance = DBL_MAX;
	size_t nearest_neighbor_index = -1;

	for ( size_t i = 0; i < this->training_set_.n_cols; i++ )
	{
		distance = this->metric_->distance(predict_vector, this->training_set_);

		if ( distance < minimum_distance )
		{
			nearest_neighbor_index = i;
			minimum_distance = distance;
		}
	}

	return this->training_labels_[nearest_neighbor_index];
}

ocr::label_t* ocr::NearestNeighbor::test( const arma::mat &test_vectors ) {
	ocr::label_t *predicted_labels = 
		(ocr::label_t*)malloc(sizeof(ocr::label_t)*test_vectors.n_cols);

	for ( size_t i = 0; i < test_vectors.n_cols; i++ ) {
		predicted_labels[i] = predict(test_vectors.col(i));
	}

	return &predicted_labels[0];
}

double ocr::NearestNeighbor::validate( const arma::mat &test_vectors,
	const arma::Col<ocr::label_t> &real_labels,
	arma::Col<ocr::label_t> *predicted_labels) {

	ocr::label_t *test_labels = test(test_vectors);
	size_t errors = 0;

	for ( int i = 0; i < test_vectors.n_cols; i++ ) {
		errors += ( test_labels[i] != real_labels[i] );
	}

	return 1.0*errors/test_vectors.n_cols;
}

void ocr::NearestNeighbor::save( const std::ostream &filename ) {

}

void ocr::NearestNeighbor::load( const std::istream &filename ) {

}
