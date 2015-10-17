using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace TegamHost
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private UART _uart;
        int TimerIsOn = 0;

        public MainWindow()
        {
            InitializeComponent();

            string[] portNames = UART.GetPortNames();

            if (portNames.Length > 0)
            {
                ComboBoxCOMPort.ItemsSource = new List<string>(portNames);
            }
        }

        private void ButtonConnect_Click(object sender, RoutedEventArgs e)
        {
            if (ComboBoxCOMPort.SelectedItem != null)
            {
                _uart = new UART((string)ComboBoxCOMPort.SelectedValue);
            }


            if (_uart.PortOpen())
            {
                LabelState.Content = "Connected";
                _uart.StartReading();
            }
        }

        private void ButtonDisconnect_Click(object sender, RoutedEventArgs e)
        {
            if (_uart.PortOpen())
            {
                _uart.StopReading();
                _uart.Disconnect();
                LabelState.Content = "Disconnected";
            }
        }

        private void ButtonSendDataPacket_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[12];
            byte[] floatData;
            int hours, minutes, seconds;
            float value1, value2;

            if (!Single.TryParse(TextBoxTemp1.Text, out value1))
            {
                MessageBox.Show("Could not parse temperature 1 value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxTemp2.Text, out value2))
            {
                MessageBox.Show("Could not parse temperature 2 value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // upper byte not used
            data[0] = 0;

            hours = DateTime.Now.Hour;
            minutes = DateTime.Now.Minute;
            seconds = DateTime.Now.Second;

            // set time
            data[1] = (byte)hours;
            data[2] = (byte)minutes;
            data[3] = (byte)seconds;

            // set floats
            floatData = BitConverter.GetBytes(value1);
            data[4] = floatData[0];
            data[5] = floatData[1];
            data[6] = floatData[2];
            data[7] = floatData[3];
            floatData = BitConverter.GetBytes(value2);
            data[8] = floatData[0];
            data[9] = floatData[1];
            data[10] = floatData[2];
            data[11] = floatData[3];

            if (!CommandHost.SendDataPacket(_uart, data))
            {
                MessageBox.Show("Transmission error sending data packet.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendChannelReadings_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[8];
            byte[] floatData;
            float value1, value2;

            if (!Single.TryParse(TextBoxTemp1.Text, out value1))
            {
                MessageBox.Show("Could not parse temperature 1 value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxTemp2.Text, out value2))
            {
                MessageBox.Show("Could not parse temperature 2 value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // set floats
            floatData = BitConverter.GetBytes(value1);
            data[0] = floatData[0];
            data[1] = floatData[1];
            data[2] = floatData[2];
            data[3] = floatData[3];
            floatData = BitConverter.GetBytes(value2);
            data[4] = floatData[0];
            data[5] = floatData[1];
            data[6] = floatData[2];
            data[7] = floatData[3];

            if (!CommandHost.SendChannelReadings(_uart, data))
            {
                MessageBox.Show("Transmission error sending channel readings.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendModelNumber_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxModelNumber.Text.Length > 10)
            {
                MessageBox.Show("Model number too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[10];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxModelNumber.Text);
            for (int i = 0; i < 10; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendModelNumber(_uart, data))
            {
                MessageBox.Show("Transmission error sending model number value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendTrend_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[1];

            if (TextBoxTrend.Text.Length > 1)
            {
                MessageBox.Show("Trend number too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxTrend.Text);
            data[0] = value[0];

            if (!CommandHost.SendTrendReadings(_uart, data))
            {
                MessageBox.Show("Transmission error sending trend readings.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendSecondDisplay_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[1];

            if (TextBoxSecondDisplay.Text.Length > 1)
            {
                MessageBox.Show("Second display number too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxSecondDisplay.Text);
            data[0] = value[0];

            if (!CommandHost.SendSecondDisplayReadings(_uart, data))
            {
                MessageBox.Show("Transmission error sending second display readings.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }

        private void ButtonSendSerialNumber_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxSerialNumber.Text.Length > 10)
            {
                MessageBox.Show("Serial number too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[10];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxSerialNumber.Text);
            for (int i = 0; i < 10; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendSerialNumber(_uart, data))
            {
                MessageBox.Show("Transmission error sending serial number value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendDeviceTime_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxDeviceTime.Text.Length > 8)
            {
                MessageBox.Show("Time number too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[4];
            byte[] value = Utilities.StringToByteArray(TextBoxDeviceTime.Text);
            for (int i = 0; i < 4; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendDeviceTime(_uart, data))
            {
                MessageBox.Show("Transmission error sending time value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendClockMode_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxClockMode.Text.Length > 1)
            {
                MessageBox.Show("Clock mode value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxClockMode.Text);
            data[0] = value[0];

            if (!CommandHost.SendClockMode(_uart, data))
            {
                MessageBox.Show("Transmission error sending clock mode value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendButtons_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxButtons.Text.Length > 2)
            {
                MessageBox.Show("Button value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[2];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxButtons.Text);
            for (int i = 0; i < 2; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendButtons(_uart, data))
            {
                MessageBox.Show("Transmission error sending button value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendDisplay_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxDisplay.Text.Length > 40)
            {
                MessageBox.Show("Display value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[20];
            byte[] value = Utilities.StringToByteArray(TextBoxDisplay.Text); //System.Text.Encoding.UTF8.GetBytes(TextBoxDisplay.Text);
            for (int i = 0; i < 20; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendDisplay(_uart, data))
            {
                MessageBox.Show("Transmission error sending display value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendBattVolt_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[4];
            byte[] floatData;
            float value1;

            if (!Single.TryParse(TextBoxBatteryVoltage.Text, out value1))
            {
                MessageBox.Show("Could not parse battery value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // set floats
            floatData = BitConverter.GetBytes(value1);
            data[0] = floatData[0];
            data[1] = floatData[1];
            data[2] = floatData[2];
            data[3] = floatData[3];

            if (!CommandHost.SendBatteryVolt(_uart, data))
            {
                MessageBox.Show("Transmission error sending battery readings.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }

        private void ButtonSendTempDisplayMode_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxClockMode.Text.Length > 1)
            {
                MessageBox.Show("TDM value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxClockMode.Text);
            data[0] = value[0];

            if (!CommandHost.SendTempDisplayMode(_uart, data))
            {
                MessageBox.Show("Transmission error sending TDM value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendChannelOff_Click(object sender, RoutedEventArgs e)
        {
            byte[] data = new byte[8];
            byte[] floatData;
            float value1, value2;

            if (!Single.TryParse(TextBoxCH1.Text, out value1))
            {
                MessageBox.Show("Could not parse Channel 1 offset value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxCH2.Text, out value2))
            {
                MessageBox.Show("Could not parse Channel 2 offset value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // set floats
            floatData = BitConverter.GetBytes(value1);
            data[0] = floatData[0];
            data[1] = floatData[1];
            data[2] = floatData[2];
            data[3] = floatData[3];
            floatData = BitConverter.GetBytes(value2);
            data[4] = floatData[0];
            data[5] = floatData[1];
            data[6] = floatData[2];
            data[7] = floatData[3];

            if (!CommandHost.SendChannelOff(_uart, data))
            {
                MessageBox.Show("Transmission error sending channel offset readings.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendTherm_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxThermocouple.Text.Length > 1)
            {
                MessageBox.Show("Thermocouple value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxThermocouple.Text);
            data[0] = value[0];

            if (!CommandHost.SendThermocouple(_uart, data))
            {
                MessageBox.Show("Transmission error sending Thermocouple value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendAdjMode_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxAdjMode.Text.Length > 1)
            {
                MessageBox.Show("Adjustment mode value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxAdjMode.Text);
            data[0] = value[0];

            if (!CommandHost.SendAdjMode(_uart, data))
            {
                MessageBox.Show("Transmission error sending adjustment mode value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendInterval_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxInterval.Text.Length > 4)
            {
                MessageBox.Show("Interval value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[4];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxInterval.Text);
            for (int i = 0; i < 4; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendInterval(_uart, data))
            {
                MessageBox.Show("Transmission error sending interval value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendReadingCount_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxReadingCount.Text.Length > 4)
            {
                MessageBox.Show("Reading value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[4];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxReadingCount.Text);
            for (int i = 0; i < 4; i++)
            {
                if (i < value.Length)
                {
                    data[i] = value[i];
                }
                else
                {
                    data[i] = 0;
                }
            }

            if (!CommandHost.SendReadingCount(_uart, data))
            {
                MessageBox.Show("Transmission error sending reading count value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendLogMode_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxLoggingMode.Text.Length > 1)
            {
                MessageBox.Show("Logging mode value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxLoggingMode.Text);
            data[0] = value[0];

            if (!CommandHost.SendLogMode(_uart, data))
            {
                MessageBox.Show("Transmission error sending logging mode value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSendStat_Click(object sender, RoutedEventArgs e)
        {

            byte[] data = new byte[20];
            byte[] floatData;
            float value1, value2, value3, value4, value5;

            if (!Single.TryParse(TextBoxMin.Text, out value1))
            {
                MessageBox.Show("Could not parse minimum value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxMax.Text, out value2))
            {
                MessageBox.Show("Could not parse maximum value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxAvg.Text, out value3))
            {
                MessageBox.Show("Could not parse average value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxRange.Text, out value4))
            {
                MessageBox.Show("Could not parse range value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!Single.TryParse(TextBoxSTD.Text, out value5))
            {
                MessageBox.Show("Could not parse standard deviation value.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // set floats
            floatData = BitConverter.GetBytes(value1);
            data[0] = floatData[0];
            data[1] = floatData[1];
            data[2] = floatData[2];
            data[3] = floatData[3];
            floatData = BitConverter.GetBytes(value2);
            data[4] = floatData[0];
            data[5] = floatData[1];
            data[6] = floatData[2];
            data[7] = floatData[3];
            floatData = BitConverter.GetBytes(value3);
            data[8] = floatData[0];
            data[9] = floatData[1];
            data[10] = floatData[2];
            data[11] = floatData[3];
            floatData = BitConverter.GetBytes(value4);
            data[12] = floatData[0];
            data[13] = floatData[1];
            data[14] = floatData[2];
            data[15] = floatData[3];
            floatData = BitConverter.GetBytes(value5);
            data[16] = floatData[0];
            data[17] = floatData[1];
            data[18] = floatData[2];
            data[19] = floatData[3];

            if (!CommandHost.SendStat(_uart, data))
            {
                MessageBox.Show("Transmission error sending data packet.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
        Random rnd1 = new Random();
        Random rnd2 = new Random();
        int Max = 5;
        int Min = 0;

        private void ButtonTimer_Click(object sender, RoutedEventArgs e)
        {
            int timervalue = 0;
            
            if (TextBoxTimerInterval.Text.Length > 4)
            {
                MessageBox.Show("Timer value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (TextBoxRandMin.Text.Length > 3)
            {
                MessageBox.Show("Random minimum value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (TextBoxRandMax.Text.Length > 3)
            {
                MessageBox.Show("Random maximum value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            timervalue = int.Parse(TextBoxTimerInterval.Text);
            Max = int.Parse(TextBoxRandMax.Text);
            Min = int.Parse(TextBoxRandMin.Text);

            if (TimerIsOn == 0)
            {
                timer.Interval = new TimeSpan(0, 0, 0, 0, timervalue);
                timer.Tick += new EventHandler(Each_Tick);
                timer.Start();
                TimerIsOn = 1;
                ButtonTimer.Content = "Stop";
            }
            else
            {
                timer.Stop();
                TimerIsOn = 0;
                ButtonTimer.Content = "Start";        
            }

            byte[] data = new byte[1];
            byte[] value = System.Text.Encoding.UTF8.GetBytes(TextBoxLoggingMode.Text);
            data[0] = value[0];
        }

        public void Each_Tick(object o, EventArgs sender)
        {
            int temp1 = rnd1.Next(Min,Max);
            int temp2 = rnd2.Next(Min,Max);

            byte[] data = new byte[12];
            byte[] floatData;
            int hours, minutes, seconds;

            // upper byte not used
            data[0] = 0;

            hours = DateTime.Now.Hour;
            minutes = DateTime.Now.Minute;
            seconds = DateTime.Now.Second;

            // set time
            data[1] = (byte)hours;
            data[2] = (byte)minutes;
            data[3] = (byte)seconds;

            // set floats
            floatData = BitConverter.GetBytes(temp1);
            data[4] = floatData[0];
            data[5] = floatData[1];
            data[6] = floatData[2];
            data[7] = floatData[3];
            floatData = BitConverter.GetBytes(temp2);
            data[8] = floatData[0];
            data[9] = floatData[1];
            data[10] = floatData[2];
            data[11] = floatData[3];

            if (!CommandHost.SendDataPacket(_uart, data))
            {
                MessageBox.Show("Transmission error sending data packet.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonSetBluetoothState_Click(object sender, RoutedEventArgs e)
        {
            if (TextBoxBluetoothState.Text.Length > 2)
            {
                MessageBox.Show("Bluetooth state value too lengthy.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] value = Utilities.StringToByteArray(TextBoxBluetoothState.Text);

            if (!CommandHost.SendBluetoothState(_uart, value))
            {
                MessageBox.Show("Transmission error sending Bluetooth state.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ButtonGetBluetoothState_Click(object sender, RoutedEventArgs e)
        {
            CommandHost.GetBluetoothState(_uart);
        }

    }
}
