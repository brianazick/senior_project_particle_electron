int button = D0; //button is on pin D0
int led = D7; // blue LED on board is attached to D7
int val = 0; //temp var for button val


void setup() {
    pinMode(button, INPUT_PULLDOWN);
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH);
}


void loop(){
    val = digitalRead(button); // read the input pin
    digitalWrite(led, !val); //set the LED to its value
}
