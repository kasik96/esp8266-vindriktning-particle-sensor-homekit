#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

homekit_characteristic_t cha_pm25_density = HOMEKIT_CHARACTERISTIC_(PM25_DENSITY, 0);

homekit_characteristic_t cha_air_quality = HOMEKIT_CHARACTERISTIC_(AIR_QUALITY, 0);

homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Air Quality Sensor - VINDRIKTNING");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_sensor, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Air Quality Sensor - VINDRIKTNING"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "VINDRIKTNING - Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(AIR_QUALITY_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &cha_pm25_density,
            &cha_air_quality,
            &cha_name,
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"
};
