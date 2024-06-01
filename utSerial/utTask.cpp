#include "utserial.h"

namespace utPetoi {
	namespace utserial {
		// ================================================================
		// utfTask - test fixture for Task class
		// ================================================================
		using utfTask = utfwin32;

		// Task(Command _cmd)
		TEST_F(utfTask, ctor_Command_nothrow) {
			Command cmd{ Command::SHUT_DOWN };
			EXPECT_NO_THROW(Task{ cmd });
		}
		TEST_F(utfTask, ctor_Command_match) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd };
			EXPECT_EQ(cmd, task.cmd);
		}
		TEST_F(utfTask, ctor_Command_arguments_empty) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd };
			EXPECT_TRUE(task.arguments.empty());
		}
		TEST_F(utfTask, ctor_Command_delay_zero) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd };
			EXPECT_EQ(0.f, task.delay);
		}

		//Task(Command _cmd, float _delay)
		TEST_F(utfTask, ctor_Command_delay_nothrow) {
			Command cmd{ Command::SHUT_DOWN };
			EXPECT_NO_THROW(Task(cmd, 8.f));
		}
		TEST_F(utfTask, ctor_Command_delay_Command_match) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd, 8.f };
			EXPECT_EQ(cmd, task.cmd);
		}
		TEST_F(utfTask, ctor_Command_delay_arguments_empty) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd, 8.f };
			EXPECT_TRUE(task.arguments.empty());
		}
		TEST_F(utfTask, ctor_Command_delay_delay_match) {
			Command cmd{ Command::SHUT_DOWN };
			Task task{ cmd, 8.f };
			EXPECT_EQ(8.f, task.delay);
		}

		//Task(Command _cmd, TaskArgs _args, float _delay)
		TEST_F(utfTask, ctor_Full_nothrow) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			EXPECT_NO_THROW(Task(cmd, args, 8.f));
		}
		TEST_F(utfTask, ctor_Full_Command_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task task{ cmd, args, 8.f };
			EXPECT_EQ(cmd, task.cmd);
		}
		TEST_F(utfTask, ctor_Full_arguments_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task task{ cmd, args, 8.f };
			EXPECT_EQ(args, task.arguments);
		}
		TEST_F(utfTask, ctor_Full_delay_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task task{ cmd, args, 8.f };
			EXPECT_EQ(8.f, task.delay);
		}

		// copy ctor
		TEST_F(utfTask, copy_ctor_nothrow) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			EXPECT_NO_THROW(Task{ taskA });
		}
		TEST_F(utfTask, copy_ctor_Command_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			Task taskB{ taskA };
			EXPECT_EQ(cmd, taskB.cmd);
		}
		TEST_F(utfTask, copy_ctor_argument_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			Task taskB{ taskA };
			EXPECT_EQ(args, taskB.arguments);
		}
		TEST_F(utfTask, copy_ctor_delay_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			Task taskB{ taskA };
			EXPECT_EQ(8.f, taskB.delay);
		}

		// assignment
		TEST_F(utfTask, assignment_nothrow) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			Task taskB{ Command::BACK_FLIP, TaskArgs{ 1,2,3,4 }, 7.f };
			EXPECT_NO_THROW(taskB = taskA);
		}
		TEST_F(utfTask, assignment_match) {
			Command cmd{ Command::SHUT_DOWN };
			TaskArgs args{ 1,2,3,4,5,6,7,8 };
			Task taskA{ cmd, args, 8.f };
			Task taskB{ Command::BACK_FLIP, TaskArgs{ 1,2,3,4 }, 7.f };
			taskB = taskA;
			EXPECT_EQ(taskA.cmd, taskB.cmd);
			EXPECT_EQ(taskA.arguments, taskB.arguments);
			EXPECT_EQ(taskA.delay, taskB.delay);
		}
	}	// namespace utserial
}	// namespace utPetoi
