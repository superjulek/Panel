/*
 * general.hpp
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#pragma once

/* I2C addresses, already left-shifted */
#define MCP_ADDRESS_1 0b01000000// Lights 1
#define MCP_ADDRESS_2 0b01000010 // Lights 2
#define MCP_ADDRESS_3 0b01000100 // Switches 1
#define MCP_ADDRESS_4 0b01000110 // Switches 2

#define MAX11616_ADDRESS 0b01101010

#define I2C_TIMEOUT 1
