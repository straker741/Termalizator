#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "constants.cpp"

//#define DEBUGGING
#define ONE_WIRE_BUS  2
#define RELAY_PIN     0

#define HOST "termalizator"
#define SSID "wlan"
#define PASS "jijxodan137"
#define PORT 80

void handleApiConfig(void);
void handleApiData(void);
void printRequest(void);

enum TermalizatorMode { MIN, AVG, MAX, MODE_LENGTH };

volatile struct Termalizator {
    bool power = false;
    bool measure = false;
    float target = 0;
    float temp = 0;
    unsigned int time = 0;
    TermalizatorMode mode = TermalizatorMode::AVG;
} termalizator;

ESP8266WebServer server(PORT);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void ICACHE_RAM_ATTR ISR_TIMER1(void) {
    timer1_write(312500); // Reset timer
    termalizator.time++;
    termalizator.measure = true;
}

void server_setup(void) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        #ifdef DEBUGGING
        Serial.print(".");
        #endif
    }

    #ifdef DEBUGGING
    Serial.print("\nhttp://");
    Serial.print(WiFi.localIP());
    Serial.printf(":%d/\r\n", PORT);
    #endif

    #ifdef DEBUGGING
    if (MDNS.begin(HOST)) {
        Serial.printf("http://%s/\r\n", HOST);
    }
    #else
    MDNS.begin(HOST);
    #endif

    // Api routes
    server.on("/api/config", HTTP_GET, handleApiConfig);
    server.on("/api/data", HTTP_GET, handleApiData);

    // Inline hooks
    server.on("/", HTTP_GET, []() {
        #ifdef DEBUGGING
        printRequest();
        #endif
        server.send_P(200, "text/html", INDEX);
    });
    server.on("/main.css", HTTP_GET, []() {
        #ifdef DEBUGGING
        printRequest();
        #endif
        server.send_P(200, "text/css", CSS);
    });
    server.on("/main.js", HTTP_GET, []() {
        #ifdef DEBUGGING
        printRequest();
        #endif
        server.send_P(200, "text/javascript", JS);
    });
    server.onNotFound([]() {
        #ifdef DEBUGGING
        printRequest();
        #endif
        server.send(404, "text/plain", "");
    });

    server.begin();
}

void timer1_setup(void) {
    timer1_attachInterrupt(ISR_TIMER1);
    timer1_enable(TIM_DIV256, TIM_EDGE, TIM_SINGLE);
    timer1_write(312500);
}

// SETUP
void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

    #ifdef DEBUGGING
    Serial.begin(115200);
    Serial.println("Termalizator!");
    #endif

    server_setup();
    timer1_setup();
    sensors.begin();
}

// LOOP
void loop() {
    if (termalizator.measure) {
        termalizator.measure = false;
        if (termalizator.power && sensors.getDS18Count() != 0) {
            // Request execution of temperature reading to all devices on the bus
            sensors.requestTemperatures();

            // Saving temperatures
            float minTemp = 255, maxTemp = -255, sumTemp = 0;
            uint8_t n = 0;
            for (uint8_t i = 0; i < sensors.getDS18Count(); i++) {
                float T = sensors.getTempCByIndex(i);
                if (T != DEVICE_DISCONNECTED_C) {
                    minTemp = min(T, minTemp);
                    maxTemp = max(T, maxTemp);
                    sumTemp = sumTemp + T;
                    n++;
                }
            }

            switch(termalizator.mode) {
                case TermalizatorMode::MIN:
                    termalizator.temp = minTemp;
                    break;
                case TermalizatorMode::MAX:
                    termalizator.temp = maxTemp;
                    break;
                case TermalizatorMode::AVG:
                default:
                    termalizator.temp = sumTemp / (float)n;
                    break;
            }

            if (termalizator.temp > termalizator.target)
                digitalWrite(RELAY_PIN, HIGH);
            else
                digitalWrite(RELAY_PIN, LOW);
        }
        else {
            digitalWrite(RELAY_PIN, HIGH);
        }
    }

    server.handleClient();
    MDNS.update();
}

void handleApiConfig(void) {
    #ifdef DEBUGGING
    printRequest();
    #endif
    if (server.hasArg("target")) {
        String target = server.arg("target");
        termalizator.target = target.toFloat();
    }
    if (server.hasArg("power")) {
        String power = server.arg("power");
        termalizator.power = power == "0" ? false : true;
        termalizator.time = 0;
    }
    if (server.hasArg("mode")) {
        String mode = server.arg("mode");
        if (mode == "0")
            termalizator.mode = TermalizatorMode::MIN;
        else if (mode == "1")
            termalizator.mode = TermalizatorMode::AVG;
        else if (mode == "2")
            termalizator.mode = TermalizatorMode::MAX;
        else
            termalizator.mode = TermalizatorMode::AVG;
    }
    server.send(200, "text/plain", "");
}

void handleApiData(void) {
    #ifdef DEBUGGING
    printRequest();
    #endif

    char data[256];
    snprintf(data, 256,
    "{\
        \"power\":\"%s\",\
        \"target\":\"%.3f\",\
        \"temp\":\"%.3f\",\
        \"time\":%d,\
        \"mode\":%d\
    }",
    termalizator.power ? "1" : "0",
    termalizator.target,
    termalizator.temp,
    termalizator.time,
    (uint8_t)termalizator.mode);

    server.send(200, "application/json", data);
}

void printRequest(void) {
    switch(server.method()) {
        case HTTP_OPTIONS:
            Serial.print("OPTIONS ");
            break;
        case HTTP_DELETE:
            Serial.print("DELETE ");
            break;
        case HTTP_PATCH:
            Serial.print("PATCH ");
            break;
        case HTTP_PUT:
            Serial.print("PUT ");
            break;
        case HTTP_POST:
            Serial.print("POST ");
            break;
        case HTTP_HEAD:
            Serial.print("HEAD ");
            break;
        case HTTP_GET:
            Serial.print("GET ");
            break;
        case HTTP_ANY:
        default:
            Serial.print("ANY ");
            break;
    }
    Serial.printf("%s", server.uri().c_str());
    int args = server.args();
    if (args != 0) {
        Serial.printf("?%s=", server.argName(0).c_str());
        Serial.print(server.arg(0).c_str());
        for (uint8_t i = 1; i < args; i++) {
            Serial.printf("&%s=", server.argName(i).c_str());
            Serial.print(server.arg(i).c_str());
        }
    }
    Serial.print("\n\n");
}
