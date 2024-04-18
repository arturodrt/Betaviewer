/** @file      serialComms.hpp
 *  @brief     Header file for Serial Communication functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/29
 */

 /* Header guard ------------------------------------------------------------------------------ */
#ifndef SERIALCOMMS_H_
#define SERIALCOMMS_H_
/* Includes ---------------------------------------------------------------------------------- */
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "phoslibs.hpp"

/* Define ------------------------------------------------------------------------------------ */
/* Exported Macro ---------------------------------------------------------------------------- */
/* Exported types ---------------------------------------------------------------------------- */
/* Exported enums ---------------------------------------------------------------------------- */
/* Exported struct --------------------------------------------------------------------------- */
/* Global variables -------------------------------------------------------------------------- */
/* Exported function prototypes -------------------------------------------------------------- */

/**
 * @brief Opens a COM port for communication.
 *
 * This function attempts to open a COM port for communication.
 * The COM port name and access mode are specified internally.
 * It configures the serial port settings with default values:
 * - Baud rate: 115200
 * - Data bits: 8
 * - Stop bits: 1
 * - Parity: None
 *
 * @return True if the COM port is opened successfully, false otherwise.
 */
bool openCOMPort( void );

/**
 * @brief Parses received serial data into an array of integers.
 *
 * This function parses the received serial data, represented as a string,
 * into an array of integers. The serial data is expected to contain a series
 * of comma-separated integer values. The function extracts each value from
 * the input string using stringstream and stores them in the 'data' array.
 *
 * @param g_strReceivedData The string containing the received serial data.
 *
 * @note This function assumes that the received data format is consistent
 *       and contains exactly NUMBERS_TO_RECEIVE comma-separated integer values.
 *
 * @warning If the input string does not contain enough values, or if the values
 *          cannot be parsed as integers, the behavior is undefined.
 */
void parseSerialData(const std::string& receivedData);

/**
 * @brief Reads serial data from the serial port.
 *
 * This function reads serial data from the serial port and processes it.
 * The received data is expected to be in a specific format where each message
 * starts with a '\r\n' sequence and ends with another '\r\n' sequence. The
 * function parses each received message and updates the provided string with
 * the parsed data.
 *
 * @param boUpdateMatrix Pointer to a boolean indicating whether the matrix
 *                       needs to be updated based on the received data.
 * @param strReceivedData Pointer to a string where the received data will be
 *                        stored after processing.
 *
 * @return An ePhosError_t value indicating the outcome of the operation:
 *         - eSuccess: Operation completed successfully.
 *         - eReadError: An error occurred while reading serial data.
 *
 */ 
ePhosError_t eReadSerialData( bool *boUpdateMatrix, std::string *strReceivedData );


#endif /* SERIALCOMMS_H_ */

