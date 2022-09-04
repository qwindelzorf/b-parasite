#include "shtc3.h"

#include <app_error.h>
#include <nrf_delay.h>
#include <nrf_drv_twi.h>
#include <nrf_log.h>
#include <nrf_log_ctrl.h>

#include "../../config/prst_config.h"

static const nrf_drv_twi_t twi_ = NRF_DRV_TWI_INSTANCE(0);
static nrf_drv_twi_config_t twi_config_ = NRF_DRV_TWI_DEFAULT_CONFIG;

static uint8_t buff[6];

static void write_cmd(uint16_t command) {
  uint8_t cmd[2];
  cmd[0] = command >> 8;
  cmd[1] = command & 0xff;
  APP_ERROR_CHECK(nrf_drv_twi_tx(&twi_, PRST_SHTC3_ADDR, cmd, 2,
                                 /*no_stop=*/false));
}

void prst_shtc3_init() {
  twi_config_.scl = PRST_SHT3C_SCL_PIN;
  twi_config_.sda = PRST_SHT3C_SDA_PIN;
  twi_config_.frequency = NRF_TWI_FREQ_100K;
}

prst_shtc3_read_t prst_shtc3_read() {
  APP_ERROR_CHECK(nrf_drv_twi_init(&twi_, &twi_config_, NULL, NULL));
  nrf_drv_twi_enable(&twi_);

  // Wake the sensor up.
  write_cmd(PRST_SHTC3_CMD_WAKEUP);
  nrf_delay_ms(1);

  // Request measurement.
  write_cmd(PRST_SHTC3_CMD_MEASURE_TFIRST_NORMAL);

  // Reading in normal (not low power) mode can take up to 12.1 ms, according to
  // the datasheet.
  nrf_delay_ms(15);

  // Read temp and humidity.
  while (nrf_drv_twi_rx(&twi_, PRST_SHTC3_ADDR, buff, 6) != 0) {
    nrf_delay_ms(10);
  }
  // Put the sensor in sleep mode.
  write_cmd(PRST_SHTC3_CMD_SLEEP);

  // Uninit i2c.
  nrf_drv_twi_uninit(&twi_);

  // TODO(rbaron): verify the CRC of the measurements. The function is described
  // in the datasheet.

  float temp_c = -45 + 175 * ((float)((buff[0] << 8) | buff[1])) / (1 << 16);
  uint16_t humi = (buff[3] << 8) | buff[4];

  prst_shtc3_read_t ret = {.temp_celsius = temp_c, .humidity = humi};

#if PRST_SHT3C_DEBUG
  NRF_LOG_INFO("[sht3c] Read temp: " NRF_LOG_FLOAT_MARKER " oC",
               NRF_LOG_FLOAT((float)ret.temp_celsius));
  NRF_LOG_INFO("[sht3c] Read humi: " NRF_LOG_FLOAT_MARKER " %%",
               NRF_LOG_FLOAT(100.0 * ret.humidity / 0xffff));
#endif
  return ret;
}