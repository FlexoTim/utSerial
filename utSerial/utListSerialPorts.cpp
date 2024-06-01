#include "utserial.h"

namespace utPetoi {
	namespace utserial {

		ostream& operator <<(ostream& os, const PortInfo& rport)
		{
			cout << left << setw(16) << "port:"
				<< right << rport.port << "\n"
				<< left << setw(16) << "description:"
				<< right << rport.description << "\n"
				<< left << setw(16) << "hardware_id:"
				<< right << rport.hardware_id << "\n"
				;
			return os;
		}

		using utfListSerialPorts = utfwin32;

		TEST_F(utfListSerialPorts, echo_list) {
			vector <PortInfo> ports{ list_ports() };
			cout << ports;
		}
	}	// namespace utserial
}	// namespace utPetoi
