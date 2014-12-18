
byte data[3];

void setup () {
  pinMode (13, OUTPUT);
  Serial.begin (9600);
  digitalWrite (13, LOW);
  *((char*) data) = 'c';
  *((int*) (data+1)) = -2;
}


void loop () {
  
  Serial.write (data, 3);
  
  delay (800);
  
}
