#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		using std::string_view;
		using std::endl;
		using std::chrono::milliseconds;
		using std::this_thread::sleep_for;

		using namespace serial;

		// ================================================================
		// utfExample_NoFlush - tests from serial\serial_example.cpp
		// uses gtest's Value-Parameterized Test
		// ================================================================
		class utfExample_NoFlush : public utfSerialOpen
							, public testing::WithParamInterface <uint32_t>
		{
		protected:
			const string test_string{ "Hello, UNO" };
			const int iter{ 10 };
		public:
			utfExample_NoFlush()
			{
				cout << "Timeout == " << GetParam();
				utSerial.setTimeout(
					Timeout::max()
					, GetParam()
					, 0
					, GetParam()
					, 0
				);
			}
			~utfExample_NoFlush()
			{
			}
		protected:
			bool on_test(int len)
			{
				int count{ 0 };
				while (count < iter) {
					size_t bytes_wrote{ utSerial.write(test_string) };
					string result{ utSerial.read(test_string.length() + len) };
					cout << "Iteration: " << count
						<< ", Bytes written: " << bytes_wrote
						<< ", Bytes read: " << result.length()
						<< ", String read: " << result << endl;

					count += 1;
				}
				return true;
			}
		};

		TEST_P(utfExample_NoFlush, read_more)
		{
			cout << ", asking for 1 more byte than written." << endl;
			on_test(1);
		}
		TEST_P(utfExample_NoFlush, read_match)
		{
			cout << ", asking for exactly what was written." << endl;
			on_test(0);
		}
		TEST_P(utfExample_NoFlush, read_less)
		{
			cout << ", asking for 1 less than was written." << endl;
			on_test(-1);
		}

		INSTANTIATE_TEST_CASE_P(
			TimeoutValue
			, utfExample_NoFlush
			, testing::Values(1000U, 250U)
		);

		// ================================================================
		// utfExample - tests from serial\serial_example.cpp
		// uses gtest's Value-Parameterized Test
		// ================================================================
		class utfExample_Flush : public utfSerialOpen
			, public testing::WithParamInterface <uint32_t>
		{
		protected:
			const string test_string{ "Hello, UNO" };
			const int iter{ 10 };
		public:
			utfExample_Flush()
			{
				cout << "Timeout == " << GetParam();
				utSerial.setTimeout(
					Timeout::max()
					, GetParam()
					, 0
					, GetParam()
					, 0
				);
				EXPECT_TRUE(on_flush_input());
			}
			~utfExample_Flush()
			{
			}
		protected:
			bool on_flush_input()
			{
				sleep_for(milliseconds(15));
				size_t count{ utSerial.available() };
				while (count) {
					utSerial.read(count);
					count = utSerial.available();
				}
				return 0U == utSerial.available();
			}
			bool on_test(int len)
			{
				EXPECT_TRUE(on_flush_input());
				int count{ 0 };
				while (count < iter) {
					size_t bytes_wrote{ utSerial.write(test_string) };
					string result{ utSerial.read(test_string.length() + len) };
					cout << "Iteration: " << count
						<< ", Bytes written: " << bytes_wrote
						<< ", Bytes read: " << result.length()
						<< ", String read: " << result << endl;

					EXPECT_TRUE(on_flush_input());
					count += 1;
				}
				return true;
			}
		};

		TEST_P(utfExample_Flush, read_more)
		{
			cout << ", asking for 1 more byte than written." << endl;
			on_test(1);
		}
		TEST_P(utfExample_Flush, read_match)
		{
			cout << ", asking for exactly what was written." << endl;
			on_test(0);
		}
		TEST_P(utfExample_Flush, read_less)
		{
			cout << ", asking for 1 less than was written." << endl;
			on_test(-1);
		}

		INSTANTIATE_TEST_CASE_P(
			TimeoutValue
			, utfExample_Flush
			, testing::Values(1000U, 250U)
		);
	}	// namespace utserial
}	// namespace utPetoi
