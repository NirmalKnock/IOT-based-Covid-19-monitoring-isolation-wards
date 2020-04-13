int pirInput=9;

const int trigPin = 7;
const int echoPin = 6;

float duration, distance;

void setup()
{ 
  Serial.begin(9600);
  pinMode(pirInput,INPUT);
  pinMode(trigPin, OUTPUT);


  pinMode(echoPin, INPUT);
  Serial.begin(9600);
 
 
 
}
void loop()
{ digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(3000);
if(distance<45){//use can increase the distance

  
    Serial.println("OK");
    delay(5000);
    Serial.println("ATD+918072090514;");// change your number
    delay(20000);
    send_message();
    Serial.println("ATH");
    delay(1000);
    
  }
}
void send_message(){
 
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+918072090514\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("paitent escaped be alert");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


  
