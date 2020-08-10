#include <WiFi.h>

// Wifi constants
const int RESPONSE_TIMEOUT = 6000;    // ms to wait for response from host
const int POSTING_PERIOD = 6000;      // periodicity of getting a number fact.
const uint16_t IN_BUFFER_SIZE = 1000; // size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 1000;// size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE];  // char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE];// char array buffer to hold HTTP response
char network[] = "Amador_G";
char password[] = "18281829";

// variables
const int LOOP_PERIOD = 100;
int primary_timer = 0;

// variables for the buzzer
const int BUZZER_PIN = 33;
const int BUZZ_DURATION = 250;
int buzzer_timer;
boolean buzzer_on = false;

int local_parity = 0;

void setup () {
  Serial.begin (115200);
  initWifi();
  pinMode(33, OUTPUT);
  primary_timer = millis();
  buzzer_timer = millis();
}

void loop () {
  // Send the Get Request to the web server
  sprintf(request_buffer, "GET /hurt HTTP/1.1\r\n");
  strcat(request_buffer, "Host: 73.231.51.90:80 \r\n");
  strcat(request_buffer, "\r\n"); //header
  do_http_request("73.231.51.90", request_buffer, response_buffer, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT, true);

  // Parse the response (char[]) as an integer
  int parity = 0;
  sscanf(response_buffer, "%d", &parity);

  // If the parity changed, then begin buzzing
  if (parity != local_parity) {
    local_parity = parity;
    // Update the state of the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    buzzer_timer = millis();
    buzzer_on = true;
  }

  // Delay until the amount of time has elapsed
  while (millis() - primary_timer < LOOP_PERIOD) {
    // Check if the buzzer needs to be turned off
    if (buzzer_on && millis() - buzzer_timer > BUZZ_DURATION) {
      buzzer_on = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  primary_timer = millis();
}
