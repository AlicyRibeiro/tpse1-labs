#ifndef _PAD_CONTROL_REGISTERS_
#define _PAD_CONTROL_REGISTERS_

#include "CONTROL_MODULE_Registers.h"

/**
 * @brief MUXMODES for pin pads
 **/
typedef enum{
    MODE_0 = 0,
    MODE_1 = 1,
    MODE_2 = 2,
    MODE_3 = 3,
    MODE_4 = 4,
    MODE_5 = 5,
    MODE_6 = 6,
    MODE_7 = 7
}muxmode;

/**
 * @fn void PAD_setMode(CONTROL_MODULE conf_module_pin, pinmode_t mode)
 * @brief            Set a mode to a control module.
 * @param[in] conf_module_pin Module to set the mode to.
 * @param[in] mode   Mode to set the module to.
 * @return           void
 **/
void padControlSetMode(CONTROL_MODULE conf_module_pin, muxmode mode);

/**
 * @fn muxmode PAD_getMode(CONTROL_MODULE conf_module_pin)
 * @brief            Get the mode of a module.
 * @param[in] conf_module_pin Module to get the mode from;
 * @return           mode of this control module
 **/
muxmode padControlGetMode(CONTROL_MODULE conf_module_pin);

#endif