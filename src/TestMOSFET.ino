int button = D0; //button is on pin D0
int led = D7; // blue LED on board is attached to D7
int led_state; //LED state
int mosfet = DAC1; //analog output pin for mosfet Vgs
int button_state; //temp var for button state
int prev_button_state; //temp var for previous button state


void setup() {
    pinMode(button, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    pinMode(mosfet, OUTPUT);
    analogWrite(mosfet, 4095);
    digitalWrite(led, HIGH);
    led_state = 1;
    button_state = digitalRead(button);
}


void loop(){
    prev_button_state = button_state;
    button_state = digitalRead(button); // read the input pin

    if(!button_state) {
        led_state = !led_state;
        digitalWrite(led, led_state); //set the LED to its value

        analogWrite(mosfet, 2482); //set the mosfet gate voltage to 2.0 V

        delay(500);
        led_state = !led_state;
        digitalWrite(led, led_state); //set the LED to its value

        analogWrite(mosfet, 0); //set the mosfet gate voltage to 0 V
    }
    delay(150);
}
