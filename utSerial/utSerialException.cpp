#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		using utfSerialException = utfwin32;

		TEST_F(utfSerialException, SerialException_copy_ctor_valid) {
			SerialException A{ "SerialException A" };
			SerialException B{ A };
			EXPECT_EQ(string(A.what()), string(B.what()));
		}

		TEST_F(utfSerialException, IOException_copy_ctor_valid) {
			IOException A{ __FILE__, __LINE__, "IOException A" };
			IOException B{ A };
			EXPECT_EQ(string(A.what()), string(B.what()));
		}

		TEST_F(utfSerialException, PortNotOpenedException_copy_ctor_valid) {
			PortNotOpenedException A{ "PortNotOpenedException A" };
			PortNotOpenedException B{ A };
			EXPECT_EQ(string(A.what()), string(B.what()));
		}

	}	// namespace utserial
}	// namespace utPetoi
