// We are using two solid state relays to control the AC motor with an Arduino Uno
// Attach 200k resistor between both terminals on the motor's capacitor
// Allow the motor to have a 10 seconds of operation time each time
// the code is based on an AC motor with 25% duty cycle
// The relay pins connect to arduino's digital PWM Pin 10 and 11, ground to ground
// SSR circuit developed with Eric Rosenthal 
//yesyesno LLC Jan, 17, 2013     mailto: molmol@openmolmol.com


int PinDown = 11; // choose the pin for the relay 
int PinUp = 10; // choose the pin for the relay  


int nSecondsMoving = 10;  // unit in seconds; DO NOT go less than 10 seconds 
int nSecondsMovingUp = nSecondsMoving*1.2;  // the motor goes up 1.2 times longer than it goes down

int nSecondsPausedMin = nSecondsMoving * 4;    
// this is nSecondsMoving * 4 -- we need to wait 2 minutes if we've moved for 30 seconds

int nSecondsPausedMax = nSecondsMoving * 4 + 10;   
// this is nSecondMovind * 4 + something to add for randomness, ie 10 seconds.. 

boolean firstTime;

void setup() {
    Serial.begin(9600);
    pinMode(PinUp, OUTPUT);  // declare relayPin as output  
    // motor will go down first 
    pinMode(PinDown, OUTPUT);  // declare relayPin as output

    firstTime = true;

}

void loop(){
  
    digitalWrite(PinUp, LOW);  // turn relay OFF
    digitalWrite(PinDown, LOW);  // turn relay OFF
    
    if (firstTime == true){
      delay(1 * 1000);  // 1 second of delay on first start
    } else {
      delay(random(nSecondsPausedMin, nSecondsPausedMax) * 1000);  // random delay between each operation
    }
    
    digitalWrite(PinUp, HIGH);  // turn relay ON 

    delay(nSecondsMovingUp*1000);
    
    digitalWrite(PinUp, LOW);  // turn relay OFF

    delay(random(nSecondsPausedMin, nSecondsPausedMax) * 1000);
    
    digitalWrite(PinDown, HIGH);  // turn relay ON

    delay(nSecondsMoving * 1000);
    
    digitalWrite(PinDown, LOW); // turn relay OFF
    
    firstTime = false;
    //end down
}
