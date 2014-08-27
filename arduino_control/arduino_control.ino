#include <SPI.h>
#include <Ethernet.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // pins on arduino
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[ROWS] = {30,28,26,24}; 
byte colPins[COLS] = {38,36,34,32};
Keypad keypad = Keypad( makeKeymap(keys), rowPins,colPins, ROWS, COLS );

int f1 = 0;
String msg, data_received, keymsg;
boolean flag = false;
char c;
boolean access=false;
char o='O';
char y='Y';
int lock= 22;

void(* resetFunc) (void) = 0;
String keyPad();
int alphaNum(String tag);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.1.14";
IPAddress ip(192,168,0,4);
EthernetClient client;

void setup() {
  Serial.begin(9600);
  pinMode(22, OUTPUT);
  pinMode(6, OUTPUT);
  lcd.begin(16, 2);
  lcd.display();
  lcd.print("Swap your card!");
  lcd.setCursor(0,1);
  lcd.print("MODE for keypad!");
  pinMode(42,OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(lock, OUTPUT);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  NotValid:
  msg = "";
  f1 = 1;
  flag = false;
  char mode = keypad.getKey();
  while(Serial.available()>0 || (mode=='*' && mode != NO_KEY)) {
    c=Serial.read();
    if(flag) msg+=c;
    if (msg.length() == 12) {
      c=Serial.read();
      c=Serial.read();
      Serial.println(msg);
      f1 = 1;
      break;
    }
    if((mode == '*' && mode != NO_KEY))
      keymsg = keyPad();
    if(keymsg.length()){
      Serial.println(keymsg);
      f1 = 0;
      break;
    }
    mode = keypad.getKey();
    flag = true;
  }
  if(f1) {
    msg.trim();
    if(!alphaNum(msg) || msg.length() != 12){
      delay(20);
      goto NotValid;
    }
  }
  else {
    msg = keymsg;
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
  //Serial.print(client.available());
  delay(200);
  //while(client.available()>0){
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
    data_received+=c;
    //Serial.print("toooot");
  }
  /*
  if(data_received[data_received.length()-5] == o)
    Serial.println("5");
  if(data_received[data_received.length()-4] == o)
    Serial.println("4");
  if(data_received[data_received.length()-3] == o)
    Serial.println("3");
  if(data_received[data_received.length()-2] == o)
    Serial.println("2");
  */
  if (data_received[data_received.length()-2] == o)
  {
    digitalWrite(22, HIGH);
    lcd.clear();
    lcd.print("ACCESS GRANTED!");
    delay(1000);
    digitalWrite(22, LOW);
  }
  else
  {
    lcd.clear();
    lcd.print("ACCESS DENIED!");
    delay(1000);
    digitalWrite(6, HIGH);
  }
  delay(200);
  resetFunc();
}

String keyPad()
{
  boolean cont = true;
  Serial.println("I'm in");
  char key;
  String keypadIn ="";
  lcd.clear();
  while (cont)
  {
    key = keypad.getKey();
    if (key != NO_KEY)
    {
      if (key!='D')
      {
        Serial.println(key);
        lcd.print("*");
        keypadIn += key;
      }
      else
      {
        cont=false;
      }
    }  
  }
  Serial.println("I'm out");
  return keypadIn;
} 

int alphaNum(String tag){
  for (int i=0;i<tag.length(); i++)
    if (!((tag[i] >= 'a' && tag[i] <= 'z') ||
          (tag[i] >= 'A' && tag[i] <= 'Z') || 
          (tag[i] >= '0' && tag[i] <= '9')))
      return 0;
  return 1;
}

