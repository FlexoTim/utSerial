//
// utSerial.h
//

#pragma once

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#ifdef GTEST_OS_WINDOWS
#include "windows.h"
#include "strsafe.h"
#endif

#include "serial/serial.h"

using std::string;
using std::ostream;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::cout;

using namespace ::testing;

#ifdef DISABLED_CODE
#else
#endif	// DISABLED_CODE

namespace utPetoi {

	// ====================================================
	// utfwin32 - Windows base unit test fixture class
	// ====================================================
	class utfwin32 : public testing::Test
	{
#ifdef GTEST_OS_WINDOWS
	protected:
		DWORD expected_error{ ERROR_SUCCESS };

	public:
		utfwin32()
		{
			// flush errors
			on_error(TEXT(__FUNCTION__));
		}

		~utfwin32()
		{
			// report errors
			on_error(TEXT(__FUNCTION__));
		}
	protected:
		DWORD expect_error(DWORD dw = ERROR_SUCCESS);
		void on_error(LPCTSTR lpszFunction, DWORD dw = ::GetLastError());
#else
		// !GTEST_OS_WINDOWS
		// stub API's
	protected:
		unsigned long expect_error(unsigned long dw) { return 0UL; }
		void on_error(const char*, unsigned long) {}
#endif
	};

	namespace utserial {
		using namespace serial;

		template <typename T>
		ostream& operator <<(ostream& os, const vector <T>& list)
		{
			for (auto val : list) {
				os << val;
			}
			return os;
		}

		ostream& operator <<(ostream& os, const PortInfo& rport);

		// ================================================================
		// utfSerial - test fixture for Serial class
		// ================================================================
		// default values
		const string default_port{ "COM6" };
		const flowcontrol_t default_flowcontrol{ flowcontrol_none };
		const uint32_t default_timeout{ 16U };

		class utfSerial : public utfwin32
		{
		protected:
			// serial port ctor parameters
			string port{ default_port };
			unsigned long baud{ 115200 };
			uint32_t timeout{ default_timeout };
			Timeout ctimeout{ Timeout::simpleTimeout(timeout) };
			bytesize_t bytesize{ eightbits };
			parity_t parity{ parity_none };
			stopbits_t stopbits{ stopbits_one };
			flowcontrol_t flowcontrol{ default_flowcontrol };

			Serial utSerial{};	// serial port under test
			// n.b., Serial default ctor

		public:
			utfSerial()
			{
				EXPECT_FALSE(utSerial.isOpen());
			}
			~utfSerial()
			{
				EXPECT_TRUE(close_port());
			}
		protected:
			bool open_port();
			bool close_port();
		};
	}	// namespace utserial

}	// namespace utPetoi
