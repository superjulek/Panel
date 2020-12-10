/*
 * pin_master.h
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#ifndef LIB_PIN_MASTER_H_
#define LIB_PIN_MASTER_H_

#include "pins.h"
#include "general.h"

typedef struct pin_master_t pin_master_t;

/**
 * Controller of all inputs and outputs of board.
 * Controlls both internal IO and expanders.
 */
struct pin_master_t
{
    /**
     * Reload all inputs
     */
    void (*reload_inputs)(pin_master_t *public);

    /**
     * Reload all outputs
     */
    void (*reload_outputs)(pin_master_t *public);
};

/**
 * Constructor of pin master instance.
 * @param x         test
 * @return          pointer to created instance
 * @note            should be used only once
 */
pin_master_t *pin_master_create();

#endif /* LIB_PIN_MASTER_H_ */
