
fullremotepowerswitch.ino

37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
    Particle.function("mosfet", actuateMOSFETWeb); // declare the MOSFET actuation function as a Particle function so that it can be called via their REST API
    /**
     * This is the curl request that must be sent to actuate a power button.
     * curl https://api.particle.io/v1/devices/56002d001950483553353620/mosfet -d access_token=013b79d222f5e7dd12698c8ad79684755d8468cf -d arg="power_button"
     */

    Particle.variable("power_state", actual_state_power); // declare the computer power state variable as a Particle variable so that it can be called via their REST API
    /**
     * This is the curl request that must be sent to read in the power state.
     * curl https://api.particle.io/v1/devices/56002d001950483553353620/power_state?access_token=013b79d222f5e7dd12698c8ad79684755d8468cf
     */
}
/**
 * Infinitely loop over this section to wait for a button press.
 */
void loop()
{
    prev_button_state = button_state;
    button_state = digitalRead(button); // read the input pin

    if(!button_state) {
        actuateMOSFET(); // if the button was pressed, actuate the MOSFET
    }

    prev_state_power = read_state_power;
    read_state_power = digitalRead(led_power);

    actual_state_power = prev_state_power && read_state_power;
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
Ready. Last Event: device/app-hash = 0F672C4AA5BDE3ABBBF967318B1627...  remote_desktop_power_switch  v0.5.4 
