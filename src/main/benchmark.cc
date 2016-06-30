#include <chrono>
#include <iostream>

#include "classifier/nearest_neighbor.h"
#include "metric/pnorm_metric.h"
#include "parser/mnist_parser.h"
#include "util/timer.h"

// Helper typedef to reduce code repetition. Includes a classifier and a string
// name that will be used to identify the algorithm in the output
typedef std::pair<std::string, ocr::ClassifierInterface*> NamedClassifier;

int main() {

	// Manhattan-norm Nearest-Neighbor
	ocr::Metric *metric_manhattan = new ocr::PNorm(1);
	ocr::NearestNeighbor *nn_manhattan = new ocr::NearestNeighbor(metric_manhattan);

	// Euclidean-norm Nearest-Neighbor
	ocr::Metric *metric_euclidean = new ocr::PNorm(2);
	ocr::NearestNeighbor *nn_euclidean = new ocr::NearestNeighbor(metric_euclidean);

	// Create a list of all the classifiers with an identifiable name for easier
	// comparison of output values. Uses the NamedClassifier typedef 
	std::vector<NamedClassifier> classifiers = std::vector<NamedClassifier>();
	classifiers.push_back(NamedClassifier("Manhattan Nearest-Neighbor", nn_manhattan));
	classifiers.push_back(NamedClassifier("Euclidean Nearest-Neighbor", nn_euclidean));

	// Load the MNist data
	arma::mat mnist_test_images = ocr::mnist::parse_images(
									"data/t10k-images-idx3-ubyte");
	arma::Col<ocr::label_t> mnist_test_labels = ocr::mnist::parse_labels(
									"data/t10k-labels-idx1-ubyte");
	arma::mat mnist_train_images = ocr::mnist::parse_images(
									"data/train-images-idx3-ubyte");
	arma::Col<ocr::label_t> mnist_train_labels = ocr::mnist::parse_labels(
									"data/train-labels-idx1-ubyte");

	// Timer to benchmark the training and testing times of the classifiers
	ocr::Timer timer = ocr::Timer();

	// Print out a table of train/test times as well as error rate for each
	// algorithm that is used
	std::cout << "Classifier Name" << "\t\t\t" << "Training (ms)" << "\t" << "Testing (ms)" << "\t" << "Error Rate" << std::endl;
	for ( auto c : classifiers ) {
		std::cout << c.first << "\t" << std::flush;

		timer.start();
		c.second->train(mnist_train_images, mnist_train_labels);
		std::cout << timer.elapsed_ms().count() << "\t\t" << std::flush;

		timer.start();
		double error_rate = c.second->validate(mnist_test_images, mnist_test_labels);
		std::cout << timer.elapsed_ms().count() << "\t\t" << std::flush;

		std::cout << error_rate;

		std::cout << std::endl;
	}
}