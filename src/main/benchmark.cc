#include <chrono>
#include <iostream>

#include "classifier/nearest_neighbor.h"
#include "metric/pnorm_metric.h"
#include "parser/mnist_parser.h"
#include "util/timer.h"

#include "util/principle_component_analysis.h"

// Helper typedef to reduce code repetition. Includes a classifier and a string
// name that will be used to identify the algorithm in the output
typedef std::pair<std::string, ocr::ClassifierInterface*> NamedClassifier;

int main() {

	// Timer to benchmark the training and testing times of the classifiers
	ocr::Timer timer = ocr::Timer();

	// Manhattan-norm Nearest-Neighbor
	ocr::Metric *metric_manhattan = new ocr::PNorm(1);
	ocr::NearestNeighbor *nn_manhattan = new ocr::NearestNeighbor(metric_manhattan);

	// Euclidean-norm Nearest-Neighbor
	ocr::Metric *metric_euclidean = new ocr::PNorm(2);
	ocr::NearestNeighbor *nn_euclidean = new ocr::NearestNeighbor(metric_euclidean);

	// 3-Norm Nearest-Neighbor
	ocr::Metric *metric_3norm = new ocr::PNorm(3);
	ocr::NearestNeighbor *nn_3norm = new ocr::NearestNeighbor(metric_3norm);

	// Create a list of all the classifiers with an identifiable name for easier
	// comparison of output values. Uses the NamedClassifier typedef 
	std::vector<NamedClassifier> classifiers = std::vector<NamedClassifier>();
	classifiers.push_back(NamedClassifier("Manhattan Nearest-Neighbor", nn_manhattan));
	classifiers.push_back(NamedClassifier("Euclidean Nearest-Neighbor", nn_euclidean));
	// classifiers.push_back(NamedClassifier("3-Norm Nearest-Neighbor", nn_3norm));

	// Load the MNist data
	arma::mat mnist_train_images = ocr::mnist::parse_images(
									"data/train-images-idx3-ubyte");
	arma::Col<ocr::label_t> mnist_train_labels = ocr::mnist::parse_labels(
									"data/train-labels-idx1-ubyte");
	arma::mat mnist_test_images = ocr::mnist::parse_images(
									"data/t10k-images-idx3-ubyte");
	arma::Col<ocr::label_t> mnist_test_labels = ocr::mnist::parse_labels(
									"data/t10k-labels-idx1-ubyte");

	// Compute the PCA
	// Uses a value determined iteratively in previous work
	// The current PCA dimension decision implementation provides a value too
	// large and as the value is known, I have decided not to use the dimension
	// decision yet.
	ocr::PCA pca = ocr::PCA(56);
	pca.solve(mnist_train_images);
	// std::cout << pca.get_dimensions() << "\t" << pca.get_percent_variability() << std::endl;
	std::cout << "Principle Component Analysis" << std::endl;
	std::cout << "Method" << "\t\t" << "Dimensions" << "\t" << "Variability (%)" << "\t" << "Time (ms)" << std::endl;
	std::cout << "Auto" << "\t\t" << std::flush;
	pca.set_auto_dimension();
	timer.start();
	pca.solve(mnist_train_images);
	std::cout << pca.get_dimensions() << "\t\t";
	std::cout << pca.get_percent_variability() << "\t\t";
	std::cout << timer.elapsed_ms().count() << std::endl;
	std::cout << "Known Optimal" << "\t" << std::flush;
	pca.set_dimensions(56);
	timer.start();
	pca.solve(mnist_train_images);
	std::cout << pca.get_dimensions() << "\t\t";
	std::cout << pca.get_percent_variability() << "\t\t";
	std::cout << timer.elapsed_ms().count() << std::endl;
	std::cout << std::endl;

	// Reduce the dataset using the computed PCA
	arma::mat mnist_train_images_reduced = pca.project(mnist_train_images);
	arma::mat mnist_test_images_reduced = pca.project(mnist_test_images);

	// Print out a table of train/test times as well as error rate for each
	// algorithm that is used
	std::cout << "Classifier Name" << "\t\t\t" << "Training (ms)" << "\t" << "Testing (ms)" << "\t" << "Error Rate" << std::endl;
	for ( auto c : classifiers ) {
		std::cout << c.first << "\t" << std::flush;

		timer.start();
		c.second->train(mnist_train_images_reduced, mnist_train_labels);
		std::cout << timer.elapsed_ms().count() << "\t\t" << std::flush;

		timer.start();
		double error_rate = c.second->validate(mnist_test_images_reduced, mnist_test_labels);
		std::cout << timer.elapsed_ms().count() << "\t\t" << std::flush;

		std::cout << error_rate;

		std::cout << std::endl;
	}
}