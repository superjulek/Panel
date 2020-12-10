/*
 * general.h
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#ifndef LIB_GENERAL_H_
#define LIB_GENERAL_H_

//#define uint8_t unsigned char
#define bool uint8_t
#define TRUE 1
#define FALSE 0

/* I2C addresses, already left-shifted */
#define MCP_ADDRESS_1 0b01000000// Lights 1
#define MCP_ADDRESS_2 0b01000010 // Lights 2
#define MCP_ADDRESS_3 0b01000100 // Switches 1
#define MCP_ADDRESS_4 0b01000110 // Switches 2

#define MAX11616_ADDRESS 0b01101010

#define I2C_TIMEOUT 1


#endif /* LIB_GENERAL_H_ */
