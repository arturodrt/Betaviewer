/** @file      serialComms.cpp
 *  @brief     Source file file for Serial Communication functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/29
 */

 /* Includes ---------------------------------------------------------------------------------- */
#include "serialComms.hpp"
#include "circularBuffer.hpp"
/* Private define ---------------------------------------------------------------------------- */
#define NUMBERS_TO_RECEIVE              (64)
/* Define matrix size */
/* Private typedef --------------------------------------------------------------------------- */
/* Private macro ----------------------------------------------------------------------------- */
/* Private enum ------------------------------------------------------------------------------ */
/* Private struct ---------------------------------------------------------------------------- */
/* Private variables ------------------------------------------------------------------------- */
HANDLE hSerial;
/* String to store received data */
std::string g_strReceivedData;
CircularBuffer<char> circularBuffer(192);

/* Private function prototypes --------------------------------------------------------------- */

bool openCOMPort(void)
{
    /* Your code to open the COM port goes here */

    /* Serial port setup */
    hSerial = CreateFileW(
        L"COM3",               /* COM port name (L prefix for wide character string) */
        GENERIC_READ,          /* Read access */
        0,                     /* No sharing (exclusive access) */
        NULL,                  /* No security attributes */
        OPEN_EXISTING,         /* Opens the existing port */
        0,                     /* No overlapped I/O */
        NULL                   /* No template file */
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port\n";
        return 1;
    }
    else {
        std::cout << "Serial port opened successfully\n";
    }

    /* Configure serial port settings */
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state\n";
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_115200;  /* Set baud rate to 115200 */
    dcbSerialParams.ByteSize = 8;           /* 8 data bits */
    dcbSerialParams.StopBits = ONESTOPBIT;  /* 1 stop bit */
    dcbSerialParams.Parity = NOPARITY;      /* No parity */
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port state\n";
        CloseHandle(hSerial);
        return 1;
    }

    return true;
}

void parseSerialData(const std::string& strReceivedData) {
    std::stringstream ss(strReceivedData);
    for (int i = 0; i < NUMBERS_TO_RECEIVE; ++i) {
        std::string value_str;
        std::getline(ss, value_str, ',');
    }
}

ePhosError_t eReadSerialData(bool* boUpdateMatrix, std::string* strReceivedData)
{
    char buffer[64];
    static std::stringstream ss;
    static bool startFlag = false;
    char strChar;
    static uint8_t ucCounter = 0;
    DWORD bytesRead;

    if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
    {
        // Push data into circular buffer
        for (DWORD i = 0; i < bytesRead; ++i)
        {
            circularBuffer.push(buffer[i]);
        }
    }
    else
    {
        return eReadError;
    }

    while (!startFlag && !circularBuffer.isEmpty())
    {
        strChar = circularBuffer.pop();
        if (strChar == '+')
        {
            startFlag = true;
        }
    }

    if (startFlag)
    {
        while (ucCounter < NUMBERS_TO_RECEIVE && !(circularBuffer.isEmpty()))
        {
            strChar = circularBuffer.pop();
            if (strChar == ',')
            {
                ucCounter++;
            }
            g_strReceivedData += strChar;
        }

        if (ucCounter == NUMBERS_TO_RECEIVE)
        {
            parseSerialData(g_strReceivedData);
            *strReceivedData = g_strReceivedData;
            g_strReceivedData.clear(); // Clear received data buffer
            startFlag = false; // Reset start flag
            ucCounter = 0;
        }
    }

    *boUpdateMatrix = startFlag;

    return eSuccess;
}