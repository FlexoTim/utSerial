#include "utserial.h"

namespace utPetoi {
	namespace utserial {

		TEST_F(utfSerialOpen, available_empty) {
			EXPECT_EQ(0U, utSerial.available());
		}
		TEST_F(utfSerialOpen, close_nothrow) {
			ASSERT_TRUE(utSerial.isOpen());
			EXPECT_NO_THROW(utSerial.close());
		}
		TEST_F(utfSerialOpen, close_is_closed) {
			ASSERT_TRUE(utSerial.isOpen());
			ASSERT_NO_THROW(utSerial.close());
			EXPECT_FALSE(utSerial.isOpen());
		}
		TEST_F(utfSerialOpen, flush_nothrow) {
			EXPECT_NO_THROW(utSerial.flush());
		}
		TEST_F(utfSerialOpen, flush_empty) {
			ASSERT_NO_THROW(utSerial.flush());
			EXPECT_EQ(0, utSerial.available());
		}
		TEST_F(utfSerialOpen, flushInput_nothrow) {
			EXPECT_NO_THROW(utSerial.flushInput());
		}
		TEST_F(utfSerialOpen, flushOutput_nothrow) {
			EXPECT_NO_THROW(utSerial.flushOutput());
		}

		TEST_F(utfSerialOpen, read_size_zero_nothrow) {
			EXPECT_NO_THROW(utSerial.read(0));
		}
		TEST_F(utfSerialOpen, read_size_nothrow) {
			EXPECT_NO_THROW(utSerial.read());
		}
		TEST_F(utfSerialOpen, read_size_match) {
			string data{ "0123456789" };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(string("0"), utSerial.read());
		}
		TEST_F(utfSerialOpen, read_match_size_match) {
			string data{ "0123456789" };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(data, utSerial.read(data.length()));
		}

		TEST_F(utfSerialOpen, read_string_nothrow) {
			string buf;
			EXPECT_NO_THROW(utSerial.read(buf, 1));
		}
		TEST_F(utfSerialOpen, read_string_empty) {
			string buf;
			EXPECT_EQ(0, utSerial.read(buf, 1));
		}
		TEST_F(utfSerialOpen, read_vector_empty) {
			vector <uint8_t> buf;
			EXPECT_EQ(0, utSerial.read(buf, 1));
		}
		TEST_F(utfSerialOpen, read_ptr_isempty) {
			uint8_t buf[16]{};
			EXPECT_EQ(0, utSerial.read(buf, sizeof(buf)));
		}
		TEST_F(utfSerialOpen, readline_size_nothrow) {
			EXPECT_NO_THROW(utSerial.readline(32));
		}
		TEST_F(utfSerialOpen, readline_size_empty) {
			EXPECT_TRUE(utSerial.readline(32).empty());
		}
		TEST_F(utfSerialOpen, readline_string_empty) {
			string buffer{};
			EXPECT_EQ(0, utSerial.readline(buffer, 1));
		}
		TEST_F(utfSerialOpen, readlines_vector_empty) {
			EXPECT_TRUE(utSerial.readlines(1).empty());
		}
		TEST_F(utfSerialOpen, sendBreak_throw_IOException) {
			EXPECT_THROW(utSerial.sendBreak(10), IOException);
		}
		TEST_F(utfSerialOpen, setBreak_nothrow) {
			EXPECT_NO_THROW(utSerial.setBreak());
		}
		TEST_F(utfSerialOpen, setDTR_nothrow) {
			EXPECT_NO_THROW(utSerial.setDTR());
		}
		TEST_F(utfSerialOpen, setRTS_nothrow) {
			EXPECT_NO_THROW(utSerial.setRTS());
		}
		TEST_F(utfSerialOpen, waitByteTimes_throw_IOException) {
			EXPECT_THROW(utSerial.waitByteTimes(8), IOException);
		}
		// waitForChange blocks indefinitely
		TEST_F(utfSerialOpen, DISABLED_waitForChange_nothrow) {
			EXPECT_NO_THROW(utSerial.waitForChange());
		}
		TEST_F(utfSerialOpen, waitReadable_throw_IOException) {
			EXPECT_THROW(utSerial.waitReadable(), IOException);
		}

		TEST_F(utfSerialOpen, write_empty_string_nothrow) {
			string data{};
			EXPECT_NO_THROW(utSerial.write(data));
		}
		TEST_F(utfSerialOpen, write_empty_string_zero) {
			string data{};
			EXPECT_EQ(0, utSerial.write(data));
		}
		TEST_F(utfSerialOpen, write_string_nothrow) {
			string data{ "0123456789" };
			EXPECT_NO_THROW(utSerial.write(data));
		}
		TEST_F(utfSerialOpen, write_string_match_count) {
			string data{ "0123456789" };
			EXPECT_EQ(data.length(), utSerial.write(data));
		}

		// size_t write(const std::vector<uint8_t>& data);
		// exception terminates testing
		TEST_F(utfSerialOpen, DISABLED_write_empty_vector_throw) {
			vector <uint8_t> data{};
			EXPECT_ANY_THROW(utSerial.write(data));
		}
		// size_t write(const uint8_t* data, size_t size);
		TEST_F(utfSerialOpen, write_nullptr_zero_nothrow) {
			EXPECT_NO_THROW(utSerial.write(nullptr, 0));
		}
		TEST_F(utfSerialOpen, write_dereference_nullptr_throw) {
			EXPECT_THROW(utSerial.write(nullptr, 1), IOException);
			//expect_error(ERROR_NOACCESS);		
		}
		TEST_F(utfSerialOpen, write_nullptr_zero) {
			EXPECT_EQ(0, utSerial.write(nullptr, 0));
		}
		TEST_F(utfSerialOpen, write_default_ptr_nothrow) {
			uint8_t* data{};	// todo: empty vector throws
			EXPECT_NO_THROW(utSerial.write(data, 0));
		}
		TEST_F(utfSerialOpen, write_default_ptr_zero) {
			uint8_t* data{};	// todo: empty vector throws
			EXPECT_EQ(0, utSerial.write(data, 0));
		}
	}	// namespace utserial
}	// namespace utPetoi
