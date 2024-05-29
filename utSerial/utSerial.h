//
// utSerial.h
//

#pragma once

#include "gtest/gtest.h"

#include <string>
#include <iostream>

#ifdef GTEST_OS_WINDOWS
#include "windows.h"
#include "strsafe.h"
#endif

#include "serial/serial.h"

using std::string;
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

}	// namespace utPetoi
