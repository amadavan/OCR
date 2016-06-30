#ifndef OCR_UTIL_SERIALIZE_H_
#define OCR_UTIL_SERIALIZE_H_

#include <iostream>

namespace ocr {

class Serializable {

protected:
	/**
	 * Base constructor for Serializable
	 *
	 * The empty constructor for Serializable is defined as protected to ensure 
	 * that no unwitting developer accidently attempts to use it to create an
	 * object.
	 */
	Serializable() {}

public:
	virtual ~Serializable() {}
	
	/**
	 * Serialization routine
	 *
	 * Serialize the class by saving all required information to a stream that
	 * can later be read and used to recreate all necessary information to
	 * restore the class to its original state.
	 *
	 * @param[in] filename std::ostream stream to write save data
	 */
	 virtual void save( const std::ostream &ostream ) = 0;

	/**
	 * Deserialization routine
	 *
	 * Loads all the required information from a stream to restore the class to
	 * a previously created state that has been saved using the save routine.
	 * The restored class should be identical in state to the previously saved
	 * class.
	 *
	 * @param[in] filename std::istream stream to load data from
	 */
	virtual void load( const std::istream &ostream ) = 0;

};

}

#endif // OCR_UTIL_SERIALIZE_H_