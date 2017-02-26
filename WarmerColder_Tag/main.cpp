#include "mbed.h"
#include "ble/BLE.h"
#include "color.h"

//#define TINY_BLE

#define BAUD_RATE       115200 // baud

#define UPDATE_INTERVAL 500 // ms

#define SCAN_INTERVAL   160 // units of 0.625ms
#define SCAN_WINDOW     SCAN_INTERVAL // units of 0.625ms

#define ADV_INTERVAL    200 // ms
#define TX_POWER        -4 // dBm

#define TAG_NAME        "WarmerColderTag"
Gap::Address_t addr = {0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

#define MAGIC_RX_LEN    3
#define MAGIC_TX_LEN    3
const uint8_t magic_rx[MAGIC_RX_LEN] = {0xC0, 0xFF, 0xEE}; // COFFEE
const uint8_t magic_tx[MAGIC_TX_LEN] = {0xBA, 0x6E, 0x15}; // BAGELS

#define RSSI_RED        -40 // dBm

#ifdef TINY_BLE
#define RED_PIN         p22
#define GREEN_PIN       p21
#define BLUE_PIN        p23
#else
// nRF51822 Smart Beacon
#define RED_PIN         p16
#define GREEN_PIN       p12
#define BLUE_PIN        p15
#endif
PwmOut red_led(RED_PIN);
PwmOut green_led(GREEN_PIN);
PwmOut blue_led(BLUE_PIN);

Ticker t;
Timer clk;
Serial serial(p9, p11);
BLE& ble = BLE::Instance(BLE::DEFAULT_INSTANCE);

struct datapoint {
    int timestamp;
    int rssi;
};

// Circular buffer for calculating rolling average
#define AVG_LAST_N_MILLISECONDS         2000
#define MAX_RECEIVED_ADVERTISEMENTS     50
struct datapoint receivedAdvertisements[MAX_RECEIVED_ADVERTISEMENTS];
int recvAdvHeadIdx, recvAdvTailIdx;


void setRGB(float r, float g, float b) {
    red_led = 1.0 - r;
    green_led = 1.0 - g;
    blue_led = 1.0 - b;
}

void setHSV(float h, float s, float v) {
    float r, g, b;
    HSVtoRGB(r, g, b, h, s, v);
    setRGB(r, g, b);
}

void setHue(int rssi) {
    float hue;
    if (rssi > -80) {
        hue = 0;
    } else if (rssi > -90) {
        hue = 335;
    } else if (rssi > -100) {
        hue = 260;
    } else {
        hue = 240;
    }
    setHSV(hue, 1, 1);
}

void ledUpdateCallback(void) {
    int sum = 0;
    int total = 0;
    int avg = -105;
    int i = recvAdvTailIdx;
    while (i != recvAdvHeadIdx) {
        struct datapoint dp = receivedAdvertisements[i];
        if ((clk.read_ms() - dp.timestamp) > AVG_LAST_N_MILLISECONDS) {
            // Remove old data points
            recvAdvTailIdx = (recvAdvTailIdx + 1) % MAX_RECEIVED_ADVERTISEMENTS;
        } else {
            sum += dp.rssi;
            total++;
        }
        i = (i + 1) % MAX_RECEIVED_ADVERTISEMENTS;
    }
    if (total > 0) {
        avg = sum / total;
    } else {
        printf("%d, %d, %d\n", recvAdvTailIdx, recvAdvHeadIdx, i);
    }
#ifdef TINY_BLE
    printf("Avg RSSI: %d\n", avg);
#endif
    
    setHue(avg);
    wait(0.1);
    setRGB(0, 0, 0);
}

void advertisementReceivedCallback(const Gap::AdvertisementCallbackParams_t *params) {
    // Check if the advertisement came from the phone
    // Android offsets the manufacturer specific data by 4 bytes
    if (!memcmp(params->advertisingData + 4, &magic_rx, MAGIC_RX_LEN)) {
#ifdef TINY_BLE
        printf("%d\n", params->rssi);
#endif
        receivedAdvertisements[recvAdvHeadIdx].timestamp = clk.read_ms();
        receivedAdvertisements[recvAdvHeadIdx].rssi = params->rssi;
        recvAdvHeadIdx = (recvAdvHeadIdx + 1) % MAX_RECEIVED_ADVERTISEMENTS;
        if(recvAdvHeadIdx == recvAdvTailIdx) {
            recvAdvTailIdx = (recvAdvTailIdx + 1) % MAX_RECEIVED_ADVERTISEMENTS;
        }
    }
}

void bleInitCallback(BLE::InitializationCompleteCallbackContext *params) {
    if (params->error != BLE_ERROR_NONE ||
        ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
#ifdef TINY_BLE
        printf("Error in BLE initialization\n");
#endif
        // Indicate the error and loop forever
        setRGB(1, 0, 0);
        while (1);
    }
    
    // Setup scanning
    ble.gap().setScanParams(SCAN_INTERVAL, SCAN_WINDOW);
    ble.gap().startScan(advertisementReceivedCallback);
    
    // Setup advertising
    ble.gap().setAdvertisingType(
        GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA,
        magic_tx, MAGIC_TX_LEN);
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::BREDR_NOT_SUPPORTED);
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::SHORTENED_LOCAL_NAME,
        (const uint8_t*)TAG_NAME, sizeof(TAG_NAME));
    ble.gap().setAddress(Gap::ADDR_TYPE_RANDOM_STATIC, addr);
    ble.gap().setTxPower(TX_POWER);
    ble.gap().setAdvertisingInterval(ADV_INTERVAL);
    ble.gap().startAdvertising();
}

int main(void) {
    clk.start();
    
    setRGB(0, 0, 0);
    t.attach(ledUpdateCallback, UPDATE_INTERVAL/1000.0);

#ifdef TINY_BLE
    serial.baud(BAUD_RATE);
    printf("\nInitializing tag\n");
#endif
    
    BLE &ble = BLE::Instance();
    ble.init(bleInitCallback);
    while (!ble.hasInitialized());

    for (;;) {
        ble.waitForEvent();
    }
}
