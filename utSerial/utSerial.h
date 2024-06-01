//
// utSerial.h
//

#pragma once

#include "gtest/gtest.h"
#include "serial/serial.h"

#ifdef GTEST_OS_WINDOWS
#include "windows.h"
#include "strsafe.h"
#endif

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

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

namespace serial {
	bool operator==(const Timeout& lhs, const Timeout& rhs);
	bool operator!=(const Timeout& lhs, const Timeout& rhs);
}	// namespace serial

namespace utPetoi {
	extern vector <string> commandline;

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

		ostream& operator <<(ostream& os, const PortInfo& rport);

		template <typename T>
		ostream& operator <<(ostream& os, const vector <T>& list)
		{
			for (auto val : list) {
				os << val;
			}
			return os;
		}

		ostream& operator <<(ostream& os, const PortInfo& rport);

		// ====================================================
		// utfSerial - test fixture for Serial class
		// ====================================================
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
				EXPECT_TRUE(parse_commandline());
				EXPECT_FALSE(utSerial.isOpen());
			}
			~utfSerial()
			{
				EXPECT_TRUE(close_port());
			}
		protected:
			bool parse_commandline();
			bool open_port();
			bool close_port();
		};

		// ====================================================
		// utfSerialOpen - test fixture for Serial class open port
		// ====================================================
		class utfSerialOpen : public utfSerial
		{
		protected:
		public:
			utfSerialOpen()
			{
				open_port();
			}
			~utfSerialOpen()
			{
				flush();
				// n.b., ~utfSerial calls close_port
			}
		protected:
			bool flush()
			{
				using namespace std::chrono_literals;

				if (!utSerial.isOpen()) {
					return false;
				}
				EXPECT_NO_THROW(utSerial.flush());
				std::this_thread::sleep_for(16ms);

				string reply{};
				size_t count{};	// track iteration count
				while (0 < utSerial.available()) {
					reply += utSerial.read(1);
					++count;
				}
				return 0 == utSerial.available();
			}
		};

		enum Command : uint8_t
		{
			SHUT_DOWN                   // rest and shutdown all servos
			, SWITCH_GYRO               // switch whether to use IMU data
			, PAUSE_MOTION              // TODO: difference between shutdown?
			, CALIBRATE                 // Calibration mode
			, SWITCH_RECOVERING         // TODO: check if this can be disabled
			, REPEAT_SKILL              // repeat last called skill
			, PLAY_CUSTOM_SKILL         // play custom defined skill
			, MOVE_JOINT_SEQUENCE       // move joints in sequence
			, MOVE_JOINTS_SIMULTANEOUS  // move joints all at once
			, SET_JOINTS                // set all joints at once
			, PLAY_MELODY               // play built-in melody
			, PLAY_CUSTOM_SOUND         // play the cutom provided sound

			, STEPPING      // stepping on the same spot
			, BACK          // going back
			, BACK_LEFT     // going back and left
			, BACK_RIGHT    // going back and right
			, CRAWL         // crawl forward
			, CRAWL_LEFT    // crawl left
			, CRAWL_RIGHT   // crawl right
			, WALK          // walk forward
			, WALK_LEFT     // walk left
			, WALK_RIGHT    // walk right
			, TROT          // trot forward
			, TROT_LEFT     // trot left
			, TROT_RIGHT    // trot right
			, BOUND         // not recommended

			, BALANCE       // balancing mode
			, BUTT_UP       // raise hip
			, CALIB_POSE    // Calibration pose, make easy to calibrate joints
			, REST          // rest mode TODO: difference between SHUT_DOWN
			, SIT
			, SLEEP
			, STRETCH
			, ZERO          // template for designing new posture

			, CHECK_AROUND
			, GREETING
			, PEE
			, PUSH_UP
			, MIMIC_DEATH
			, BACK_FLIP
		};

		// alias for command arguments
		using TaskArgs = vector <int16_t>;

		struct Task
		{
			Command cmd;
			TaskArgs arguments;
			float delay;		// in seconds

			Task(Command _cmd)
				: cmd(_cmd)
				, arguments{}
				, delay(0.f)
			{
			}
			Task(Command _cmd, float _delay)
				: cmd(_cmd)
				, arguments{}
				, delay(_delay)
			{
				//delay = 0.f;	// hack
			}
			Task(Command _cmd, TaskArgs _args, float _delay)
				: cmd(_cmd)
				, arguments{ _args.begin(), _args.end() }
				, delay(_delay)
			{
				//delay = 0.f;	// hack
			}
		};
	}	// namespace utserial
}	// namespace utPetoi
