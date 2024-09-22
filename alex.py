import speech_recognition as sr
import pyttsx3
import serial
import re  # Import regular expressions library

# Initialize the speech recognizer, text-to-speech engine, and Arduino serial communication
listener = sr.Recognizer()
engine = pyttsx3.init()

# Set the voice for the text-to-speech engine
voices = engine.getProperty("voices")
if len(voices) > 1:
    engine.setProperty('voice', voices[1].id)  # Ensure there is a second voice available

# Setup Arduino communication (adjust port and baudrate)
arduino = None  # Initialize the variable

try:
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Update to your port
    print("Connection to Arduino successful!")  # Confirmation message
    engine.say("Connection to Arduino successful!")  # Audio feedback
    engine.runAndWait()
except serial.SerialException as e:
    print(f"Error connecting to Arduino: {e}")
    engine.say(f"Error connecting to Arduino: {e}")
    engine.runAndWait()

# Greet the user
engine.say("I am Shingi. How can I help you?")
engine.runAndWait()


# Function to extract percentage value and execute the corresponding command
def extract_percentage(command):
    match = re.search(r'(\d+)%', command)
    if match:
        percentage = int(match.group(1))
        return percentage
    else:
        print("No percentage value found in the command")
        return None

# Function to handle commands
def execute_command(command):
    global arduino  # Declare arduino as global

    if "on" in command and "lights" in command:
        message = "Turning on lights"
    
        arduino.write(b"00\n")  # Sending '00' to Arduino for turning on the lights)

    elif "off" in command and "lights" in command:
        message = "Turning off lights"

        arduino.write(b"01\n")  # Sending '01' to Arduino for turning off the lights)

    elif "on" in command and "fan" in command:
        message = "Turning on fan"

        arduino.write(b"02\n")  # Sending '02' to Arduino to turn on the fan)

    elif "off" in command and "fan" in command:
        message = "Turning off fan"

        arduino.write(b"03\n")  # Sending '03' to Arduino to turn off the fan)

    elif "set lights" in command or "set light" in command:
        percent = extract_percentage(command)
        if percent is not None:
            message = f"Setting lights to {percent}%"

            arduino.write(f"04{percent}\n".encode())  # Send percentage to Arduino)

    elif "set fans" in command or "set fan" in command:
        percent = extract_percentage(command)
        if percent is not None:
            message = f"Setting fans to {percent}%"
            arduino.write(f"05{percent}\n".encode())  # Send percentage to Arduino)
    
    elif "power saving" in command and "on" in command:
        message = "Power Saving mode on"
        arduino.write(b"06\n")
        

    elif "everything" in command and "off" in command:
        message = "Turing eveything off"
        arduino.write(b"07\n")
        
    elif "rest" in command and "on" in command:
        message = "Rest mode on"
        arduino.write(b"08\n")

    elif "bye-bye" in command or "bye" in command:
        message = "Exit"
        # Here, you can stop the recognition loop by raising a KeyboardInterrupt
        raise KeyboardInterrupt
    else:
        message = "Command not recognized"  # Ensure unrecognized command is spoken
    if(message):
        print(message)
# Main loop to listen for voice commands
try:
    with sr.Microphone() as source:
        while True:
            try:
                print("Start Speaking!!")
                listener.adjust_for_ambient_noise(source)
                
                voice = listener.listen(source, timeout=3, phrase_time_limit=5)
                command = listener.recognize_google(voice).lower()
                
                print("You said:", command)
                execute_command(command)

            except sr.WaitTimeoutError:
                print("No speech detected, waiting for the next line...")
                continue  # Restart the listening process

            except sr.UnknownValueError:
                print("Sorry, I did not understand the audio, restarting listening process.")
                continue  # Restart the listening process

            except sr.RequestError as e:
                print(f"Could not request results from Google Speech Recognition service; {e}")
                continue  # Restart the listening process

            except Exception as e:
                print(f"An unexpected error occurred: {e}")
                continue  # Restart the listening process

except KeyboardInterrupt:
    print("\nRecognition stopped.")
    engine.say("Recognition stopped.")
    engine.runAndWait()
