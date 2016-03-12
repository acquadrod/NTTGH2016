

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

 

int longPin = 2;
int shortPin = 7;
int num=0;
char msg[50];

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(10, 165,68, 74);
IPAddress server(10, 165, 64, 239);
IPAddress netmask(255, 255, 248, 0);
IPAddress gateway(10, 165, 64, 1);


EthernetClient ethClient;
PubSubClient client(ethClient);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

   if ((char)payload[0] == 'L') {
      digitalWrite(longPin,HIGH);
      delay(100);
      digitalWrite(longPin,LOW);
      num++;
      Serial.println("serving Long coffe ");
       snprintf (msg, 75, "total #%d", num);
       client.publish("machine1",msg);
        Serial.println(num);
     
   } else if  ((char)payload[0] == 'S') {
      digitalWrite(shortPin,HIGH);
      delay(100);
      digitalWrite(shortPin,LOW);
      num++;
      Serial.println("serving Espresso coffe ");
      Serial.println(num);
      snprintf (msg, 75, "total #%d", num);
      client.publish("machine1",msg);
     
      
   } else {
      digitalWrite(longPin,LOW);
      digitalWrite(shortPin,LOW);
      Serial.println("stopping coffe ");
       Serial.println(num);
   }
 
  Serial.println();
 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // ... and resubscribe
      client.subscribe("coffe");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);

  num=0;
  pinMode(longPin, OUTPUT);
  pinMode(shortPin, OUTPUT);
  client.setServer(server, 1883);
  client.setCallback(callback);

   Ethernet.begin(mac, ip, gateway, gateway, netmask);
  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());
 
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
