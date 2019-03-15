/*
 * File: fullremotepowerswitch.ino
 * Author: Brian Zick
 * Date: 2019-02-22
 * Purpose: To receive input from an Android application and actuate a MOSFET to then turn on a computer.
 * Modified:
 */

int led = D7; // blue LED on board is attached to D7
bool led_state; // LED state

int mosfet = DAC1; //analog output pin for mosfet Vgs

int button = D0; //the secondary button is on pin D0
bool button_state; // temp var for button state

int led_power = B1; // the power LED header on the motherboard
bool read_state_power; // the current power state of the computer

/**
 * Initialize variables and pins.
 */
void setup()
{
    pinMode(button, INPUT_PULLUP); // the secondary button is an input with a pull up resistor for a default off state
    pinMode(led, OUTPUT); // the LED is an output
    pinMode(mosfet, OUTPUT); // the MOSFET is an output
    analogWrite(mosfet, 0); // write 0V to the MOSFET
    digitalWrite(led, HIGH); // turn the LED on by default
    led_state = 1; // set the LED power state variable to on
    button_state = digitalRead(button); // read in the button state


    Particle.function("mosfet", actuateMOSFETWeb); // declare the MOSFET actuation function as a Particle function so that it can be called via their REST API
    /**
     * This is the curl request that must be sent to actuate a power button.
     * curl https://api.particle.io/v1/devices/56002d001950483553353620/mosfet -d access_token=REDACTED -d arg="power_button"
     */

    Particle.variable("power_state", read_state_power); // declare the computer power state variable as a Particle variable so that it can be called via their REST API
    /**
     * This is the curl request that must be sent to read in the power state.
     * curl https://api.particle.io/v1/devices/56002d001950483553353620/power_state?access_token=REDACTED
     */
}

/**
 * Infinitely loop over this section to wait for a button press.
 */
void loop()
{
    button_state = digitalRead(button); // read the input pin

    if(!button_state) {
        actuateMOSFET(); // if the button was pressed, actuate the MOSFET
    }

    read_state_power = digitalRead(led_power);
}

/**
 * A helper function to encapsulate the action of actuating the MOSFET, and switching a helper LED for testing purposes.
 * This modularity allows it to be called both when the button is pressed and the API is called.
 */
void actuateMOSFET(){
    led_state = !led_state;
    digitalWrite(led, led_state); //set the LED to its value

    analogWrite(mosfet, 2482); //set the mosfet gate voltage to 2.0 V

    delay(500);
    led_state = !led_state;
    digitalWrite(led, led_state); //set the LED to its value

    analogWrite(mosfet, 0); //set the mosfet gate voltage to 0 V
}

/** Particle.functions always take a string as an argument and return an integer.
  * The string passed indicates the command sent by the API request.
  * If the command is correct, in this case "power_button", the desired action is carried out and a 1 is returned.
  * If an incorrect command is passed, -1 is returned.
  */
int actuateMOSFETWeb(String command){
    if (command == "power_button") {
        actuateMOSFET();
        return 1;
    } else {
        return -1;
    }
}
