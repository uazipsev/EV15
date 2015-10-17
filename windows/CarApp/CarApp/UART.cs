using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;
using System.Windows;

namespace TegamHost
{
    /// <summary>
    /// UART controller for serial communication.
    /// </summary>
    class UART
    {
        public const int UART_READ_BUFFER_SIZE = 513;

        static bool _continue;
        static SerialPort _serialPort;
        Thread _readThread;
        char[] _readBuffer;
        int _readBytes;

        public UART(string portName)
        {
            ResetReadBuffer();

            _readThread = new Thread(Read);

            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();

            // Set the correct settings
            _serialPort.PortName = portName;
            _serialPort.BaudRate = (int) 115200;
            _serialPort.Parity = Parity.None;
            _serialPort.DataBits = 8;
            _serialPort.StopBits = StopBits.One;
            _serialPort.Handshake = Handshake.None;

            // Set the read/write timeouts
            _serialPort.ReadTimeout = 500;
            _serialPort.WriteTimeout = 500;

            _serialPort.Encoding = Encoding.Default;

            _serialPort.Open();
        }

        public void Disconnect()
        {
            _serialPort.Close();
        }

        public static string[] GetPortNames()
        {
            // Get a list of serial port names. 
            string[] ports = SerialPort.GetPortNames();

            return ports;
        }

        public bool PortOpen()
        {
            return _serialPort != null && _serialPort.IsOpen;
        }

        public void StartReading()
        {
            _continue = true;
            _readThread.Start();
        }

        public void StopReading()
        {
            _continue = false;
        }

        private void Read()
        {
            while (_continue)
            {
                try
                {
                    int bytesToRead = _serialPort.BytesToRead;

                    if (bytesToRead > 0)
                    {
                        bytesToRead = bytesToRead + _readBytes < UART_READ_BUFFER_SIZE ? bytesToRead : UART_READ_BUFFER_SIZE - _readBytes;
                        _serialPort.Read(_readBuffer, _readBytes, bytesToRead);

                        _readBytes += bytesToRead;

                        if (_readBuffer[_readBytes - 1] == '\r')
                        {
                            CommandHost.TegamServiceCode_t serviceCode;
                            byte[] data;
                            byte[] decodedBuf = new byte[_readBytes + 1];

                            // decoded what was read from UART
                            COBS.Decode(Encoding.Default.GetBytes(_readBuffer), (ushort)(_readBytes + 1), ref decodedBuf);

                            if (CommandHost.Parse(decodedBuf, out serviceCode, out data))
                            {
                                switch (serviceCode)
                                {
                                    case CommandHost.TegamServiceCode_t.TEGAM_ERROR:
                                        MessageBox.Show("Received an error from Tegam 919!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                                        break;
                                    case CommandHost.TegamServiceCode_t.TEGAM_BLUETOOTH_GET_ACK:
                                        MessageBox.Show("Current Bluetooth state: " + data[0]);
                                        break;
                                    case CommandHost.TegamServiceCode_t.TEGAM_MODEL_NUMBER_SET_ACK:
                                        //MessageBox.Show("Received ACK for model number set.");
                                        break;
                                    case CommandHost.TegamServiceCode_t.TEGAM_DATA_PACKET_UPD_ACK:
                                        //MessageBox.Show("Received ACK for data packet update.");
                                        break;
                                    case CommandHost.TegamServiceCode_t.TEGAM_SEND_NEXT_READING_SET_REQ:
                                        MessageBox.Show("Received request to send next reading. Value: " + data[0]);
                                        break;
                                    case CommandHost.TegamServiceCode_t.TEGAM_CHANNEL_READINGS_SET_ACK:
                                        //MessageBox.Show("Received ACK for channel readings set.");
                                        break;
                                }
                            }

                            ResetReadBuffer();
                        }
                    }
                }
                catch (TimeoutException) { }
            }
        }

        public char[] ReadBuffer()
        {
            return _readBuffer;
        }

        public void ResetReadBuffer()
        {
            _readBuffer = new char[UART_READ_BUFFER_SIZE];
            _readBytes = 0;
        }

        public void Write(String sbuffer)
        {
            if (PortOpen())
            {
                _serialPort.WriteLine(sbuffer);
            }
        }

        public void Write(byte[] buffer, int count)
        {
            if (PortOpen())
            {
                _serialPort.Write(buffer, 0, count);
            }
        }
    }
}
