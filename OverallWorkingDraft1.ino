#define LIGHT_PIN 6  // Pin for controlling lights
#define FAN_PIN 9    // Pin for controlling fans
int pirsensorPin = 2; // Pin for the PIR sensor
int ldrsensorPin = A0;
bool adjustingLight = false; // Flag to indicate if we are adjusting light based on sensor
bool restModeActive = false; // Flag to indicate if rest mode is active

void setup() {
    Serial.begin(9600);  // Start serial communication
    pinMode(LIGHT_PIN, OUTPUT);  // Set light pin as output
    pinMode(FAN_PIN, OUTPUT);     // Set fan pin as output
    pinMode(ldrsensorPin, INPUT);    // Set sensor pin as input
    pinMode(pirsensorPin, INPUT);
    // Start with lights and fan off
    digitalWrite(LIGHT_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
}

void loop() {
    // Check for serial input
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');  // Read command until newline
        command.trim();  // Remove any whitespace

        if (command == "00") {  // Command to turn on lights
            Serial.println("Turning on lights");
            analogWrite(LIGHT_PIN, 255);
            restModeActive = false; // Set the flag to 
            adjustingLight = false; 
        }
        else if (command == "01") {  // Command to turn off lights
            Serial.println("Turning off lights");
            analogWrite(LIGHT_PIN, 0);
            restModeActive = false; // Set the flag to true
            adjustingLight = false; 
        }
        else if (command == "02") {  // Command to turn on fan
            Serial.println("Turning on fan");
            digitalWrite(FAN_PIN, HIGH);
            restModeActive = false; // Set the flag to true
            adjustingLight = false; 
        }
        else if (command == "03") {  // Command to turn off fan
            Serial.println("Turning off fan");
            digitalWrite(FAN_PIN, LOW);
            restModeActive = false; // Set the flag to true
            adjustingLight = false; 
        }
        else if (command.startsWith("04")) {  // Handling light percentage
            int percent = command.substring(2).toInt();
            if (percent >= 0 && percent <= 100) {
                Serial.print("Setting lights to ");
                Serial.print(percent);
                Serial.println("%");
                analogWrite(LIGHT_PIN, map(percent, 0, 100, 0, 255));  // Set light brightness
                restModeActive = false; // Set the flag to true
                adjustingLight = false; 
            }
        }
        else if (command.startsWith("05")) {  // Handling fan percentage
            int percent = command.substring(2).toInt();
            if (percent >= 0 && percent <= 100) {
                Serial.print("Setting fans to ");
                Serial.print(percent);
                Serial.println("%");
                analogWrite(FAN_PIN, map(percent, 0, 100, 64, 255));  // Set fan speed
                restModeActive = false; // Set the flag to true
                adjustingLight = false; 
            }
        }
        else if (command == "06") {  // Start adjusting light based on sensor readings
            Serial.println("Adjusting light based on sensor readings");
            adjustingLight = true; // Set the flag to true
            restModeActive = false;
        }
        else if (command == "07") {  // Turn off both lights and fans
            Serial.println("Turning off lights and fan");
            digitalWrite(FAN_PIN, LOW);
            digitalWrite(LIGHT_PIN, LOW);
            adjustingLight = false; // Also stop adjusting light if turned off
            restModeActive = false;
        }
        else if (command == "08") {  // Rest Mode
            Serial.println("Rest Mode activated");
            restModeActive = true; // Set the flag to true
            adjustingLight = false; // Ensure adjusting light is off
        }
    }

    // Continuously read the sensor if adjustingLight is true
    if (adjustingLight) {
        int sensorValue = analogRead(ldrsensorPin); // Read the value from the sensor
        Serial.println(sensorValue);
        analogWrite(LIGHT_PIN, map(sensorValue, 350, 1000, 255, 0)); // Adjust light based on sensor value

        // Small delay for stability
        delay(100);
        
        // Check if a new command has come in that might change the adjusting state
        // if (Serial.available() > 0) {
        //     String command = Serial.readStringUntil('\n');  // Read command until newline
        //     command.trim();  // Remove any whitespace

        //     // Stop adjusting if a new command is received
        //     if (command != "06") {
        //         adjustingLight = false; // Set the flag to false to stop adjusting
        //     }
        // }
    }

    // If Rest Mode is active, read the PIR sensor continuously
    if (restModeActive) {
        int pirValue = digitalRead(pirsensorPin); // Read the value from the PIR sensor
        if (pirValue == HIGH) {
            Serial.println("Motion detected: Turning on lights");
            digitalWrite(LIGHT_PIN, HIGH); // Turn on the lights
        } else {
            Serial.println("No motion: Turning off lights");
            digitalWrite(LIGHT_PIN, LOW); // Turn off the lights
        }

        // Check for new commands
        // if (Serial.available() > 0) {
        //     String command = Serial.readStringUntil('\n');  // Read command until newline
        //     command.trim();  // Remove any whitespace
            
        //     // Exit rest mode if a new command is received
        //     if (command != "08") {
        //         restModeActive = false; // Set the flag to false to stop rest mode
        //         // digitalWrite(LIGHT_PIN, LOW); // Turn off lights if exiting rest mode
        //     }
        // }

        // Small delay for stability
        // delay(100);
    }
}
