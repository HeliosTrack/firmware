/**
 *
 * @license MIT License
 *
 * Copyright (c) 2022 lewis he
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      QMI8658_GetDataExample.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @date      2022-10-16
 *
 */

#include "SensorQMI8658.hpp"
#include "qmi.h"

SensorQMI8658 qmi;

IMUdata acc;
IMUdata gyr;

SPIClass SDCardSPI(HSPI);


void RunOnceQMI()
{
    // enculer de  while (!Serial);


    pinMode(SPI_CS, OUTPUT);    //sdcard pin set high
    digitalWrite(SPI_CS, HIGH);

    // SDCard shares SPI bus with QMI8658
    // SPI has been initialized in initBoard.
    // Only need to pass SPIhandler to the QMI class.
    if (!qmi.begin(IMU_CS, -1, -1, -1, SDCardSPI)) {
        Serial.println("Failed to find QMI8658 - check your wiring!");
        while (1) {
            delay(1000);
        }
    }

    /* Get chip id*/
    Serial.print("Device ID:");
    Serial.println(qmi.getChipID(), HEX);

    qmi.configAccelerometer(
        /*
         * ACC_RANGE_2G
         * ACC_RANGE_4G
         * ACC_RANGE_8G
         * ACC_RANGE_16G
         * */
        SensorQMI8658::ACC_RANGE_4G,
        /*
         * ACC_ODR_1000H
         * ACC_ODR_500Hz
         * ACC_ODR_250Hz
         * ACC_ODR_125Hz
         * ACC_ODR_62_5Hz
         * ACC_ODR_31_25Hz
         * ACC_ODR_LOWPOWER_128Hz
         * ACC_ODR_LOWPOWER_21Hz
         * ACC_ODR_LOWPOWER_11Hz
         * ACC_ODR_LOWPOWER_3H
        * */
        SensorQMI8658::ACC_ODR_1000Hz,
        /*
        *  LPF_MODE_0     //2.66% of ODR
        *  LPF_MODE_1     //3.63% of ODR
        *  LPF_MODE_2     //5.39% of ODR
        *  LPF_MODE_3     //13.37% of ODR
        * */
        SensorQMI8658::LPF_MODE_0,
        // selfTest enable
        true);


    qmi.configGyroscope(
        /*
        * GYR_RANGE_16DPS
        * GYR_RANGE_32DPS
        * GYR_RANGE_64DPS
        * GYR_RANGE_128DPS
        * GYR_RANGE_256DPS
        * GYR_RANGE_512DPS
        * GYR_RANGE_1024DPS
        * */
        SensorQMI8658::GYR_RANGE_64DPS,
        /*
         * GYR_ODR_7174_4Hz
         * GYR_ODR_3587_2Hz
         * GYR_ODR_1793_6Hz
         * GYR_ODR_896_8Hz
         * GYR_ODR_448_4Hz
         * GYR_ODR_224_2Hz
         * GYR_ODR_112_1Hz
         * GYR_ODR_56_05Hz
         * GYR_ODR_28_025H
         * */
        SensorQMI8658::GYR_ODR_896_8Hz,
        /*
        *  LPF_MODE_0     //2.66% of ODR
        *  LPF_MODE_1     //3.63% of ODR
        *  LPF_MODE_2     //5.39% of ODR
        *  LPF_MODE_3     //13.37% of ODR
        * */
        SensorQMI8658::LPF_MODE_3,
        // selfTest enable
        true);


    // In 6DOF mode (accelerometer and gyroscope are both enabled),
    // the output data rate is derived from the nature frequency of gyroscope
    qmi.enableGyroscope();
    qmi.enableAccelerometer();

    // Print register configuration information
    qmi.dumpCtrlRegister();

    Serial.println("Read data now...");
}

Vector3 getAccelerometerData() {
    Vector3 acc = {0, 0, 0};
    if (qmi.getAccelerometer(acc.x, acc.y, acc.z)) {
        Serial.print("{ACCEL: ");
        Serial.print(acc.x);
        Serial.print(",");
        Serial.print(acc.y);
        Serial.print(",");
        Serial.print(acc.z);
        Serial.println("}");
    }
    return acc;
}

Vector3 getGyroscopeData() {
    Vector3 gyr = {0, 0, 0};
    qmi.getGyroscope(gyr.x, gyr.y, gyr.z);
    return gyr;
}
