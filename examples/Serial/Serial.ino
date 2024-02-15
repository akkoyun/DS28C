// Include DS28C Library
#include <DS28C.h>

// Declare Object
DS28C DS28C_Object(true, 1);

// Setup Function
void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Start DS28C Object
	DS28C_Object.Begin();

	// Header
	Serial.println(F("DS28C Serial ID Chip."));
	Serial.println(__I2C_Functions_Version__);
	Serial.println(F("---------------------------------------"));

	// Print Serial ID
	Serial.print(F("Serial ID : "));
	Serial.println(String(DS28C_Object.SerialID));
	Serial.println(F("---------------------------------------"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[0], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[1], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[2], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[3], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[4], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[5], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[6], HEX); Serial.print(F("]-"));
	Serial.print(F("[")); Serial.print(DS28C_Object.Serial_ID[7], HEX); Serial.println(F("]"));
	Serial.println(F("---------------------------------------"));

}

void loop() {


}