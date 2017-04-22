#include <ESP8266WiFi.h>
#include <aREST.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char* ssid = "*****";
const char* password = ******";
#define LISTEN_PORT           80
int ledPin = D4;
void connectWiFi(const char* network_name, const char* network_password, int pauseMs);
void initRest(int id, String name);
int lcdMessage(String message);
int cnt;


WiFiServer server(LISTEN_PORT);
LiquidCrystal_I2C lcd(0x27, 16, 2);
aREST rest = aREST();

void setup() {
  Serial.begin(115200);
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  
  connectWiFi(ssid, password, 500);
  initRest("1", "wf8266");
  lcd.init();
  
  lcdMessage("Hello, World!");
  cnt = 0;
}

void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}


void connectWiFi(const char* network_name, const char* network_password, int pauseMs) {
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(network_name);
  WiFi.begin(network_name, network_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(pauseMs);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started: ");
  Serial.println(WiFi.localIP());
}

int lcdMessage(String message) {
  Serial.print("LCD: ");
  Serial.println(message);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  return cnt++;
}

void initRest(String id, String name) {
  rest.set_id(id);
  rest.set_name(name);
  delay(10);
  Serial.println("rest registered: ");
  Serial.print("id=");
  Serial.print(id);
  Serial.print(", name=");
  Serial.print(name);
  rest.function("lcd", lcdMessage);
  Serial.println("lcd => lcdMessage");
}

