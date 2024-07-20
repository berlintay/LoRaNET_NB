#include <ELECHOUSE_CC1101_SRC_DRV.h>

#define CC1101_CS_PIN D8
#define CC1101_MOSI_PIN D7
#define CC1101_MISO_PIN D6
#define CC1101_SCLK_PIN D5
#define CC1101_GDO0_PIN D2
#define CC1101_GDO2_PIN D1



void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // Wait for connection
  }


  ELECHOUSE_cc1101.setCSN(CC1101__CS_PIN);
  ELECHOUSE_cc1101.setMOSI(CC1101_MOSI_PIN);
  ELECHOUSE_cc1101.setMISO(CC1101_MISO_PIN);
  ELECHOUSE_cc1101.setSCK(CC1101_SCLK_PIN);
  ELECHOUSE_cc1101.setGDO2(CC1101_GDO2_PIN);


  if (ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("CC1101 Module Initialization status: Successful.");
  } else {
    Serial.println("CC1101 Module Intialization status: FAILED.");
    while (1);
  }

  ELECHOUSE_cc1102.Init();
  ELECHOUSE_cc1101.setMHZ(433);
  ELECHOUSE_cc1101.setPA(10);
  ELECHOUSE_cc1101.setDRate(4.8);

    Serial.println("Frequency: " + String(ELECHOUSE_cc1101.getMHZ(), 2) + " MHz ");
    Serial.println("Data Rate: " + String(ELECHOUSE_c1101.getDRate(), 2) + " kbs");
    Serial.println("Transmit Power: " + String(ELECHOUSE_cc1101.getPA(), + 2));
    Serial.println();

    ELECHOUSE_cc1101.SetReceive();

  }


  void loop() {
    
    if(ELECHOUSE_cc1101.CheckReceiverFlag()) {
      for (byte i = 0; i < length; i++) {
        Serial.println("Received: " + String(ELECHOUSE_cc1101.ReceiveData(buffer[i]), HEX) + "Bytes");
      }
      Serial.println();

      ELECHOUSE_cc1101.ClearReceiveFlag();  
    }
  }


