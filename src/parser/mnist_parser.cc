#include "parser/mnist_parser.h"

arma::mat ocr::mnist::parse_images(const std::string& filename) {

	arma::mat image_set;

	std::ifstream file = std::ifstream(filename.c_str(), std::ios::binary);
	if ( file.is_open() ) {

		int32_t magic_number = ocr::utilities::read_integer(file, true);
		int32_t num_images = ocr::utilities::read_integer(file, true);
		int32_t num_rows = ocr::utilities::read_integer(file, true);
		int32_t num_cols = ocr::utilities::read_integer(file, true);
		int32_t num_vars = num_rows*num_cols;
		image_set = arma::mat(num_rows*num_cols, num_images);

		for ( size_t i = 0; i < num_images; i++ )
		{
			unsigned char *data_buffer = (unsigned char*)malloc(num_vars);
			file.read((char*)data_buffer, num_vars);
			for ( int j = 0; j < num_vars; j++ )
			{
				image_set.at(j, i) = data_buffer[j];
			}
		}
	}

	return image_set;
}

arma::Col<ocr::label_t> ocr::mnist::parse_labels(const std::string& filename) {

	arma::Col<ocr::label_t> label_set;

	std::ifstream file = std::ifstream(filename.c_str(), std::ios::binary);
	if ( file.is_open() )
	{
		int32_t magic_number = ocr::utilities::read_integer(file, true);
		int32_t num_images = ocr::utilities::read_integer(file, true);
		label_set = arma::Col<ocr::label_t>(num_images);

		unsigned char *data_buffer = (unsigned char*)malloc(num_images);
		file.read((char*)data_buffer, num_images);
		for ( int i = 0; i < num_images; i++ )
		{
			label_set[i] = (int32_t)data_buffer[i];
		}

	}

	return label_set;
}