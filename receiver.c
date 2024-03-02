#include <WiFi.h>
#include <PubSubClient.h>
#include <LoRa.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(15, 4, 16);

// LoRA
#define SCK 5 // GPIO5 -- SX127x's SCK
#define MISO 19 // GPIO19 -- SX127x's MISO
#define MOSI 27 // GPIO27 -- SX127x's MOSI
#define SS 18 // GPIO18 -- SX127x's CS
#define RST 14 // GPIO14 -- SX127x's RESET
#define DI0 26 // GPIO26 -- SX127x's IRQ(Interrupt Request)

long int freq, freq_or;
long int sf, sf_or;
long int sb, sb_or;

// LoRA packet
union pack
{
  uint8_t frame[16]; // trames avec octets
  float data[4]; // 4 valeurs en virgule flottante
} sdp ; // paquet d’émission

// WiFi
const char *ssid = "raspi-webgui"; // Enter your WiFi name
const char *password = "RASPI_TP";  // Enter WiFi password
bool loraConfigured = false;
// MQTT Broker
const char *mqtt_broker = "10.3.141.205";
const char *topic = "srt/jvas";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
float d1=12.0, d2=321.54 ;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 9600;
 Serial.begin(9600);
 u8x8.begin(); u8x8.setFont(u8x8_font_chroma48medium8_r);
  
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
     u8x8.drawString(0,0, "Connecting WiFi..");
 }
 
 Serial.println("Connected to the WiFi network");
 u8x8.drawString(0,0, "Connecting OK !");

 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);

 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("MQTT broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
  client.publish(topic, "Valou UwU");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    char buf[length + 1];
    buf[length] = '\0';

     for (int i = 0; i < length; i++) {
     buf[i] = (char) payload[i];
    }

    sscanf(buf, "%ld;%ld;%ld", &freq_or, &sf_or, &sb_or);
  if ((freq_or != freq) || (sf_or != sf)  || (sb_or != sb)) {
      freq = freq_or;
      sf = sf_or;
      sb = sb_or;
      Serial.println("Reconfig LORA");
      Serial.println(freq_or);
      Serial.println(sf_or);
      Serial.println(sb_or);
      configLoRa();
    }

 /*Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------"); */
}

void configLoRa() {
    // LoRA
  pinMode(DI0, INPUT); // signal interrupt
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);

  if (!LoRa.begin(freq)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(sf);
  LoRa.setSignalBandwidth (sb);
  //LoRa.onReceive(onReceive);
  loraConfigured = true;

  // put the radio into receive mode
  //LoRa.receive();
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }

  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}

void loop() {

  client.loop();
  if (loraConfigured) {
      Serial.println("New Packet") ;

      LoRa.beginPacket(); // start packet
      sdp.data[0]=d1;
      sdp.data[1]=d2;
      LoRa.write(sdp.frame,16);
      LoRa.endPacket();

      d1++; d2+=2;
  }
  delay(2000);
}
