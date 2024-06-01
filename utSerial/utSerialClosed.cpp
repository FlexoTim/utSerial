#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		// ================================================================
		// utfSerialClosed - test fixture for Serial class closed port
		// ================================================================
		using utfSerialClosed = utfSerial;

		// size_t available();
		TEST_F(utfSerialClosed, available) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_EQ(0U, utSerial.available());
		}
		TEST_F(utfSerialClosed, close_nothrow) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_NO_THROW(utSerial.close());
		}
		TEST_F(utfSerialClosed, flush_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.flush(), PortNotOpenedException);
		}
		TEST_F(utfSerialClosed, flushInput_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.flushInput(), PortNotOpenedException);
		}
		TEST_F(utfSerialClosed, flushOutput_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.flushOutput(), PortNotOpenedException);
		}
		TEST_F(utfSerialClosed, isOpen_false) {
			EXPECT_FALSE(utSerial.isOpen());
		}

		TEST_F(utfSerialClosed, open_throw_invalid_argument) {
			ASSERT_FALSE(utSerial.isOpen());
			ASSERT_NO_THROW(utSerial.setPort(""));

			EXPECT_THROW(utSerial.open(), std::invalid_argument);

			ASSERT_NO_THROW(utSerial.setPort(port));
		}
		TEST_F(utfSerialClosed, open_throw_IOException) {
			ASSERT_FALSE(utSerial.isOpen());
			ASSERT_NO_THROW(utSerial.setPort("COM9"));

			EXPECT_THROW(utSerial.open(), IOException);
			expect_error(::GetLastError());

			ASSERT_NO_THROW(utSerial.setPort(port));
		}
		TEST_F(utfSerialClosed, open_throw_SerialException) {
			ASSERT_FALSE(utSerial.isOpen());
			ASSERT_NO_THROW(utSerial.setPort(port));
			ASSERT_NO_THROW(utSerial.setBaudrate(baud));
			ASSERT_NO_THROW(utSerial.setTimeout(ctimeout));
			ASSERT_NO_THROW(utSerial.setBytesize(bytesize));
			ASSERT_NO_THROW(utSerial.setParity(parity));
			ASSERT_NO_THROW(utSerial.setStopbits(stopbits));
			ASSERT_NO_THROW(utSerial.setFlowcontrol(flowcontrol));
			ASSERT_NO_THROW(utSerial.open());
			ASSERT_TRUE(utSerial.isOpen());

			EXPECT_THROW(utSerial.open(), SerialException);

			ASSERT_TRUE(utSerial.isOpen());
			ASSERT_NO_THROW(utSerial.close());
		}

		// std::string read(size_t size = 1);
		TEST_F(utfSerialClosed, read_size_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.read(), PortNotOpenedException);
		}
		// size_t read(std::string& buffer, size_t size = 1);
		TEST_F(utfSerialClosed, read_string_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			string buf;
			EXPECT_THROW(utSerial.read(buf), PortNotOpenedException);
		}
		// size_t read(std::vector<uint8_t>& buffer, size_t size = 1);
		TEST_F(utfSerialClosed, read_vector_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			vector<uint8_t> buf;
			EXPECT_THROW(utSerial.read(buf), PortNotOpenedException);
		}
		// size_t read(uint8_t* buffer, size_t size);
		TEST_F(utfSerialClosed, read_ptr_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			uint8_t buf[32]{};
			EXPECT_THROW(utSerial.read(buf, sizeof(buf)), PortNotOpenedException);
		}

		// std::string readline(size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialClosed, readline_size_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.readline(32), PortNotOpenedException);
		}
		// size_t readline(std::string& buffer, size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialClosed, readline_string_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			string buffer{};
			EXPECT_THROW(utSerial.readline(buffer), PortNotOpenedException);
		}
		// std::vector<std::string> readlines(size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialClosed, readlines_vector_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.readlines(1), PortNotOpenedException);
		}
		// void sendBreak(int duration);
		TEST_F(utfSerialClosed, sendBreak_throw_IOException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.sendBreak(10), IOException);
		}
		// void setBreak(bool level = true);
		TEST_F(utfSerialClosed, setBreak_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.setBreak(), PortNotOpenedException);
		}
		// void setDTR(bool level = true);
		TEST_F(utfSerialClosed, setDTR_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.setDTR(), PortNotOpenedException);
		}
		// void setRTS(bool level = true);
		TEST_F(utfSerialClosed, setRTS_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.setRTS(), PortNotOpenedException);
		}

		// void waitByteTimes(size_t count);
		TEST_F(utfSerialClosed, waitByteTimes_throw_IOException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.waitByteTimes(32), IOException);
		}
		// bool waitForChange();
		TEST_F(utfSerialClosed, waitForChange_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.waitForChange(), PortNotOpenedException);
		}
		// bool waitReadable();
		TEST_F(utfSerialClosed, waitReadable_throw_IOException) {
			ASSERT_FALSE(utSerial.isOpen());
			EXPECT_THROW(utSerial.waitReadable(), IOException);
		}

		// size_t write(const std::string& data);
		TEST_F(utfSerialClosed, write_string_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			string data{};
			EXPECT_THROW(utSerial.write(data), PortNotOpenedException);
		}
		// size_t write(const std::vector<uint8_t>& data);
		TEST_F(utfSerialClosed, write_vector_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			vector <uint8_t> data{ 0 };	// todo: empty vector throws
			EXPECT_THROW(utSerial.write(data), PortNotOpenedException);
		}
		// size_t write(const uint8_t* data, size_t size);
		TEST_F(utfSerialClosed, write_ptr_throw_PortNotOpenedException) {
			ASSERT_FALSE(utSerial.isOpen());
			uint8_t* data{};	// todo: empty vector throws
			EXPECT_THROW(utSerial.write(data, 0), PortNotOpenedException);
		}
	}	// namespace utserial
}	// namespace utPetoi
