// Program for control of engines using PID algorithm
// Set Point Alterable by Potentiometer

#define PWM_OUT       3
#define ENCODER_A 2
#define POT_IN A0

// Global Variables

int output;           // defines pwm output
int speed;            // engine speed
int lastError = 0;    // declares the last error

int setpoint;
int error = 0;     // current error
int I_error = 0;   // full gain
int D_error = 0;   // derivative gain
float KP = 0.1;    // proportional constant
float KI = 0.0001; // integrative constant
float KD = 0.001;  // derivative constant


void setup() {
  
  Serial.begin(9600);               // starts serial communication
  
  pinMode(ENCODER_A, INPUT);        // defines the encoder to send data
  pinMode(POT_IN, INPUT);           // defines the potentiometer to send data and control the set point value
  pinMode(PWM_OUT, OUTPUT);         // sets port 3 for sending PWM signal for speed control
  
  output = 10;                      // sets an initial value for pwm_valor 
  analogWrite(PWM_OUT, output);     // controls the pwm value through port 3 output
}

void loop() {
   // calculates the set point value from the analogue reading of the potentiometer
  setpoint = map(analogRead(POT_IN), 0,1023,0,600);  
   
// performs the encoder reading and transforms the pulse value into speed
  speed = 19.1*((60*1000*10) / pulseIn(ENCODER_A, HIGH)); 
  
  error = setpoint - speed; // calculates the error value
   
  I_error += error; // error summary
  D_error = lastError - error; // error variation
  
  // as this loop will be called regularly, we can 
  // assume that dt is constant and not include it in the accounts above.
  // dt is next to KP, KI, KD, implicitly.
  
  // Implementation of the PID Algorithm
  output += KP*error + KI*I_error + KD*D_error;     
  
  // limits control output to pwm valed values (10-255)
  output = constrain(output, 10, 255);
 
  // sends the signal to the "motor"
  analogWrite(PWM_OUT, output);
  
  // prints the speed and setpoint values.
  // RPM values
  // use the graphics function of the serial monitor!  
  Serial.print(speed);     
  Serial.print(",");
  Serial.println(setpoint);  
}
