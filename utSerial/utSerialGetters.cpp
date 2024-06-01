#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		// ================================================================
	// utfSerialGetters - test fixture for Serial class getter functions
	// ================================================================
		using utfSerialGetters = utfSerial;

		TEST_F(utfSerialGetters, getBaudrate) {
			EXPECT_EQ(9600U, utSerial.getBaudrate());
		}
		TEST_F(utfSerialGetters, getBytesize) {
			EXPECT_EQ(bytesize_t::eightbits, utSerial.getBytesize());
		}
		TEST_F(utfSerialGetters, getCD_throw_PortNotOpenedException) {
			EXPECT_THROW(utSerial.getCD(), PortNotOpenedException);
		}
		TEST_F(utfSerialGetters, getCTS_throw_PortNotOpenedException) {
			EXPECT_THROW(utSerial.getCTS(), PortNotOpenedException);
		}
		TEST_F(utfSerialGetters, getDSR_throw_PortNotOpenedException) {
			EXPECT_THROW(utSerial.getDSR(), PortNotOpenedException);
		}
		TEST_F(utfSerialGetters, getFlowcontrol) {
			EXPECT_EQ(default_flowcontrol, utSerial.getFlowcontrol());
		}
		TEST_F(utfSerialGetters, getParity) {
			EXPECT_EQ(parity_t::parity_none, utSerial.getParity());
		}
		TEST_F(utfSerialGetters, getPort) {
			EXPECT_TRUE(utSerial.getPort().empty());
		}
		TEST_F(utfSerialGetters, getRI_throw) {
			EXPECT_ANY_THROW(utSerial.getRI());
		}
		TEST_F(utfSerialGetters, getStopbits) {
			EXPECT_EQ(stopbits_t::stopbits_one, utSerial.getStopbits());
		}
		TEST_F(utfSerialGetters, getTimeout) {
			EXPECT_EQ(Timeout(), utSerial.getTimeout());
		}

	}	// namespace utserial
}	// namespace utPetoi
