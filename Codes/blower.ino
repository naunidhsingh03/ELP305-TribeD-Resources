const int poten = A3; 
      int var;

void setup()
{
  pinMode(6, OUTPUT);
}

void loop()
{
  var = analogRead(poten);
  analogWrite(6,var);
  
}