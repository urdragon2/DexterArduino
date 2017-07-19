#include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);



#define DIRECTIONA 4
#define MOTORA 5

#define DIRECTIONB 7
#define MOTORB 6 


void setup() {
 Serial.begin(9600);
 pinMode (MOTORA, OUTPUT);
 pinMode (DIRECTIONA, OUTPUT);
 pinMode (MOTORB, OUTPUT);
 pinMode (DIRECTIONB, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("MOVE");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE MOVE Peripheral");
}

void loop() {
    // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        Serial.println(switchCharacteristic.value());
        switch (switchCharacteristic.value()) {
          case 0:
            leftturn();
            break;
          case 1:
            forward();
            break;
          case 2:
            rightturn();
            break;
          case 3:
            backward();
            break;
          case 4:
            stopbot();
            break;
          default:
            stopbot();
            break;
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

void forward()
{
  digitalWrite (DIRECTIONA, 1);
  digitalWrite (DIRECTIONB, 1); 
  analogWrite (MOTORA, 255);
  analogWrite (MOTORB, 255);
}


void backward()
{
  digitalWrite (DIRECTIONA, 0);
  digitalWrite (DIRECTIONB, 0); 
  analogWrite (MOTORA, 255);
  analogWrite (MOTORB, 255);
}

void rightturn()
{
  digitalWrite (DIRECTIONA, 1);
  digitalWrite (DIRECTIONB, 0); 
  analogWrite (MOTORA, 196);
  analogWrite (MOTORB, 196);
}


void leftturn()
{
  digitalWrite (DIRECTIONA, 0);
  digitalWrite (DIRECTIONB, 1); 
  analogWrite (MOTORA, 196);
  analogWrite (MOTORB, 196);
}


void stopbot()
{
  digitalWrite (DIRECTIONA, 1);
  digitalWrite (DIRECTIONB, 1); 
  analogWrite (MOTORA, 0);
  analogWrite (MOTORB, 0);
}

