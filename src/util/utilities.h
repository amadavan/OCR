#ifndef OCR_UTIL_UTILITIES_H_
#define OCR_UTIL_UTILITIES_H_

#include <fstream>

namespace ocr {
	namespace utilities {
		/**
		 * Endian swap of 4-byte variable
		 *
		 * Determine the endian-swapped value of a variable of size 4 bytes.
		 *
		 * @param[in] variable 4-byte variable whose endian will be swapped
		 *
		 * @return 32-bit integer input with endian swapped
		 */
		int32_t swap_endian(const int32_t &variable);

		/**
		 * Read 4-byte integer from input file stream
		 *
		 * Given an input file stream, reads an integer and performs an endian
		 * swap if specified.
		 *
		 * @param[in] file_stream input file stream from which to read integer
		 * @param[in] do_endian_swap boolean value specifying whether or not to
		 *   do endian swap (default = true)
		 *
		 * @return integer value read from file and endian swapped if necessary
		 */
		int32_t read_integer(std::ifstream &file_stream,
							bool do_endian_swap = true);
	}
}

#endif // OCR_UTIL_UTILITIES_H_