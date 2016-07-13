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

	size_t nearest_neighbor_index = -1;

	arma::vec distances = arma::vec(this->training_set_.n_cols);
	for ( arma::uword i = 0; i < this->training_set_.n_cols; i++ ) {
		distances[i] = this->metric_->distance(predict_vector, this->training_set_.unsafe_col(i));
	}

	nearest_neighbor_index = distances.index_min();

	return this->training_labels_[nearest_neighbor_index];
}

ocr::label_t* ocr::NearestNeighbor::test( const arma::mat &test_vectors ) {
	ocr::label_t *predicted_labels = 
		(ocr::label_t*)malloc(sizeof(ocr::label_t)*test_vectors.n_cols);

	for ( size_t i = 0; i < test_vectors.n_cols; i++ ) {
		predicted_labels[i] = predict(test_vectors.unsafe_col(i));
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
