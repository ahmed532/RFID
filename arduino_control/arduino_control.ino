#include <SPI.h>
#include <Ethernet.h>

String msg, data_received;
boolean flag = false;
char c;
boolean access=false;
char o='O';
char y='Y';

void(* resetFunc) (void) = 0;
int alphaNum(String tag){
  for (int i=0;i<tag.length(); i++)
    if (!((tag[i] >= 'a' && tag[i] <= 'z') ||
          (tag[i] >= 'A' && tag[i] <= 'Z') || 
          (tag[i] >= '0' && tag[i] <= '9')))
      return 0;
  return 1;
}

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.1.14";
IPAddress ip(192,168,1,4);
EthernetClient client;

void setup() {
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  NotValid:
  msg = "";
  flag = false;
  while(Serial.available()>0) {
    //Serial.println("loooooping");
    //Serial.println(msg);
    c=Serial.read();
    if(flag) msg+=c;
    if (msg.length() == 12) {
      c=Serial.read();
      c=Serial.read();
      Serial.println(msg);
      break;
    }
    flag = true;
  }
  msg.trim();
  if(!alphaNum(msg) || msg.length() != 12){
  delay(20);
  goto NotValid;
  }
  Serial.print("#");Serial.print(msg);Serial.println("#");
  String req = "GET /auth.php?q=" + msg + " HTTP/1.1";
  //Serial.println(req);
  delay(50);
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println(req);
    client.println("Host: 192.168.1.14");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed");
  }
}

void loop(){
  while (client.available()>0) {
    char c = client.read();
    Serial.print(c);
    data_received+=c;
  }

  if (data_received[data_received.length()-4] == o)
  {
    access=true;
    digitalWrite(7, HIGH);
  }
  else
  {
    access=false;
    digitalWrite(6, HIGH);
  }
  resetFunc();
}
