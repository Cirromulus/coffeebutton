#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <wpa2_enterprise.h>


const char* ssid = "eduroam";
#define EAP_ID "ppieper@uni-bremen.de"
#define EAP_USERNAME "ppieper@uni-bremen.de"
#define EAP_PASSWORD "53494547a04845494C"

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);

  wifi_station_disconnect();
  wifi_station_set_config(&wifi_config);

  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();

  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8_t*) EAP_ID, strlen(EAP_ID));
  wifi_station_set_enterprise_username((uint8_t*) EAP_USERNAME, strlen(EAP_USERNAME));
  wifi_station_set_enterprise_password((uint8_t*) EAP_PASSWORD, strlen(EAP_PASSWORD));

  wifi_station_connect();

  // WPA2 enterprise magic starts here
  /*WiFi.disconnect();
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ID, strlen(EAP_ID));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable(&config);

  */
  // WPA2 enterprise magic ends here

  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void loop() {
  // put your main code here, to run repeatedly:

}
