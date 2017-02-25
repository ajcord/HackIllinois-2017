#include "mbed.h"
#include "ble/BLE.h"

#define BAUD_RATE       115200
#define SCAN_INTERVAL   160 // units of 0.625ms
#define SCAN_WINDOW     SCAN_INTERVAL

PwmOut red_led(p22);
PwmOut green_led(p21);
PwmOut blue_led(p23);

Ticker t;
Serial serial(p9, p11);
BLE& ble = BLE::Instance(BLE::DEFAULT_INSTANCE);

void setLED(float r, float g, float b) {
    red_led = 1.0 - r;
    green_led = 1.0 - g;
    blue_led = 1.0 - b;
}

void ledUpdateCallback(void) {
    // TODO
    float temp = red_led;
    red_led = green_led;
    green_led = blue_led;
    blue_led = temp;
}

void advertisementReceivedCallback(const Gap::AdvertisementCallbackParams_t *params) {
    // Check if the advertisement came from the phone
    if (params->advertisingData[0] == 0xc0 &&
        params->advertisingData[1] == 0xff &&
        params->advertisingData[2] == 0xee) {
        printf("%d\n", params->rssi);
    }
}

void bleInitCallback(BLE::InitializationCompleteCallbackContext *params) {
    if (params->error != BLE_ERROR_NONE ||
        ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        printf("Error in BLE initialization\n");
        return;
    }
    
    ble.gap().setScanParams(SCAN_INTERVAL, SCAN_WINDOW);
    ble.gap().startScan(advertisementReceivedCallback);
}

int main(void) {
    setLED(0.0, 1.0, 1.0);
    t.attach(ledUpdateCallback, 1);

    serial.baud(BAUD_RATE);
    printf("\nInitializing tag\n");
    
    BLE &ble = BLE::Instance();
    ble.init(bleInitCallback);

    for (;;) {
        ble.waitForEvent();
    }
}
