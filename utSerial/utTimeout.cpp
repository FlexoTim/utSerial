//===================================================================
#include "utserial.h"

#ifdef DISABLED_CODE
#else
#endif	// DISABLED_CODE

namespace serial {
	bool operator==(const Timeout& lhs, const Timeout& rhs)
	{
		return lhs.inter_byte_timeout == rhs.inter_byte_timeout
			&& lhs.read_timeout_constant == rhs.read_timeout_constant
			&& lhs.read_timeout_multiplier == rhs.read_timeout_multiplier
			&& lhs.write_timeout_constant == rhs.write_timeout_constant
			&& lhs.write_timeout_multiplier == rhs.write_timeout_multiplier;
	}
	bool operator!=(const Timeout& lhs, const Timeout& rhs)
	{
		return !(lhs == rhs);
	}

}	// namespace serial

namespace utPetoi {
	namespace utserial {
		// ================================================================
		// utfTimeout - Test fixture for Timeout class
		// ================================================================
		class utfTimeout : public utfwin32
		{
		protected:
			Timeout uttimeout{};
		public:
			utfTimeout() = default;
			~utfTimeout() = default;
		protected:
		};

		TEST_F(utfTimeout, ctor_valid) {
			SUCCEED();
		}
		TEST_F(utfTimeout, copy_ctor_valid) {
			Timeout copyTimeout{ uttimeout };
			EXPECT_EQ(copyTimeout, uttimeout);
		}
		TEST_F(utfTimeout, equality_valid) {
			EXPECT_EQ(Timeout{}, uttimeout);
		}
		TEST_F(utfTimeout, inequality_valid) {
			EXPECT_NE(Timeout{ 1U }, uttimeout);
		}
		TEST_F(utfTimeout, assignment_valid) {
			Timeout timeout1{ 1U };
			ASSERT_NE(timeout1, uttimeout);
			ASSERT_NO_THROW(timeout1 = uttimeout);
			EXPECT_EQ(timeout1, uttimeout);
		}
	}	// namespace utserial
}	// namespace utPetoi
