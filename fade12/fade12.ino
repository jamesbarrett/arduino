/*
 * 
 * take care -  heatsink the transistor and the LED
 * Important that maxBright does not overdrive the led circuit 
 * ramp up the value - measure the voltage across the LED (max 3.5 - 3.7v)
 * also check the current and work out the power
 * make sure each burst doesn't heat anything up too much
 * put a capacitor across the power rails 
 * to smooth the output and the meter readimg
 * - with 12 1w LEDs I am using 470uF electrolytic
 */

int ledPin = 6; 
int maxBright = 255;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  for(int i = 0; i<maxBright; i++){
    analogWrite(ledPin, i);
    Serial.println(i);
    delay(2);
  }
  delay(1000);
  analogWrite(ledPin, 0);
  
  delay(600000);
}
