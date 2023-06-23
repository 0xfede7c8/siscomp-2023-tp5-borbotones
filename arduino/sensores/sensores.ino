    const int trig = 9;
    const int echo = 10;

    const int dist_bit0 = 30;
    const int dist_bit1 = 31;
    const int dist_bit2 = 32;
    const int dist_bit3 = 33;
    const int dist_bit4 = 34;
    const int dist_bit5 = 35;
    const int dist_bit6 = 36;
    const int dist_bit7 = 37;

    const int pote_bit0 = 38;
    const int pote_bit1 = 39;
    const int pote_bit2 = 40;
    const int pote_bit3 = 41;
    const int pote_bit4 = 42;
    const int pote_bit5 = 43;
    const int pote_bit6 = 44;
    const int pote_bit7 = 45;

    const int analogIn = A0;

    char buf[100];
   
    
void setup() 
{
    pinMode(trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(echo, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication

    pinMode(dist_bit0, OUTPUT);
    pinMode(dist_bit1, OUTPUT);
    pinMode(dist_bit2, OUTPUT);
    pinMode(dist_bit3, OUTPUT);
    pinMode(dist_bit4, OUTPUT);
    pinMode(dist_bit5, OUTPUT);
    pinMode(dist_bit6, OUTPUT);
    pinMode(dist_bit7, OUTPUT);

    pinMode(pote_bit0, OUTPUT);
    pinMode(pote_bit1, OUTPUT);
    pinMode(pote_bit2, OUTPUT);
    pinMode(pote_bit3, OUTPUT);
    pinMode(pote_bit4, OUTPUT);
    pinMode(pote_bit5, OUTPUT);
    pinMode(pote_bit6, OUTPUT);
    pinMode(pote_bit7, OUTPUT);
}

void loop()
{
    int distance = calculateDistance();
    int pote = get_pote();
    sprintf(buf, "Distancia %i - Pote: %i\n", distance, pote);

    Serial.print(buf);
    output_gpio(distance, pote);
    // output_gpio2(pote);
    delay(500);
}

int get_pote() 
{
  // Para limitar el rango a 256 y usar 8bits
  return (analogRead(analogIn) * 256)/1024;
}

void output_gpio(int distance, int pote) 
{
  // Output each bit to bits
  digitalWrite(dist_bit0, (distance & B00000001) ? HIGH : LOW);
  digitalWrite(dist_bit1, (distance & B00000010) ? HIGH : LOW);
  digitalWrite(dist_bit2, (distance & B00000100) ? HIGH : LOW);
  digitalWrite(dist_bit3, (distance & B00001000) ? HIGH : LOW);
  digitalWrite(dist_bit4, (distance & B00010000) ? HIGH : LOW);
  digitalWrite(dist_bit5, (distance & B00100000) ? HIGH : LOW);
  digitalWrite(dist_bit6, (distance & B01000000) ? HIGH : LOW);
  digitalWrite(dist_bit7, (distance & B10000000) ? HIGH : LOW);

  digitalWrite(pote_bit0, (pote & B00000001) ? HIGH : LOW);
  digitalWrite(pote_bit1, (pote & B00000010) ? HIGH : LOW);
  digitalWrite(pote_bit2, (pote & B00000100) ? HIGH : LOW);
  digitalWrite(pote_bit3, (pote & B00001000) ? HIGH : LOW);
  digitalWrite(pote_bit4, (pote & B00010000) ? HIGH : LOW);
  digitalWrite(pote_bit5, (pote & B00100000) ? HIGH : LOW);
  digitalWrite(pote_bit6, (pote & B01000000) ? HIGH : LOW);
  digitalWrite(pote_bit7, (pote & B10000000) ? HIGH : LOW);
}

int calculateDistance(){ 
    digitalWrite(trig, LOW); 
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
    return duration*0.034/2;
}