#include <Arduino.h>

void setup();

void loop();

int main()
{
	init();

	setup();

	for(;;)
	{
		loop();
	}

    return 0;
}


void setup()
{
	Serial.begin(9600);
	Serial.write("setup ");

	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	Serial.write("Setting LED to HIGH ");
	digitalWrite(LED_BUILTIN, HIGH);
	delay(2000);
	Serial.write("Setting LED to LOW ");
	digitalWrite(LED_BUILTIN, LOW);
	delay(2000);
}
