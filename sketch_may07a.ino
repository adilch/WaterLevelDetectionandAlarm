// for ultrasonic
#include <NewPing.h>
// for GSM
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char msg;
char call;
boolean sndMsg = false;
float valueFromSensor;

//Define Trig and Echo pin
#define trigPin 11
#define echoPin 12
// Define maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_DISTANCE 300
//NewPing setup of pins and maximum distance.
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); 
void setup()
{
Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
mySerial.begin(9600);   // Setting the baud rate of GSM Module 
 Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("c : to make a call");
  Serial.println();
  delay(100);
}
void loop()
{
delay(50); //Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//Serial.print("Distance = ");
//Serial.print(sonar.ping_in()); // Send ping, get distance in cm and print result (0 = outside set distance range)
//Serial.println(" inch");

valueFromSensor = sonar.ping_in();

//to check the distance is gt than 40 inch


//
if(valueFromSensor >= 40 && sndMsg==true){    
    
//    SendMessage();
//MakeCall();
  Serial.println("this is float inch  gt 40 inch away");
sndMsg=false;
   
}

if(valueFromSensor<30){
  sndMsg=true;
  Serial.println(valueFromSensor);
  }

//end to check the distance gt than 40 inch away

 
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'c':
      MakeCall();
      break;
    case 'i':
      ReceiveCall();
      break;
  }
 if (mySerial.available()>0)
 Serial.write(mySerial.read());
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+9779860236578\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Water Level is getting low.");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call=mySerial.read();
    Serial.print(call);
  }
}


void MakeCall()
{
  mySerial.println("ATD+9779860236578;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}
