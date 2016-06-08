#include "util/utilities.h"

int32_t ocr::utilities::swap_endian(const int32_t &number) {
	return __builtin_bswap32(number);
}

int32_t ocr::utilities::read_integer(std::ifstream &file_stream,
	bool do_endian_swap) {

	int32_t number = 0;
	file_stream.read((char*)&number, sizeof(number));

	if ( do_endian_swap )
		number = ocr::utilities::swap_endian(number);

	return number;
}