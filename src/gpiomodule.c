/**
 * @file
 *  @brief Contains all wrapper functions for Python.
 *
 *  This is is part of https://github.com/alanbarr/TODO
 *  a Python Wrapper for: https://github.com/alanbarr/RaspberryPi-GPIO; a C 
 *  library which allows control of the Raspberry PI's GPIO pins.
 *  Copyright (C) Alan Barr 2012
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>. */


#include <Python.h>
#include "rpiGpio.h"

/* Creating an Error for the module */
static PyObject * gpyoError;

/******************************************************************************/
PyDoc_STRVAR(pinFuncionDoc, "Allows a GPIO pin to be set as input or output.\n"
"The first argument should be the pin number as an integer.\n"
"The second argument should be the desired function: the string \"input\" or "
"\"output.");

static PyObject * pinFunction(PyObject * self, PyObject * args)
{
    int pinNumber;
    const char * functionString;
    eFunction function;
    errStatus gpioRtn;

    if (!PyArg_ParseTuple(args, "is", &pinNumber, &functionString))
    {
        return NULL;
    }

    if (strcmp("input", functionString) == 0)
    {
        function = input;
    }

    else if (strcmp("output", functionString) == 0)
    {
        function = output;
    }
    
    else 
    {
        PyErr_SetString(gpyoError, "Valid arguments are \"input\" or \"output\"");
        return NULL;
    }

    if (OK != (gpioRtn = gpioSetFunction(pinNumber, function)))
    {
        PyErr_Format(gpyoError, "gpioSetFunction failed. %s",
                     gpioErrToString(gpioRtn));
        return NULL;

    }

    Py_RETURN_NONE;

}

/******************************************************************************/
PyDoc_STRVAR(pinStateDoc, "Allows a previously configured output pin to be set.\n"
"The first argument is the pin number as an integer.\n"
"The second argument is desired state to set the pin: the string \"low\" or "
"\"high\".");

static PyObject * pinState(PyObject * self, PyObject * args)
{
    int pinNumber;
    const char * stateString = NULL;
    eState state;
    errStatus gpioRtn;

    if (!PyArg_ParseTuple(args, "is", &pinNumber, &stateString))
    {
        return NULL;
    }

    if (strcmp("low", stateString) == 0)
    {
        state = low;
    }

    else if (strcmp("high", stateString) == 0)
    {
        state = high;
    }
    
    else 
    {
        PyErr_SetString(gpyoError, "Valid arguments are \"high\" or \"low\"");
        return NULL;
    }

    if (OK != (gpioRtn = gpioSetPin(pinNumber, state)))
    {
        PyErr_Format(gpyoError, "gpioSetPin failed. %s",
                     gpioErrToString(gpioRtn));
        return NULL;
    }

    Py_RETURN_NONE;
}


/******************************************************************************/
PyDoc_STRVAR(pinReadDoc, "Reads the state of a pin.\n"
"The first argument is the integer pin number.\n"
"The functions returns 1 if the pin is high or 0 if the pin is low.");
                      
static PyObject * pinRead(PyObject * self, PyObject * args)
{
    int pinNumber;
    eState state;
    int rtn;

    if (!PyArg_ParseTuple(args, "i", &pinNumber))
    {
        return NULL;
    }

    if (OK != (rtn = gpioReadPin(pinNumber, &state)))
    {
        return NULL;
    }

    return PyLong_FromLong(state);
}


/******************************************************************************/
PyDoc_STRVAR(pinResistorDoc, "Allows an internal resistor to be configured.\n"
"The first argument is the integer pin number.\n"
"The second argument is the desired resistor configuration as a string - may be "
"\"pullup\", \"pulldown\" or \"disable\".");

static PyObject * pinResistor(PyObject * self, PyObject * args)
{
    int pinNumber;
    const char * resistorString = NULL;
    eResistor resistor;
    errStatus gpioRtn;

    if (!PyArg_ParseTuple(args, "is", &pinNumber, &resistorString))
    {
        return NULL;
    }

    if (strcmp("pullup", resistorString) == 0)
    {
        resistor = pullup;
    }

    else if (strcmp("pulldown", resistorString) == 0)
    {
        resistor = pulldown;
    }

    else if (strcmp("disable", resistorString) == 0)
    {
        resistor = pullDisable;
    }
    
    else 
    {
        PyErr_SetString(gpyoError, "Valid arguments are \"pullup\", "
                                   "\"pulldown\" or \"disable\"");
        return NULL;
    }

    if (OK != (gpioRtn = gpioSetPullResistor(pinNumber, resistor)))
    {
        PyErr_Format(gpyoError, "gpioSetPullResistor failed. %s",
                     gpioErrToString(gpioRtn));
        return NULL;
    }

    Py_RETURN_NONE;
}


/******************************************************************************/
static PyMethodDef gpioFunctions[] = {  
    {"pin_function",  (PyCFunction)pinFunction, METH_VARARGS, pinFuncionDoc},
    {"pin_state",     (PyCFunction)pinState,    METH_VARARGS, pinStateDoc},
    {"pin_read",      (PyCFunction)pinRead,     METH_VARARGS, pinReadDoc},
    {"pin_resistor",  (PyCFunction)pinResistor, METH_VARARGS, pinResistorDoc},
    {NULL, NULL, 0, NULL}
};


PyDoc_STRVAR(gpioDoc, 
"A python wrapper to offer direct control of the Raspberry Pi's GPIO pins.");

static struct PyModuleDef gpiomodule = {
   PyModuleDef_HEAD_INIT,
   "gpyo",   
   gpioDoc,
    /* size of per-interpreter state of the module,
       or -1 if the module keeps state in global variables. */
   -1,     
   gpioFunctions
};

PyMODINIT_FUNC PyInit_gpyo(void)
{
    PyObject *m;
    
    errStatus gpioRtn;

    m = PyModule_Create(&gpiomodule);
    if (m == NULL)
    {
        return NULL;
    }
    
    gpyoError = PyErr_NewException("gpyo.error", NULL, NULL);
    Py_INCREF(gpyoError);
    PyModule_AddObject(m, "error", gpyoError);

    if ((gpioRtn = gpioSetup()) != OK)
    {
        PyErr_Format(gpyoError, "gpioSetup failed. %s", 
                     gpioErrToString(gpioRtn));
        return NULL;
    }
    return m;
}

