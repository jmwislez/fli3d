#define PKT_TM        0 
#define PKT_TC        1
#define APID_OFFSET   100
#define NUMBER_OF_PID 2

#include <WiFi.h>
#include "WiFiUdp.h"

WiFiUDP wifiUDP;

char*    wifi_ssid = "your_wifi_ssid";
char*    wifi_password = "your_wifi_password";
char*    yamcs_server = "your_ip_address";
uint16_t yamcs_tm_port = 10015;

struct __attribute__ ((packed)) ccsds_hdr_t {
  uint8_t  apid_H:3;                // 0:5
  bool     sec_hdr:1;               // 0: 4
  bool     type:1;                  // 0:  3
  uint8_t  version:3;               // 0:   0
  uint8_t  apid_L;                  // 1
  uint8_t  seq_ctr_H:6;             // 2:2
  uint8_t  seq_flag:2;              // 2: 0
  uint8_t  seq_ctr_L;               // 3
  uint8_t  pkt_len_H;               // 4
  uint8_t  pkt_len_L;               // 5
} ccsds_hdr;

struct __attribute__ ((packed)) packet1_t {
  uint32_t millis:24;               // 0+1+2
  uint16_t ctr;                     // 3+4
  uint8_t  mode:4;                  // 5:4
  bool     bool1:1;                 // 5: 3
  bool     bool2:1;                 // 5:  2
  bool     bool3:1;                 // 5:   1
  bool     bool4:1;                 // 5:    0
  float    pressure;                // 6+7+8+9
} packet1;

struct __attribute__ ((packed)) packet2_t {
  uint32_t millis:24;               // 0+1+2
  uint16_t ctr;                     // 3+4
  float    value1;                  // 5+6+7+8
  float    value2;                  // 9+10+11+12
} packet2;

void ccsds_publish (uint16_t PID, char* payload_ptr, uint16_t payload_len) {
  update_ccsds_hdr (PID, PKT_TM, payload_len);
  wifiUDP.beginPacket(yamcs_server, yamcs_tm_port);
  wifiUDP.write ((const uint8_t*)&ccsds_hdr, sizeof (ccsds_hdr_t));
  wifiUDP.write ((const uint8_t*)payload_ptr, payload_len); 
  wifiUDP.endPacket();
}

void update_ccsds_hdr (uint16_t PID, bool pkt_type, uint16_t pkt_len) {
  static uint16_t ccsds_ctr[NUMBER_OF_PID+1];
  ccsds_ctr[PID]++;
  ccsds_hdr.version = 0;
  ccsds_hdr.type = pkt_type;
  ccsds_hdr.sec_hdr = false;
  ccsds_hdr.apid_H = (uint8_t)((PID + APID_OFFSET) >> 8);
  ccsds_hdr.apid_L = (uint8_t)(PID + APID_OFFSET);
  ccsds_hdr.seq_flag = 3;
  ccsds_hdr.seq_ctr_H = (uint8_t)(ccsds_ctr[PID] >> 8);
  ccsds_hdr.seq_ctr_L = (uint8_t)ccsds_ctr[PID];
  ccsds_hdr.pkt_len_H = (uint8_t)((pkt_len - 1) >> 8);
  ccsds_hdr.pkt_len_L = (uint8_t)(pkt_len - 1);
  Serial.print ("[version:");
  Serial.print (ccsds_hdr.version);
  Serial.print ("|type:");
  Serial.print (ccsds_hdr.type);
  Serial.print ("|sec_hdr:");
  Serial.print (ccsds_hdr.sec_hdr);
  Serial.print ("|apid:");
  Serial.print (256*ccsds_hdr.apid_H+ccsds_hdr.apid_L);
  Serial.print ("|ctr:");
  Serial.print (ccsds_ctr[PID]);
  Serial.print ("|len:");
  Serial.print (pkt_len - 1);
  Serial.println ("]");
}

void setup() {
  Serial.begin (115200);
  Serial.println ();
  WiFi.begin (wifi_ssid, wifi_password);
  Serial.print ("Connecting");
  while (WiFi.status () != WL_CONNECTED)
  {
    delay (500);
    Serial.print (".");
  }
  Serial.println ();
  Serial.print ("Connected, IP address: ");
  Serial.println (WiFi.localIP());
}

void loop() {
  static uint32_t next_second;
  if (millis() > next_second) {
    next_second = millis() + 1000;
    packet1.millis = millis();
    packet1.ctr++;
    packet1.mode = random (0,4);
    packet1.bool1 = false;
    packet1.bool2 = random (0,2);
    packet1.bool3 = random (0,2);
    packet1.bool4 = true;
    packet1.pressure = (float)(random (1000000,1013000))/1000;
    ccsds_publish (1, (char*)&packet1, sizeof(packet1));
    delay (500);
    packet2.millis = millis();
    packet2.ctr++;
    packet2.value1 = (float)(random (-10000,10000))/1000;
    packet2.value2 = -123.456;
    ccsds_publish (2, (char*)&packet2, sizeof(packet2));
  }
}
