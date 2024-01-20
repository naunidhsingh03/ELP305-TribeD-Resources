

 
const int trigger=9;
const int echo =8;
const int LED = 13;
const int MOSFET = 12;
float time=0,distance=0;

void setup()

{

Serial.begin(9600);

 pinMode(trigger,OUTPUT);

 pinMode(echo,INPUT);

 pinMode(LED,OUTPUT);

 pinMode(MOSFET,OUTPUT);

 delay(2000);

}

void loop()
{
 measure_distance();
  Serial.println(distance);
 if(distance<40)
 {
   digitalWrite(LED,HIGH);digitalWrite(MOSFET,HIGH);
 }
 else
 {
   digitalWrite(LED,LOW);digitalWrite(MOSFET,LOW);
 }


 delay(500);

}


void measure_distance()

{

 digitalWrite(trigger,LOW);

 delayMicroseconds(2);

 digitalWrite(trigger,HIGH);

 delayMicroseconds(10);

 digitalWrite(trigger,LOW);

 delayMicroseconds(2);

 time=pulseIn(echo,HIGH);

 distance=time*340/20000;

}

