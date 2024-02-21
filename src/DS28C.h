/* *******************************************************************************
 *  Copyright (C) 2014-2023 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: DS28C
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *
 *********************************************************************************/

#ifndef __DS28C__
#define __DS28C__

	// Define Arduino Library
	#ifndef Arduino_h
		#include <Arduino.h>
	#endif

	// Include I2C Functions Library
	#ifndef __I2C_Functions__
		#include <I2C_Functions.h>
	#endif

	// DS28C Library Class
	class DS28C : private I2C_Functions {

		// Public Context
		public:

			// Declare Public Variables
			char SerialID[17];

			// Construct a new DS28C object
			explicit DS28C(const bool _Multiplexer_Enable = false, const uint8_t _Multiplexer_Channel = 0) : I2C_Functions(__I2C_Addr_DS28C__, _Multiplexer_Enable, _Multiplexer_Channel) {

				// Clear Serial ID Hex Array
				memset(this->SerialID, '\0', sizeof(this->SerialID));

			}

			// Begin Function
			bool Begin(void) {

				// Start I2C
				I2C_Functions::Begin();

				// Control for Device
				if (I2C_Functions::Detect()) {

					// Declare Serial ID Array
					uint8_t Serial_ID[8];

					// Set DS28C to I2C Mode
					I2C_Functions::Write_Register(0x08, 0x01, false);

					// Send CRC  Read Request to DS28C and read
					Serial_ID[0] = I2C_Functions::Read_Register(0x07);

					// Send 40-47 bit Read Request to DS28C and read
					Serial_ID[1] = I2C_Functions::Read_Register(0x06);

					// Send 32-39 bit Read Request to DS28C and read
					Serial_ID[2] = I2C_Functions::Read_Register(0x05);

					// Send 24-31 bit Read Request to DS28C and read
					Serial_ID[3] = I2C_Functions::Read_Register(0x04);

					// Send 16-23 bit Read Request to DS28C and read
					Serial_ID[4] = I2C_Functions::Read_Register(0x03);

					// Send 08-15 bit Read Request to DS28C and read
					Serial_ID[5] = I2C_Functions::Read_Register(0x02);

					// Send 00-07 bit Read Request to DS28C and read
					Serial_ID[6] = I2C_Functions::Read_Register(0x01);

					// Send Device Family bit Read Request to DS28C and read
					Serial_ID[7] = I2C_Functions::Read_Register(0x00);

					// Convert the 64-bit serial number to a hex string
					for (int i = 0; i < 8; i++) sprintf(&this->SerialID[i * 2], "%02X", Serial_ID[i]);
					
					// End Function
					return(true);

				} else {

					// Set Serial ID to Zero
					memset(this->SerialID, '0', sizeof(this->SerialID));

					// End Function
					return(false);

				}

			}

	};

#endif /* defined(DS28C) */
