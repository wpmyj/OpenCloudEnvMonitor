//@+leo-ver=4-thin
//@+node:gan0ling.20140624153650.3688:@shadow adns2080.h
//@@language c
//@@tabwidth -4
//@+others
//@-others
 /* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef ADNS2080_H
#define ADNS2080_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

/** @file
* @brief ADNS2080 mouse sensor driver
*
* @defgroup nrf_drivers_adns2080 ADNS2080 driver
* @{
* @ingroup nrf_drivers
* @brief ADNS2080 mouse sensor driver.
*/

/**
 * Describes return values for @ref adns2080_init.
 */
typedef enum
{
  ADNS2080_OK, /*!< Operation was succesful */
  ADNS2080_SERIAL_COMM_FAILURE, /*!< Serial communication failed */
  ADNS2080_CHIP_NOT_DETECTED, /*!< Product/Revision ID was not what was expected */
  ADNS2080_INVALID_PARAMETER /*!< Given parameters were not valid */
} adns2080_status_t;

/**
 * ADNS2080 motion output pin polarity values.
 */
typedef enum
{
  ADNS2080_MOTION_OUTPUT_POLARITY_LOW = 0,  /*!< Motion output polarity active low */
  ADNS2080_MOTION_OUTPUT_POLARITY_HIGH = 1  /*!< Motion output polarity active high */
} motion_output_polarity_t;

/**
 * Motion output pin configuration.
 */
typedef enum
{
  ADNS2080_MOTION_OUTPUT_SENSITIVITY_LEVEL = 0,  /*!< Motion output pin will be driven low/high (depending on the polarity setting) as long as there is motion data in DELTA registers */
  ADNS2080_MOTION_OUTPUT_SENSITIVITY_EDGE = 1  /*!< Motion output pin will be driven low/high (depending on the polarity setting) for 380 ns when motion is detected during rest modes */
} motion_output_sensitivity_t;

/**
 * Mouse sensor resolution values.
 */
typedef enum
{
  ADNS2080_RESOLUTION_250DPI = 1, /*!< 250 dpi resolution */
  ADNS2080_RESOLUTION_500DPI = 2, /*!< 500 dpi resolution */
  ADNS2080_RESOLUTION_1000DPI = 0, /*!< 1000 dpi resolution */
  ADNS2080_RESOLUTION_1250DPI = 3, /*!< 1250 dpi resolution */
  ADNS2080_RESOLUTION_1500DPI = 4, /*!< 1500 dpi resolution */
  ADNS2080_RESOLUTION_1750DPI = 5, /*!< 1750 dpi resolution */
  ADNS2080_RESOLUTION_2000DPI = 6 /*!< 2000 dpi resolution */
} adns2080_resolution_t;

/**
 * Mouse sensor forced mode options.
 */
typedef enum
{
  ADNS2080_MODE_NORMAL = 0, /*!< Normal operation mode */
  ADNS2080_MODE_REST1 = 1, /*!< Rest1 operation mode */
  ADNS2080_MODE_REST2 = 2, /*!< Rest2 operation mode */
  ADNS2080_MODE_REST3 = 3, /*!< Rest3 operation mode */
  ADNS2080_MODE_RUN1 = 4, /*!< Run1 operation mode */
  ADNS2080_MODE_RUN2 = 5, /*!< Run2 operation mode */
  ADNS2080_MODE_IDLE = 6 /*!< Idle operation mode */
} adns2080_mode_t;

/**
 * Mouse sensor motion reporting bits.
 */
typedef enum
{
  ADNS2080_MOTION_BITS_8 = 0,  /*!< Motion reporting uses 8 bits */
  ADNS2080_MOTION_BITS_12 = 1  /*!< Motion reporting uses 12 bits */
} adns2080_motion_bits_t;

/**
 * @brief Function for initializing the mouse sensor chip.
 *
 * Valid mouse sensor information will be available 50 milliseconds after this
 * function finishes.
 * 
 * @return 
 * @retval ADNS2080_OK Mouse sensor was initialized succesfully.
 * @retval ADNS2080_SERIAL_COMM_FAILURE Serial communications failure.
 * @retval ADNS2080_CHIP_NOT_DETECTED Could not find revision 0 ADNS2080 chip.
 */
adns2080_status_t adns2080_init(void);

/**
 * @brief Function for resetting the mouse sensor chip.
 *
 * Valid mouse sensor information will be available 50 milliseconds after this
 * function finishes.
 * All register settings will be lost and need to be reloaded.
 * 
 */
void adns2080_reset(void);

/**
 * @brief Function for reading mouse sensor product ID.
 *
 * Chip is expected to be initialized before calling this function.
 * Returned product ID should always be 0x2A.
 *
 * @return Product ID.
 */
uint8_t adns2080_product_id_read(void);

/**
 * @brief Function for reading mouse sensor revision ID.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @return Product ID.
 */
uint8_t adns2080_revision_id_read(void); // also note there is "not rev id" register

/**
 * @brief Function for powering down the mouse sensor.
 *
 * Chip is expected to be initialized before calling this function.
 * Serial port should not be accessed during the power down. To exit the power
 * down mode, @ref adns2080_wakeup must be called.
 *
 */
void adns2080_powerdown(void);

/**
 * @brief Function for waking up the mouse sensor.
 *
 * After wakeup, all mouse sensor settings must be reloaded. Valid mouse sensor 
 * information will be available 55 milliseconds after this function finishes. 
 */
void adns2080_wakeup(void);

/**
 * @brief Function for configuring the MOTION interrupt output pin.
 *
 * When motion is detected by the mouse sensor, the chip has a MOTION pin 
 * indicating there is motion data in DELTA_X and DELTA_Y registers. This 
 * function configures the polarity and sensitivity of that pin.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @param polarity MOTION output pin is either active LOW (default) or active HIGH
 * @param sensitivity Level or Edge (default) sensitive 
 * @return
 * @retval ADNS2080_OK Operation succeeded.
 * @retval ADNS2080_INVALID_PARAMETER One of the parameters was not within valid range.
 */
adns2080_status_t adns2080_motion_interrupt_set(motion_output_polarity_t polarity, motion_output_sensitivity_t sensitivity);

/**
 * @brief Function for setting mouse sensor resolution.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @param resolution Desired resolution.
 * @return 
 * @retval ADNS2080_OK Operation succeeded.
 * @retval ADNS2080_INVALID_PARAMETER One of the parameters was not within valid range.
 */
adns2080_status_t adns2080_resolution_set(adns2080_resolution_t resolution);

/**
 * @brief Function for setting number of bits used for mouse sensor motion reporting.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @param motion_bits Desired number of bits.
 * @return 
 * @retval ADNS2080_OK Operation succeeded.
 * @retval ADNS2080_INVALID_PARAMETER One of the parameters was not within valid range.
 */
adns2080_status_t adns2080_motion_bits_set(adns2080_motion_bits_t motion_bits);

/**
 * @brief Function for reading number of bits used for mouse sensor motion reporting.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @return motion_bits Number of bits.
 */
adns2080_motion_bits_t adns2080_motion_bits_read(void);

/**
 * @brief Function for reading X- and Y-axis movement (in counts) since last report.
 *
 * Absolute value is determined by resolution. 
 * Chip is expected to be initialized before calling this function.
 *
 * @param p_delta_x Location to store X-axis movement
 * @param p_delta_y Location to store Y-axis movement
 */
void adns2080_movement_read(int16_t *p_delta_x, int16_t *p_delta_y);

/**
 * @brief Function for checking if motion has been detected since last call.
 *
 * Chip is expected to be initialized before calling this function.
 *
 * @return
 * @retval true, if movement has been detected
 * @retval false, if no movement has been detected
 */
bool adns2080_is_motion_detected(void);

/**
 * @brief Function for setting mouse sensor Rest1, Rest2 and Rest3 mode motion detection time period.
 * 
 * Allowed range for the periods is 0x01 to 0xFD.
 * Resulting period is derived from the following equation :
 * Period = (Rest period + 1) * 10 milliseconds
 * Chip is expected to be initialized before calling this function.
 *
 * @param rest1_period Rest1 period
 * @param rest2_period Rest2 period
 * @param rest3_period Rest3 period
 */
void adns2080_rest_periods_set(uint8_t rest1_period, uint8_t rest2_period, uint8_t rest3_period);

/**
 * @brief Function for setting mouse sensor mode downshift time periods.
 * 
 * Allowed range for run_to_rest1_mode_time period is 0x00 to 0xFF.
 * Allowed range for rest1_to_rest2_mode_time period is 0x01 to 0xFF. 
 * Allowed range for rest2_to_rest3_mode_time period is 0x01 to 0xFF. 
 * 
 * Chip is expected to be initialized before calling this function.
 *
 * @param run_to_rest1_mode_time Run mode to Rest1 mode downshift time period (Time = run_to_rest1_mode_time * 8 * 4)
 * @param rest1_to_rest2_mode_time Rest1 mode to Rest2 mode downshift time period (Time = rest1_to_rest2_mode_time * rest1_period * 16)
 * @param rest2_to_rest3_mode_time Rest2 mode to Rest3 mode downshift time period (Time = rest2_to_rest3_mode_time * rest2_period * 128)
 */
void adns2080_downshift_times_set(uint8_t run_to_rest1_mode_time, uint8_t rest1_to_rest2_mode_time, uint8_t rest2_to_rest3_mode_time);

/**
 * @brief Function for forcing mouse sensor to a certain operating mode.
 * 
 * Chip is expected to be initialized before calling this function.
 * Normal operation will not continue until this function is called with ADNS2080_MODE_NORMAL parameter.
 *
 * @param mode Mode to force the sensor to.
 */
void adns2080_force_mode_set(adns2080_mode_t mode);

/**
 * @brief Function for reading the current forced operating mode.
 * 
 * Chip is expected to be initialized before calling this function.
 *
 * @return Mode the sensor is forced to.
 */
adns2080_mode_t adns2080_force_mode_read(void);

/**
 *@}
 **/

/*lint --flb "Leave library region" */ 
#endif
//@-node:gan0ling.20140624153650.3688:@shadow adns2080.h
//@-leo
