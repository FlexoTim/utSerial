#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		// ================================================================
		// utfSerialLoopback - test fixture for Serial class with loopback
		// connector or Arduino sketch
		// ================================================================
		class utfSerialLoopback : public utfSerialOpen
		{
		protected:
		public:
			utfSerialLoopback()
			{
				EXPECT_TRUE(utSerial.isOpen());
				EXPECT_EQ(0U, utSerial.available());
			}
			~utfSerialLoopback()
			{
				flush();
			}
		protected:
		};

		TEST_F(utfSerialLoopback, ctor_available_empty) {
			EXPECT_EQ(0U, utSerial.available());
		}
		TEST_F(utfSerialLoopback, write_string_match_count) {
			string data{ "0123456789" };
			EXPECT_EQ(data.length(), utSerial.write(data));
		}
		TEST_F(utfSerialLoopback, write_string_match) {
			string data{ "0123456789" };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(data, utSerial.read(data.length()));
		}
		// size_t write(const uint8_t* data, size_t size);
		TEST_F(utfSerialLoopback, write_ptr_match_count) {
			uint8_t data[]{ "0123456789" };
			size_t len{ sizeof(data) };
			string strdata{ &data[0], data + len };
			EXPECT_EQ(len, utSerial.write(data, len));
		}
		TEST_F(utfSerialLoopback, write_ptr_match) {
			uint8_t data[]{ "0123456789" };
			size_t len{ sizeof(data) };
			string strdata{ &data[0], data + len };
			ASSERT_EQ(len, utSerial.write(data, len));
			EXPECT_EQ(strdata, utSerial.read(len));
		}
		// size_t write(const std::vector <uint8_t>& data);
		TEST_F(utfSerialLoopback, write_vector_match_count) {
			vector <uint8_t> data{
				'0','1','2','3','4','5','6','7','8','9'
			};
			EXPECT_EQ(data.size(), utSerial.write(data));
		}
		TEST_F(utfSerialLoopback, write_vector_match) {
			vector <uint8_t> data{
				'0','1','2','3','4','5','6','7','8','9'
			};
			string strdata{ data.begin(), data.end() };
			ASSERT_EQ(data.size(), utSerial.write(data));
			EXPECT_EQ(strdata, utSerial.read(data.size()));
		}
		// size_t read(uint8_t* buffer, size_t size);
		TEST_F(utfSerialLoopback, read_ptr_match_count) {
			string data{ "0123456789" };
			uint8_t buf[10]{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(sizeof(buf), utSerial.read(buf, sizeof(buf)));
		}
		TEST_F(utfSerialLoopback, read_ptr_match) {
			string data{ "0123456789" };
			uint8_t buf[10]{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			ASSERT_EQ(sizeof(buf), utSerial.read(buf, sizeof(buf)));
			EXPECT_EQ(data, string(buf, buf + sizeof(buf)));
		}
		// size_t read(std::vector <uint8_t>& buffer, size_t size = 1);
		TEST_F(utfSerialLoopback, read_vector_match_count) {
			string data{ "0123456789" };
			vector <uint8_t> buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(data.length(), utSerial.read(buffer, data.length()));
		}
		TEST_F(utfSerialLoopback, read_vector_match) {
			string data{ "0123456789" };
			vector <uint8_t> buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			ASSERT_EQ(data.length(), utSerial.read(buffer, data.length()));
			ASSERT_EQ(data.length(), buffer.size());
			EXPECT_EQ(data, string(buffer.begin(), buffer.end()));
		}
		// size_t read(std::string& buffer, size_t size = 1);
		TEST_F(utfSerialLoopback, read_string_match_count) {
			string data{ "0123456789" };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(data.length(), utSerial.read(buffer, data.length()));
		}
		TEST_F(utfSerialLoopback, read_string_match) {
			string data{ "0123456789" };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			ASSERT_EQ(data.length(), utSerial.read(buffer, data.length()));
			EXPECT_EQ(data, buffer);
		}
		// size_t readline(std::string& buffer, size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialLoopback, readline_newline_match_count) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(line1.length(), utSerial.readline(buffer, data.length()));
		}
		TEST_F(utfSerialLoopback, readline_newline_match) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			ASSERT_EQ(line1.length(), utSerial.readline(buffer, data.length()));
			EXPECT_EQ(line1, buffer);	// n.b., eol included
		}
		TEST_F(utfSerialLoopback, readline_tilda_match_count) {
			string line1{ "0123456789~" };
			string line2{ "ABCDEFGHIJ~" };
			string data{ line1 + line2 };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(line1.length(), utSerial.readline(buffer, data.length(), "~"));
		}
		TEST_F(utfSerialLoopback, readline_tilda_match) {
			string line1{ "0123456789~" };
			string line2{ "ABCDEFGHIJ~" };
			string data{ line1 + line2 };
			string buffer{};
			ASSERT_EQ(data.length(), utSerial.write(data));
			ASSERT_EQ(line1.length(), utSerial.readline(buffer, data.length(), "~"));
			EXPECT_EQ(line1, buffer);	// n.b., eol included
		}
		// std::string readline(size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialLoopback, readline_string_newline_match_count) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(line1.length(), utSerial.readline(data.length()).length());
		}
		TEST_F(utfSerialLoopback, readline_string_newline_match) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(line1, utSerial.readline(data.length()));
		}
		TEST_F(utfSerialLoopback, readline_no_eol) {
			string line1{ "0123456789" };
			string line2{ "ABCDEFGHIJ" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			EXPECT_EQ(data, utSerial.readline(data.length()));
		}

		// std::vector<std::string> readlines(size_t size = 65536, std::string eol = "\n");
		TEST_F(utfSerialLoopback, readlines_newline_match_count) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			vector <string> buffer{ utSerial.readlines(data.length()) };
			EXPECT_EQ(2, buffer.size());
		}
		TEST_F(utfSerialLoopback, readlines_newline_match) {
			string line1{ "0123456789\n" };
			string line2{ "ABCDEFGHIJ\n" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			vector <string> buffer{ utSerial.readlines(data.length()) };
			ASSERT_EQ(2, buffer.size());
			EXPECT_EQ(line1, buffer[0]);
			EXPECT_EQ(line2, buffer[1]);
		}
		TEST_F(utfSerialLoopback, readlines_no_eol) {
			string line1{ "0123456789" };
			string line2{ "ABCDEFGHIJ" };
			string data{ line1 + line2 };
			ASSERT_EQ(data.length(), utSerial.write(data));
			vector <string> buffer{ utSerial.readlines(data.length()) };
			ASSERT_EQ(1, buffer.size());
			EXPECT_EQ(data, buffer[0]);
		}
	}	// namespace utserial
}	// namespace utPetoi
