
/*


  Author : Zac Kilburn
  This is a simple communications system for comm ports 
  
  The program accepts a number of inputs to say which board to send a packet to
  Comm port must be identified as a define for it to work with your comm port
 */

#include    <windows.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <commdlg.h>
#include    <time.h>
//#include  <windef.h>

#define CommPort "COM1"

#define polynomial 0x8C  //polynomial used to calculate crc
HANDLE hSerial;
COMMTIMEOUTS timeouts;
COMMCONFIG dcbSerialParams;
char packet[20], buffRead[100];
char *buffWrite;
DWORD dwBytesWritten, dwBytesRead;
void setupComm();
void terminalBuffer(char * bufR, char * bufW, int numberWordsR, int numberWordsW);
DWORD readBytes(char * buf, DWORD nread);
DWORD writeBytes(char * buf, DWORD nwrite);
char CRC8(char * data, char len);
int prepGenericBMMPacket();
int prepGenericPDUPacket();
int prepGenericSASPacket();
int prepGenericDDSPacket();
int prepGenericMCSPacket();
int numBytesToWrite;
int prepTBMCSPacket(int t, int b);

int main(int argc, char *argv[]) {
    printf("\n");
    if (argc > 1) {
        int i = 1;
        for (i = 1; i < argc; i++) {
            char * a = argv[i];
            if ((strcmp(a, "MCS") == 0) || (strcmp(a, "mcs") == 0)) {
                printf("Going to do a request for MCS.\n");
                numBytesToWrite = prepGenericMCSPacket();
            } else if ((strcmp(a, "MCS1") == 0) || (strcmp(a, "mcs1") == 0)) {
                printf("Going to do a request for MCS.\n");
                numBytesToWrite = prepTBMCSPacket(1000, 1000);
            } else if ((strcmp(a, "SAS") == 0) || (strcmp(a, "sas") == 0)) {
                printf("Going to do a request for SAS.\n");
                numBytesToWrite = prepGenericSASPacket();
            } else if ((strcmp(a, "PDU") == 0) || (strcmp(a, "pdu") == 0)) {
                printf("Going to do a request for PDU.\n");
                numBytesToWrite = prepGenericPDUPacket();
            } else if ((strcmp(a, "BMM") == 0) || (strcmp(a, "bmm") == 0)) {
                printf("Going to do a request for BMM.\n");
                numBytesToWrite = prepGenericBMMPacket();
            } else if ((strcmp(a, "DDS") == 0) || (strcmp(a, "dds") == 0)) {
                printf("Going to do a request for DDS.\n");
                numBytesToWrite = prepGenericDDSPacket();
            } else {
                printf("No request or a bad request was made for an output board \n");
                printf("Please type any of the following after calling the program:\n\n");
                printf("-MCS\n-SAS\n-PDU\n-BMM\n-DDS\n");
            }
        }
    } else {
        printf("\n\n\n\nNo request was made for an output board \n");
        printf("Please type any of the following after calling the program:\n");
        printf("-MCS\n-SAS\n-PDU\n-BMM\n-DDS\n");

    }
    setupComm();
    int numBytesWritten = writeBytes(packet, numBytesToWrite); //Writebytes from
    int numBytesRead = readBytes(buffRead, 25); //Grab 15 bytes if possible, store in buffRead, return number actually read
    terminalBuffer(buffRead, packet, numBytesRead, numBytesWritten); //Output bytes buffer

    CloseHandle(hSerial);
    return 1;
}

char CRC8(char * data, char len) {
    char crc = 0x00;
    while (len>=0) {
        char extract = *data++;
        char tempI;
        for (tempI = 8; tempI; tempI--) {
            char sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum) {
                crc ^= polynomial;
            }
            extract >>= 1;
        }
        len--;
    }
    return crc;
}

int prepTBMCSPacket(int t, int b) {
    char tHigh, tLow, bHigh, bLow;
    tLow = (t & 0x00FF);
    tHigh = ((t & 0xFF00) >> 8);
    bLow = (b & 0x00FF);
    bHigh = ((b & 0xFF00) >> 8);
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x04;
    packet[3] = 0x01;
    packet[4] = 0x09;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = 0x01;
    packet[9] = tHigh;
    packet[10] = tLow;
    packet[11] = 0x02;
    packet[12] = bHigh;
    packet[13] = bLow;

    int dataBytes=9;
    int k = 0;
    char crcArray[dataBytes];
    for (k = 0; k < dataBytes; k++) {
        crcArray[k] = packet[k + 5];
    }
    packet[14] = CRC8(crcArray, 9);
    return 15;
}

int prepGenericBMMPacket() {
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x05;
    packet[3] = 0x01;
    packet[4] = 0x03;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = CRC8(packet, 3);
    ; //-------------
    return 9;
}

int prepGenericPDUPacket() {
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x05;
    packet[3] = 0x01;
    packet[4] = 0x03;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = CRC8(packet, 3); //-------------
    return 9;
}

int prepGenericSASPacket() {
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x02;
    packet[3] = 0x01;
    packet[4] = 0x03;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = CRC8(packet, 3); //-------------
    return 9;
}

int prepGenericDDSPacket() {
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x03;
    packet[3] = 0x01;
    packet[4] = 0x03;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = CRC8(packet, 3); //-------------
    return 9;
}

int prepGenericMCSPacket() {
    packet[0] = 0x06;
    packet[1] = 0x85;
    packet[2] = 0x04;
    packet[3] = 0x01;
    packet[4] = 0x03;
    packet[5] = 0x00;
    packet[6] = 0x01;
    packet[7] = 0x00;
    packet[8] = 0xC4;
    return 9;
}

void setupComm() {
    hSerial = CreateFile(CommPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf(" serial port does not exist \n");
        }
        printf(" some other error occured. Inform user.\n");
    }
    //DCB    dcbSerialParams ;
    //GetCommState( hSerial, &dcbSerialParams.dcb);
    if (!GetCommState(hSerial, &dcbSerialParams.dcb)) {
        printf("error getting state \n");
    }
    dcbSerialParams.dcb.DCBlength = sizeof (dcbSerialParams.dcb);
    dcbSerialParams.dcb.BaudRate = CBR_38400;
    dcbSerialParams.dcb.ByteSize = 8;
    dcbSerialParams.dcb.StopBits = ONESTOPBIT;
    dcbSerialParams.dcb.Parity = NOPARITY;
    dcbSerialParams.dcb.fBinary = TRUE;
    dcbSerialParams.dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcbSerialParams.dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcbSerialParams.dcb.fOutxCtsFlow = FALSE;
    dcbSerialParams.dcb.fOutxDsrFlow = FALSE;
    dcbSerialParams.dcb.fDsrSensitivity = FALSE;
    dcbSerialParams.dcb.fAbortOnError = TRUE;

    if (!SetCommState(hSerial, &dcbSerialParams.dcb)) {
        printf(" error setting serial port state \n");
    }

    GetCommTimeouts(hSerial, &timeouts);
    //COMMTIMEOUTS timeouts = {0};

    timeouts.ReadIntervalTimeout = 100;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 20;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("error setting port state \n");
    }
}

DWORD writeBytes(char * buf, DWORD nwrite) {
    //****************Write Operation*********************//
    DWORD bytesWritten = 0;

    if (!WriteFile(hSerial, buf, nwrite, &bytesWritten, NULL)) {
        printf("error writing to output buffer \n");
    }
    return bytesWritten;

}

DWORD readBytes(char * buf, DWORD nread) {
    //***************Read Operation******************//
    DWORD bytesRead = 0;

    if (!ReadFile(hSerial, buf, nread, &bytesRead, NULL)) {
        printf("error reading from input buffer \n");
    }
    return bytesRead;
}

void terminalBuffer(char * bufR, char * bufW, int numberWordsR, int numberWordsW) {
    int i;
    printf("\n# bytes written: %d \n", numberWordsW);
    for (i = 0; i < numberWordsW; i++) {
        printf("%hX\n", bufW[i]&0x00FF);
    }
    printf("\n# bytes read: %d \n", numberWordsR);
    for (i = 0; i < numberWordsR; i++) {
        printf("%hX\n", bufR[i]&0x00FF);
    }
}
