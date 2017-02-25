#include "mbed.h"
#include "ble/BLE.h"


#define BAUD_RATE       115200 // baud

#define SCAN_INTERVAL   160 // units of 0.625ms
#define SCAN_WINDOW     320 // units of 0.625ms

#define ADV_INTERVAL    200 // ms
#define TX_POWER        -4 // dBm

#define TAG_NAME        "WarmerColderTag"
Gap::Address_t addr = {0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

#define MAGIC_RX_LEN    3
#define MAGIC_TX_LEN    3
const uint8_t magic_rx[MAGIC_RX_LEN] = {0xC0, 0xFF, 0xEE}; // COFFEE
const uint8_t magic_tx[MAGIC_TX_LEN] = {0xBA, 0x6E, 0x15}; // BAGELS


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
    setLED(1, 0, 0);
    wait(0.1);
    setLED(0, 0, 0);
}

void advertisementReceivedCallback(const Gap::AdvertisementCallbackParams_t *params) {
    // Check if the advertisement came from the phone
    if (!memcmp(params->advertisingData, &magic_rx, MAGIC_RX_LEN)) {
        printf("%d\n", params->rssi);
    }
}

void bleInitCallback(BLE::InitializationCompleteCallbackContext *params) {
    if (params->error != BLE_ERROR_NONE ||
        ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        printf("Error in BLE initialization\n");
        return;
    }
    
    // Setup scanning
    ble.gap().setScanParams(SCAN_INTERVAL, SCAN_WINDOW);
    ble.gap().startScan(advertisementReceivedCallback);
    
    // Setup advertising
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA,
        magic_tx, MAGIC_TX_LEN);
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::BREDR_NOT_SUPPORTED);
    ble.gap().setAdvertisingType(
        GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);
    ble.accumulateAdvertisingPayload(
        GapAdvertisingData::SHORTENED_LOCAL_NAME,
        (const uint8_t*)TAG_NAME, sizeof(TAG_NAME));
    ble.gap().setAddress(Gap::ADDR_TYPE_RANDOM_STATIC, addr);
    ble.gap().setTxPower(TX_POWER);
    ble.gap().setAdvertisingInterval(ADV_INTERVAL);
    ble.gap().startAdvertising();
}

int main(void) {
    setLED(0, 0, 0);
    t.attach(ledUpdateCallback, 1);

    serial.baud(BAUD_RATE);
    printf("\nInitializing tag\n");
    
    BLE &ble = BLE::Instance();
    ble.init(bleInitCallback);
    while (!ble.hasInitialized());

    for (;;) {
        ble.waitForEvent();
    }
}
