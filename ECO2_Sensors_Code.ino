
//code for mq135 sensor, ultrasonic sensor and two lcds
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define MQ135_PIN A0 //initilaising the pin number for the co2 sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // first address for the LCD
LiquidCrystal_I2C lcd2(0x26, 16, 2);  // the address for the second LCD (We got this through soldering)

int ppm_readings = 0; // converts the sensorValue (CO2 value) into ppm form
int sum_readings = 0; // sum of all the ppm readings
int number_samples = 10;  // for sake of average, we only take 10 readings
int avgco2 = 0; // final answer for average CO2
int dist_readings = 0; //the readings for distance measurements taken by the ultrasonic sensor
int dist_samples = 10; // To find the average of distance readings we take 10
int sum_distance = 0; // the sum of dist_readings
int avgdist = 0; //findal answer for avergae distance
int final_reading = 0; //final reading this is the average co2*the average distance travelled

int echo = 4; //pin for the echo of ultrasonic sensor
int trigger = 5; //pin for the trigger for ultrasonid sensor

void setup() {
    Serial.begin(9600); // Start serial communication
    pinMode(echo, INPUT);
    pinMode(trigger, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    lcd2.init();
    lcd2.backlight();
}

void loop() {
    int sensorValue = analogRead(MQ135_PIN); // Read sensor value
    Serial.print("MQ-135 Value: ");
    Serial.println(sensorValue); // Print value
    delay(1000); // Wait 1 second
    
    lcd.clear(); // the code for displaying the co2 reading onto the first lcd
    lcd.setCursor(2, 0); //the first line
    lcd.print("CO2: ");
    lcd.setCursor(8, 0);
    lcd.print(sensorValue);
    lcd.setCursor(12, 0);
    lcd.print("ppm");

    digitalWrite(trigger, 0); 
    delayMicroseconds(2);
    digitalWrite(trigger, 1);
    delayMicroseconds(10);
    
    float distance = pulseIn(echo, HIGH);  // Capture pulse width
    distance = (distance / 58);  // Convert to centimeters
    Serial.println(distance); // prints the value of distance from ultrasonic sesnro onto serial monitor (for debugging)
    delay(50);
    
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.setCursor(9, 1);
    lcd.print(distance);
    lcd.setCursor(14, 1);
    lcd.print("km");  // written as km for real-case scenario

    // Averaging distance readings
    
    Serial.print("Average CO2 Level: ");
    Serial.println(avgco2);

    // Calculate final reading (CO2 * distance)
    final_reading = avgco2 * avgdist;

    //the second lcd which shows the final reading of the calculation between the co2 and distance readings
    lcd2.clear();
    lcd2.setCursor(0, 0);
    lcd2.print("Final Reading: ");
    lcd2.setCursor(5, 1);
    lcd2.print(final_reading);
    lcd2.setCursor(10, 1);
    lcd2.print("ppm");
    
    delay(100);  // Short pause before next loop
}






