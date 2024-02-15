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

		// Private Context
		private:

			// DS28C Sensor Variable Structure.
			struct DS28C_Struct {

				// Multiplexer Structure.
				struct Multiplexer_Struct{

					// Multiplexer Enable Variable (if set true library make multiplexer).
					bool Enable 			= false;

					// Multiplexer Channel Variable (if not defined 0 channel make).
					uint8_t Channel 		= 0;

				} Multiplexer;

			} Sensor;

			// Serial ID Char Array Generator
			void getSerialIDHex(void) {

				// Convert the 64-bit serial number to a hex string
				for (int i = 0; i < 8; i++) {

					// Convert each byte to a 2-digit hexadecimal string
					sprintf(&this->SerialID[i * 2], "%02X", this->Serial_ID[i]);

				}

				// Null-terminate the string
				this->SerialID[16] = '\0';
			}

		// Public Context
		public:

			// Declare Public Variables
			uint8_t Serial_ID[8];
			char SerialID[17];

			// Construct a new DS28C object
			explicit DS28C(const bool _Multiplexer_Enable = false, const uint8_t _Multiplexer_Channel = 0) : I2C_Functions(__I2C_Addr_DS28C__, _Multiplexer_Enable, _Multiplexer_Channel) {

				// Set Multiplexer Variables
				this->Sensor.Multiplexer.Enable = _Multiplexer_Enable;
				this->Sensor.Multiplexer.Channel = _Multiplexer_Channel;

				// Clear Serial ID Array
				for (int i = 0; i < 8; i++) this->Serial_ID[i] = 0x00;

				// Clear Serial ID Hex Array
				memset(this->SerialID, '\0', sizeof(this->SerialID));

			}

			// Begin Function
			bool Begin(void) {

				// Start I2C
				I2C_Functions::Begin();

				// Control for Device
				if (I2C_Functions::Variables.Device.Detect) {

					// Set DS28C to I2C Mode
					I2C_Functions::Write_Register(0x08, 0x01, false);

					// Send CRC  Read Request to DS28C and read
					this->Serial_ID[0] = I2C_Functions::Read_Register(0x07);

					// Send 40-47 bit Read Request to DS28C and read
					this->Serial_ID[1] = I2C_Functions::Read_Register(0x06);

					// Send 32-39 bit Read Request to DS28C and read
					this->Serial_ID[2] = I2C_Functions::Read_Register(0x05);

					// Send 24-31 bit Read Request to DS28C and read
					this->Serial_ID[3] = I2C_Functions::Read_Register(0x04);

					// Send 16-23 bit Read Request to DS28C and read
					this->Serial_ID[4] = I2C_Functions::Read_Register(0x03);

					// Send 08-15 bit Read Request to DS28C and read
					this->Serial_ID[5] = I2C_Functions::Read_Register(0x02);

					// Send 00-07 bit Read Request to DS28C and read
					this->Serial_ID[6] = I2C_Functions::Read_Register(0x01);

					// Send Device Family bit Read Request to DS28C and read
					this->Serial_ID[7] = I2C_Functions::Read_Register(0x00);

					// Combine Serial ID
					this->getSerialIDHex();
					
					// End Function
					return(true);

				} else {

					// Send CRC  Read Request to DS28C and read
					this->Serial_ID[0] = 0x00;

					// Send 40-47 bit Read Request to DS28C and read
					this->Serial_ID[1] = 0x00;

					// Send 32-39 bit Read Request to DS28C and read
					this->Serial_ID[2] = 0x00;;

					// Send 24-31 bit Read Request to DS28C and read
					this->Serial_ID[3] = 0x00;;

					// Send 16-23 bit Read Request to DS28C and read
					this->Serial_ID[4] = 0x00;;

					// Send 08-15 bit Read Request to DS28C and read
					this->Serial_ID[5] = 0x00;;

					// Send 00-07 bit Read Request to DS28C and read
					this->Serial_ID[6] = 0x00;;

					// Send Device Family bit Read Request to DS28C and read
					this->Serial_ID[7] = 0x00;;

					// Combine Serial ID
					this->getSerialIDHex();

					// End Function
					return(false);

				}

			}

	};

#endif /* defined(DS28C) */
