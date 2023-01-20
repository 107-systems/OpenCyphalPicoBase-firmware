/*
 * Software for the auxiliary controller for the L3X-Z Hexapod
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "DigitalOutControl.h"

#include <Arduino.h>

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalOutControl::DigitalOutControl(int const out_0_pin, int const out_1_pin, Node & node_hdl)
: _out_0_pin{out_0_pin}
, _out_1_pin{out_1_pin}
{
  _out_0_sub = node_hdl.create_subscription<TOpenCyphalDigitalOut_0>(
    ID_OUTPUT0,
    CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC,
    [this](TOpenCyphalDigitalOut_0 const & msg)
    {
      if(msg.data.value)
        digitalWrite(_out_0_pin, HIGH);
      else
        digitalWrite(_out_0_pin, LOW);
    });

  _out_1_sub = node_hdl.create_subscription<TOpenCyphalDigitalOut_1>(
    ID_OUTPUT1,
    CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC,
    [this](TOpenCyphalDigitalOut_1 const & msg)
    {
      if(msg.data.value)
        digitalWrite(_out_1_pin, HIGH);
      else
        digitalWrite(_out_1_pin, LOW);
    });
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalOutControl::begin()
{
  pinMode(_out_0_pin, OUTPUT);
  pinMode(_out_1_pin, OUTPUT);

  digitalWrite(_out_0_pin, LOW);
  digitalWrite(_out_1_pin, LOW);
}