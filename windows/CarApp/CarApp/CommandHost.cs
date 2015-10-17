using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TegamHost
{
    /// <summary>
    /// Command host for command-response protocol between computer and PAN1740
    /// </summary>
    class CommandHost
    {
        private const bool WRITE = true;
        private const bool VERIFY = false;

        private const byte CMD_VERSION_CODE	= 1;

        private const byte CMD_MARK_START = 0x53;
        private const byte CMD_MARK_END = 0x0D;
        private const ushort CMD_MARK_HEADER = 0x3B9C;

        public enum TegamServiceCode_t
        {
            TEGAM_BASE = 0x0001,
            TEGAM_ERROR,
            TEGAM_BLUETOOTH_SET_REQ,
            TEGAM_BLUETOOTH_SET_ACK,
            TEGAM_BLUETOOTH_GET_REQ,
            TEGAM_BLUETOOTH_GET_ACK,
            /*
             *  Information
             */
            TEGAM_MODEL_NUMBER_SET_REQ = 0x0100,        // MSP430 -> PAN1740 (one-time upon startup)
            TEGAM_MODEL_NUMBER_SET_ACK,
            TEGAM_SERIAL_NUMBER_SET_REQ,                // MSP430 -> PAN1740 (one-time upon startup)
            TEGAM_SERIAL_NUMBER_SET_ACK,
            TEGAM_DEVICE_TIME_SET_REQ,                  // bidirectional
            TEGAM_DEVICE_TIME_SET_ACK,
            TEGAM_CLOCK_MODE_SET_REQ,                   // bidirectional
            TEGAM_CLOCK_MODE_SET_ACK,
            TEGAM_BATTERY_VOLTAGE_SET_REQ,              // MSP430 -> PAN1740
            TEGAM_BATTERY_VOLTAGE_SET_ACK,
            /*
             *  Temperature
             */
            TEGAM_DATA_PACKET_UPD_REQ = 0x0200,         // MSP430 -> PAN1740 (provides notification)
            TEGAM_DATA_PACKET_UPD_ACK,
            TEGAM_SEND_NEXT_READING_SET_REQ,            // PAN1740 -> MSP430
            TEGAM_SEND_NEXT_READING_SET_ACK,
            TEGAM_CHANNEL_READINGS_SET_REQ,             // MSP430 -> PAN1740
            TEGAM_CHANNEL_READINGS_SET_ACK,
            TEGAM_CHANNEL_OFFSETS_SET_REQ,              // bidirectional
            TEGAM_CHANNEL_OFFSETS_SET_ACK,
            TEGAM_THERMOCOUPLE_TYPE_SET_REQ,            // bidirectional
            TEGAM_THERMOCOUPLE_TYPE_SET_ACK,
            TEGAM_ADJUSTMENT_MODE_SET_REQ,              // bidirectional
            TEGAM_ADJUSTMENT_MODE_SET_ACK,
            TEGAM_TRENDING_INDICATORS_SET_REQ,          // MSP430 -> PAN1740
            TEGAM_TRENDING_INDICATORS_SET_ACK,
            /*
             *  Interface
             */
            TEGAM_DISPLAY_UPD_REQ = 0x0300,             // MSP430 -> PAN1740 (provides notification)
            TEGAM_DISPLAY_UPD_ACK,
            TEGAM_BUTTONS_SET_REQ,                      // PAN1740 -> MSP430
            TEGAM_BUTTONS_SET_ACK,
            TEGAM_TEMPERATURE_DISPLAY_MODE_SET_REQ,     // bidirectional
            TEGAM_TEMPERATURE_DISPLAY_MODE_SET_ACK,
            TEGAM_SECOND_DISPLAY_STATUS_SET_REQ,        // bidirectional
            TEGAM_SECOND_DISPLAY_STATUS_SET_ACK,
            /*
             *  Data Logging
             */
            TEGAM_INTERVAL_SET_REQ = 0x0400,            // bidirectional
            TEGAM_INTERVAL_SET_ACK,
            TEGAM_READING_COUNT_SET_REQ,                // MSP430 -> PAN1740
            TEGAM_READING_COUNT_SET_ACK,
            TEGAM_LOGGING_MODE_SET_REQ,                 // bidirectional
            TEGAM_LOGGING_MODE_SET_ACK,
            TEGAM_STATISTICS_SET_REQ,                   // MSP430 -> PAN1740
            TEGAM_STATISTICS_SET_ACK,
            TEGAM_END
        };

        public static bool SendDataPacket(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_DATA_PACKET_UPD_REQ;
            ushort valueSize = 12;

            byte[] cmdbuf = new byte[22];
            byte[] cobsbuf = new byte[24];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = value[8];
            cmdbuf[18] = value[9];
            cmdbuf[19] = value[10];
            cmdbuf[20] = value[11];
            cmdbuf[21] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 22, ref cobsbuf);

            cobsbuf[23] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 24);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_DATA_PACKET_UPD_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendChannelReadings(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_CHANNEL_READINGS_SET_REQ;
            ushort valueSize = 8;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 18, ref cobsbuf);

            cobsbuf[19] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 20);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_CHANNEL_READINGS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendTrendReadings(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_TRENDING_INDICATORS_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[19] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 20);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_TRENDING_INDICATORS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendSecondDisplayReadings(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_SECOND_DISPLAY_STATUS_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[19] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 20);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_SECOND_DISPLAY_STATUS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendModelNumber(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_MODEL_NUMBER_SET_REQ;
            ushort valueSize = 10;

            byte[] cmdbuf = new byte[20];
            byte[] cobsbuf = new byte[22];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = value[8];
            cmdbuf[18] = value[9];
            cmdbuf[19] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 20, ref cobsbuf);

            cobsbuf[21] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 22);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_MODEL_NUMBER_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendSerialNumber(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_SERIAL_NUMBER_SET_REQ;
            ushort valueSize = 10;

            byte[] cmdbuf = new byte[20];
            byte[] cobsbuf = new byte[22];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = value[8];
            cmdbuf[18] = value[9];
            cmdbuf[19] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 20, ref cobsbuf);

            cobsbuf[21] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 22);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_SERIAL_NUMBER_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendDeviceTime(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_DEVICE_TIME_SET_REQ;
            ushort valueSize = 4;

            byte[] cmdbuf = new byte[14];
            byte[] cobsbuf = new byte[16];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 14, ref cobsbuf);

            cobsbuf[15] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 16);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_DEVICE_TIME_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendClockMode(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_CLOCK_MODE_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[20];
            byte[] cobsbuf = new byte[22];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_CLOCK_MODE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendButtons(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_BUTTONS_SET_REQ;
            ushort valueSize = 2;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 12, ref cobsbuf);

            cobsbuf[13] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 14);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_BUTTONS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendBatteryVolt(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_BATTERY_VOLTAGE_SET_REQ;
            ushort valueSize = 4;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 14, ref cobsbuf);

            cobsbuf[15] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 16);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_BATTERY_VOLTAGE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendTempDisplayMode(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_TEMPERATURE_DISPLAY_MODE_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_TEMPERATURE_DISPLAY_MODE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendDisplay(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_DISPLAY_UPD_REQ;
            ushort valueSize = 20;

            byte[] cmdbuf = new byte[33];
            byte[] cobsbuf = new byte[33];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = value[8];
            cmdbuf[18] = value[9];
            cmdbuf[19] = value[10];
            cmdbuf[20] = value[11];
            cmdbuf[21] = value[12];
            cmdbuf[22] = value[13];
            cmdbuf[23] = value[14];
            cmdbuf[24] = value[15];
            cmdbuf[25] = value[16];
            cmdbuf[26] = value[17];
            cmdbuf[27] = value[18];
            cmdbuf[28] = value[19];
            cmdbuf[29] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 30, ref cobsbuf);

            cobsbuf[31] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 32);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_DISPLAY_UPD_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendThermocouple(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_THERMOCOUPLE_TYPE_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_THERMOCOUPLE_TYPE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendAdjMode(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_ADJUSTMENT_MODE_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_ADJUSTMENT_MODE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendLogMode(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_LOGGING_MODE_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_LOGGING_MODE_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendInterval(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_INTERVAL_SET_REQ;
            ushort valueSize = 4;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 14, ref cobsbuf);

            cobsbuf[15] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 16);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_INTERVAL_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendReadingCount(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_READING_COUNT_SET_REQ;
            ushort valueSize = 4;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 14, ref cobsbuf);

            cobsbuf[15] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 16);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_READING_COUNT_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendChannelOff(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_CHANNEL_OFFSETS_SET_REQ;
            ushort valueSize = 8;

            byte[] cmdbuf = new byte[18];
            byte[] cobsbuf = new byte[20];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 18, ref cobsbuf);

            cobsbuf[19] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 20);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_CHANNEL_OFFSETS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendStat(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_STATISTICS_SET_REQ;
            ushort valueSize = 20;

            byte[] cmdbuf = new byte[33];
            byte[] cobsbuf = new byte[33];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = value[1];
            cmdbuf[11] = value[2];
            cmdbuf[12] = value[3];
            cmdbuf[13] = value[4];
            cmdbuf[14] = value[5];
            cmdbuf[15] = value[6];
            cmdbuf[16] = value[7];
            cmdbuf[17] = value[8];
            cmdbuf[18] = value[9];
            cmdbuf[19] = value[10];
            cmdbuf[20] = value[11];
            cmdbuf[21] = value[12];
            cmdbuf[22] = value[13];
            cmdbuf[23] = value[14];
            cmdbuf[24] = value[15];
            cmdbuf[25] = value[16];
            cmdbuf[26] = value[17];
            cmdbuf[27] = value[18];
            cmdbuf[28] = value[19];
            cmdbuf[29] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 30, ref cobsbuf);

            cobsbuf[31] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 32);
            }

            if (VERIFY)
            {
                System.Threading.Thread.Sleep(100);

                char[] readBuf = uart.ReadBuffer();
                byte[] decodedBuf = new byte[11];

                // decoded what was read from UART
                COBS.Decode(Encoding.Default.GetBytes(readBuf), 11, ref decodedBuf);

                // reset the UART read buffer after obtaining read data
                uart.ResetReadBuffer();

                // ensure ACK command is valid
                return ValidateACK(decodedBuf, TegamServiceCode_t.TEGAM_STATISTICS_SET_ACK);
            }
            else
            {
                return true;
            }
        }

        public static bool SendBluetoothState(UART uart, byte[] value)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_BLUETOOTH_SET_REQ;
            ushort valueSize = 1;

            byte[] cmdbuf = new byte[11];
            byte[] cobsbuf = new byte[13];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = value[0];
            cmdbuf[10] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 11, ref cobsbuf);

            cobsbuf[12] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 13);
            }

            return true;
        }

        public static bool GetBluetoothState(UART uart)
        {
            ushort serviceCode = (ushort)TegamServiceCode_t.TEGAM_BLUETOOTH_GET_REQ;
            ushort valueSize = 0;

            byte[] cmdbuf = new byte[10];
            byte[] cobsbuf = new byte[12];

            cmdbuf[0] = CMD_MARK_START;
            cmdbuf[1] = CMD_MARK_HEADER & 0x00FF;
            cmdbuf[2] = (CMD_MARK_HEADER & 0xFF00) >> 8;
            cmdbuf[3] = CMD_VERSION_CODE & 0x00FF;
            cmdbuf[4] = (CMD_VERSION_CODE & 0xFF00) >> 8;
            cmdbuf[5] = (byte)(serviceCode & 0x00FF);
            cmdbuf[6] = (byte)((serviceCode & 0xFF00) >> 8);
            cmdbuf[7] = (byte)(valueSize & 0x00FF);
            cmdbuf[8] = (byte)((valueSize & 0xFF00) >> 8);
            cmdbuf[9] = CMD_MARK_END;

            COBS.Encode(cmdbuf, 10, ref cobsbuf);

            cobsbuf[11] = 0;

            if (WRITE)
            {
                uart.Write(cobsbuf, 12);
            }

            return true;
        }

        private static bool ValidateACK(byte[] command, TegamServiceCode_t serviceCode)
        {
            if (command[0] != CMD_MARK_START)
            {
                return false;
            }

            if (((command[2] << 8) + command[1]) != CMD_MARK_HEADER)
            {
                return false;
            }

            if (((command[4] << 8) + command[3]) != CMD_VERSION_CODE)
            {
                return false;
            }

            if (((command[6] << 8) + command[5]) != (ushort) serviceCode)
            {
                return false;
            }

            if (((command[8] << 8) + command[7]) != 0)
            {
                return false;
            }

            if (command[9] != CMD_MARK_END)
            {
                return false;
            }

            return true;
        }

        private static bool ValidateBluetoothGetACK(byte[] command, TegamServiceCode_t serviceCode)
        {
            if (command[0] != CMD_MARK_START)
            {
                return false;
            }

            if (((command[2] << 8) + command[1]) != CMD_MARK_HEADER)
            {
                return false;
            }

            if (((command[4] << 8) + command[3]) != CMD_VERSION_CODE)
            {
                return false;
            }

            if (((command[6] << 8) + command[5]) != (ushort)serviceCode)
            {
                return false;
            }

            if (((command[8] << 8) + command[7]) != 1)
            {
                return false;
            }

            if (command[9] > 3)
            {
                return false;
            }

            if (command[10] != CMD_MARK_END)
            {
                return false;
            }

            return true;
        }

        public static bool Parse(byte[] command, out TegamServiceCode_t serviceCode, out byte[] data)
        {
            serviceCode = TegamServiceCode_t.TEGAM_BASE;
            data = new byte[0];

            int dataSize;

            if (command[0] != CMD_MARK_START)
            {
                return false;
            }

            if (((command[2] << 8) + command[1]) != CMD_MARK_HEADER)
            {
                return false;
            }

            if (((command[4] << 8) + command[3]) != CMD_VERSION_CODE)
            {
                return false;
            }

            serviceCode = (TegamServiceCode_t) ((command[6] << 8) + command[5]);

            dataSize = (command[8] << 8) + command[7];
            data = new byte[dataSize];

            for (int i = 0; i < dataSize; i++)
            {
                data[i] = command[9 + i];
            }

            return true;
        }
    }
}
