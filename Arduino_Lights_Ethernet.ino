#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0, 123);
IPAddress gateway(192,168,0, 254);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously

const int kChanel1 = 1;
const int kChanel2 = 2;
const int kChanel3 = 3;

void setup() { 
  pinMode(kChanel1, OUTPUT);
  pinMode(kChanel2, OUTPUT);
  pinMode(kChanel3, OUTPUT);
  
  digitalWrite(kChanel1, HIGH);
  digitalWrite(kChanel2, HIGH);
  digitalWrite(kChanel3, HIGH);
  
  delay(1000);
  
  digitalWrite(kChanel1, LOW);
  digitalWrite(kChanel2, LOW);
  digitalWrite(kChanel3, LOW);

  
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      String command = "";
      
      char thisChar = client.read();
        
      command = String(thisChar);
      
  
      writeMyMessage("Command: [" + command + "]");
      
      if(command == "a"){
        digitalWrite(kChanel1, HIGH);
        writeMyMessage("Chanel 1 On");
      } else if (command == "e"){
         digitalWrite(kChanel1, LOW);
         writeMyMessage("Chanel 1 Off");
      } else if(command == "b"){
        digitalWrite(kChanel2, HIGH);
        writeMyMessage("Chanel 2 On");
      } else if (command == "f"){
         digitalWrite(kChanel2, LOW);
         writeMyMessage("Chanel 2 Off");
      } else if(command == "c"){
        digitalWrite(kChanel3, HIGH);
        writeMyMessage("Chanel 3 On");
      } else if (command == "g"){
         digitalWrite(kChanel3, LOW);
         writeMyMessage("Chanel 3 Off");
      } else {
        writeMyMessage("Invalid command: [" + command + "]");
      }
    }
  }   
}

int writeMyMessage(String message){            
      // echo the bytes back to the client:
      char messageArray[256] = "";
      message.toCharArray(messageArray, message.length());
      //server.write(messageArray);
      // echo the bytes to the server as well:
      Serial.write(messageArray); 
      Serial.print('\n');
      return 0;
}
