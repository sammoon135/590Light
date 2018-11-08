//Samantha Moon
//BME 590: Design for Disabilities
//Created: 04 NOV
//UPDATED: 04 NOV
//Skeleton From: Dr. Palmeri


// **DEFINE STUFF** //

// use preprocessor directives to define constants in the code
// These never change (unless we want them to)
#define FLASH_RATE_HZ 2 // how you want light to flash
#define BUTTON_IN D1 // where button plugs in
#define PWM_LED_OUT D11 // where LED plugs in
#define PWM_MAX 255  // max brightness value

// **SET GLOBAL VARS** //

// global variables representing "state" **across all functions**
// Globals initiated to values
// These change in the code (which is why they're globals)
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0; // makes it off
bool BUTTON_PUSHED = false; // starting state of button
int previous_button_state = 0;  // did we even use this?
int PWM_OUT = 0; //tracks the states

// **SETUP** //

// executed one-time at device startup
void setup() {

   attachInterrupt(BUTTON_IN, button_pushed, FALLING);
   // Detects event (button push w/o using delays (???))
   // "When this pin goes from high to low call BUTTON_PUSHED"
   // FALLING - pin goes from high to low (b/c detects release of button)
   // define output (PWM) pin connected to LED
   // try this: pinMode(interruptPin, INPUT_PULLUP);
   //attachInterrupt(digitalPinToInterrupt(interruptPin), button_pushed, FALLING);

}

// **DA LOOP** //

// continually-running loop
// calls functions that are named as "actions"
void loop(){

    check_for_button_press();

    set_pwm_based_on_operating_mode();

if (operating_mode < 4) {
    shine_led();
}
    if (operating_mode == 4) {
    flash_the_light();
}

}

// **FUNCTIONS** //

void set_pwm_based_on_operating_mode() {
  // bank of states
    switch (operating_mode) { 
        case 0:
            PWM_OUT = 0;
        case 1:
            PWM_OUT = PWM_MAX;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
        case 3:
            PWM_OUT = int(PWM_MAX/4);
        case 4:
            PWM_OUT = flash_the_light();
    }
}

void button_pushed() {
    BUTTON_PUSHED = true;
}

void flash_the_light() {
// you would call FLASH_RATE_HZ here!

  analogWrite(PWM_LED_OUT, PWM_MAX);   // turn the LED on (HIGH is the voltage level)
  delay(1000/FLASH_RATE_HZ);                         // wait for a second
  analogWrite(PWM_LED_OUT, 0);        // turn the LED off by making the voltage 0 (if this doesn't work try "LOW")
  delay(1000/FLASH_RATE_HZ);                       // wait for a second
}

void shine_led() {
    analogWrite(PWM_LED_OUT, PWM_0UT); //PWM_LED_OUT = pin out, PWM_OUT variable set by operating mode
}

void check_button_press() {
    // set operating_mode
    // reset previous button press state, interrupt catch, etc.

// this is not awesome but it's something - try not to hard code
// vector of operating states @top? Loop through?
// middle ground: "max cases" and make something function of max 
if (BUTTON_PUSHED == true) {
    operating_mode = operating_mode + 1;
    if (operating_mode==5) {
      operating_mode = 0;
}
}
BUTTON_PUSHED = false;   
}
