#include<LiquidCrystal.h>
#include<Ethernet.h>
#include<SPI.h>


LiquidCrystal lcd(8, 9, 5, 4, 3, 2);  // sets the interfacing pins
int Sensor_A0, Sensor_A1, Sensor_A2, reset = 1;      // Analog inputs
int CounterLcd = 1;
float Voltaje0, Voltaje1;

//Ethernet values
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE0 };
IPAddress ip(172,21,12,7);
IPAddress subnet(255,255,255,0);
IPAddress gateway(172,21,12,254);
EthernetServer server(80);

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void readData() {
  // Reads analog sensors and converts to apropiate units.
  Sensor_A0 = analogRead (A0);
  Voltaje0 = (Sensor_A0 / 51.7);
  Sensor_A1 = analogRead (A1);
  Voltaje1 = (Sensor_A1 / 51.7);
  Sensor_A2 = analogRead (A2);
}

void updateDisplay() {  // Write voltages and status in LCD Display
    if ( CounterLcd == 1) {
    lcd.setCursor(0,0);
    lcd.print("Battery: ");
    lcd.print(Voltaje0);
    lcd.print(" V");
    CounterLcd = 2;
  }
  
  else if (CounterLcd == 2) {
    lcd.setCursor(0,0);
    lcd.print("Solar  : ");
    lcd.print(Voltaje1);
    lcd.print(" V ");
    CounterLcd = 1;
  }
  
  lcd.setCursor(2,1);         //sets the cursor at row 1 column 2
  if (Sensor_A2 > 2) {
    lcd.print("Battery Mode");       
  }
  else {
      lcd.print("AC Mode");
  }
}

void setup()
{
  lcd.begin(16, 2);  // initializes the 16x2 LCD
  Ethernet.begin(mac, ip, subnet, gateway);
  server.begin();
}


void loop()
{
  readData();  
  
  updateDisplay();  
  clientConnection();
  delay (5000);
  lcd.clear();

  if (reset > 10) {  // counter to reset arduino
    resetFunc();
  }
  reset += 1;
}

void clientConnection () {
  EthernetClient client = server.available();
  if (client){
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
         if (c == '\n' && currentLineIsBlank) {
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println("Connection: close");
           //client.println("Refresh: 5");
           client.println();
           client.println("<!DOCTYPE HTML>");
           client.println("<html>");
           client.println(Voltaje0, DEC);
           client.println(Voltaje1);
           client.println(Sensor_A2);
           client.println();
           client.println("<html>");
           break;
         }
         if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
         }
         else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
         } 
      }
    }
    client.stop();
  }
}
