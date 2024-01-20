const int relayPin = 2;  
const int buttonPin = 3; 

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(relayPin, LOW); 
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
	 Serial.println(buttonState);
  if (buttonState == LOW) {
    
    digitalWrite(relayPin, HIGH);
  } else {
    
    digitalWrite(relayPin, LOW);
  }
}
