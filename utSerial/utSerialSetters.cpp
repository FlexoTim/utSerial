#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		// ================================================================
		// utfSerialSetters - test fixture for Serial class setter functions
		// ================================================================
		using utfSerialSetters = utfSerial;

		TEST_F(utfSerialSetters, setBaudrate_nothrow) {
			ASSERT_NE(0UL, baud);
			ASSERT_EQ(9600UL, utSerial.getBaudrate());	// check Serial default
			EXPECT_NO_THROW(utSerial.setBaudrate(baud));
		}
		TEST_F(utfSerialSetters, setBaudrate_match) {
			ASSERT_NE(0UL, baud);
			ASSERT_EQ(9600UL, utSerial.getBaudrate());
			ASSERT_NO_THROW(utSerial.setBaudrate(baud));
			EXPECT_EQ(baud, utSerial.getBaudrate());
		}
		TEST_F(utfSerialSetters, setBytesize) {
			ASSERT_EQ(bytesize_t::eightbits, utSerial.getBytesize());
			EXPECT_NO_THROW(utSerial.setBytesize(bytesize_t::sixbits));
			EXPECT_EQ(bytesize_t::sixbits, utSerial.getBytesize());
		}
		TEST_F(utfSerialSetters, setFlowcontrol) {
			ASSERT_EQ(default_flowcontrol, utSerial.getFlowcontrol());
			EXPECT_NO_THROW(utSerial.setFlowcontrol(flowcontrol_t::flowcontrol_software));
			EXPECT_EQ(flowcontrol_t::flowcontrol_software, utSerial.getFlowcontrol());
		}
		TEST_F(utfSerialSetters, setParity) {
			ASSERT_EQ(parity_t::parity_none, utSerial.getParity());
			EXPECT_NO_THROW(utSerial.setParity(parity_t::parity_even));
			EXPECT_EQ(parity_t::parity_even, utSerial.getParity());
		}
		TEST_F(utfSerialSetters, setPort) {
			ASSERT_FALSE(port.empty());
			ASSERT_TRUE(utSerial.getPort().empty());
			EXPECT_NO_THROW(utSerial.setPort(port));
			EXPECT_EQ(port, utSerial.getPort());
		}
		TEST_F(utfSerialSetters, setStopbits) {
			ASSERT_EQ(stopbits_t::stopbits_one, utSerial.getStopbits());
			EXPECT_NO_THROW(utSerial.setStopbits(stopbits_t::stopbits_two));
			EXPECT_EQ(stopbits_t::stopbits_two, utSerial.getStopbits());
		}
		TEST_F(utfSerialSetters, setTimeout) {
			ASSERT_EQ(Timeout(), utSerial.getTimeout());
			Timeout expected{ Timeout::simpleTimeout(1000U) };
			EXPECT_NO_THROW(utSerial.setTimeout(expected));
			EXPECT_EQ(expected, utSerial.getTimeout());
		}
	}	// namespace utserial
}	// namespace utPetoi
