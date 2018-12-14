//Samantha Moon
//BME 590: Design for Disabilities
//Created: 04 NOV
//UPDATED: 29 NOV
//Skeleton From: Dr. Palmeri


// -------------------- **DEFINE STUFF** -------------------- //

// use preprocessor directives to define constants in the code
// These never change (unless we want them to)
#define FLASH_RATE_HZ 2 // how you want light to flash
#define BUTTON_IN 2 // where button plugs in
#define PWM_LED_OUT 11 // where LED plugs in
#define PWM_MAX 255  // max brightness value

// -------------------- **SET GLOBAL VARS** -------------------- //

// global variables representing "state" **across all functions**
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash

int operating_mode = 0; // makes it off
bool BUTTON_PUSHED = false; // starting state of button
int previous_button_state = 0;  // did we even use this?
int PWM_OUT = 0; //tracks the states

// -------------------- **SETUP** -------------------- //

// executed one-time at device startup
  void setup() {
  Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, RISING);
   // "When this pin goes from low to high call BUTTON_PUSHED"
   
  pinMode(BUTTON_IN, INPUT_PULLUP);
  pinMode(PWM_LED_OUT, OUTPUT);
}

// -------------------- **DA LOOP** -------------------- //

void loop(){

//checks things

//    Serial.println("mode = ");
//    Serial.println(operating_mode);
//
//    int sensorValue = digitalRead(BUTTON_IN);
//    Serial.println("val = ");
//    Serial.println(sensorValue);
//    
//    Serial.println("PWM_OUT = ");
//    Serial.println(PWM_OUT);

    check_button_press();

    set_pwm_based_on_operating_mode();

    shine_led();

}

// -------------------- **FUNCTIONS** -------------------- //

//******************************************************
void button_pushed() {
    BUTTON_PUSHED = true;
}
void check_button_press() {
    // set operating_mode
    // reset previous button press state, interrupt catch, etc.

  if (BUTTON_PUSHED == true) {
    operating_mode = operating_mode + 1;
    if (operating_mode==5) {
      operating_mode = 0;
    }
  }

  BUTTON_PUSHED = false;   
  delay(500);
}

//******************************************************
void set_pwm_based_on_operating_mode() {
  // bank of states
  
    switch (operating_mode) { 
        case 0:
            PWM_OUT = 0;
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            break;
        case 2:
            PWM_OUT = PWM_MAX/5;
            break;
        case 3:
            PWM_OUT = PWM_MAX/10;
            break;
        case 4:
            flash_the_light();
    }
}

//******************************************************
void flash_the_light() {

  analogWrite(PWM_LED_OUT, PWM_MAX);   // turn the LED on (HIGH is the voltage level)
  delay(1000/FLASH_RATE_HZ);                         // wait for a second
  analogWrite(PWM_LED_OUT, 0);        // turn the LED off by making the voltage 0 (if this doesn't work try "LOW")
  delay(1000/FLASH_RATE_HZ);                       // wait for a second
}

//******************************************************
void shine_led() {
    analogWrite(PWM_LED_OUT, PWM_OUT); //PWM_LED_OUT = pin out, PWM_OUT variable set by operating mode
}


