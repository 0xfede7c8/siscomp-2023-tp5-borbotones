/*    
   * Ultrasonic Sensor HC-SR05/4 and Arduino
    * by Hanie Kiani
*  https://electropeak.com/learn
    */
    long duration;
    int distance;
    
    const int trig = 9;
    const int echo = 10;

    const int bit0 = 30;
    const int bit1 = 31;
    const int bit2 = 32;
    const int bit3 = 33;
    const int bit4 = 34;
    const int bit5 = 35;
    const int bit6 = 36;
    const int bit7 = 37;
   
    
void setup() 
{
    pinMode(trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(echo, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication

    pinMode(bit0, OUTPUT);
    pinMode(bit1, OUTPUT);
    pinMode(bit2, OUTPUT);
    pinMode(bit3, OUTPUT);
    pinMode(bit4, OUTPUT);
    pinMode(bit5, OUTPUT);
    pinMode(bit6, OUTPUT);
    pinMode(bit7, OUTPUT);
}

void loop()
{
    distance = calculateDistance();
    Serial.println(distance);
    output_gpio(distance);
    delay(500);
}

void output_gpio(int distance) 
{
  byte bits = (byte)distance;
  // Output each bit to bits
  digitalWrite(bit0, (distance & B00000001) ? HIGH : LOW);
  digitalWrite(bit1, (distance & B00000010) ? HIGH : LOW);
  digitalWrite(bit2, (distance & B00000100) ? HIGH : LOW);
  digitalWrite(bit3, (distance & B00001000) ? HIGH : LOW);
  digitalWrite(bit4, (distance & B00010000) ? HIGH : LOW);
  digitalWrite(bit5, (distance & B00100000) ? HIGH : LOW);
  digitalWrite(bit6, (distance & B01000000) ? HIGH : LOW);
  digitalWrite(bit7, (distance & B10000000) ? HIGH : LOW);
}

int calculateDistance(){ 
    digitalWrite(trig, LOW); 
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
    distance= duration*0.034/2;
    return distance;
}