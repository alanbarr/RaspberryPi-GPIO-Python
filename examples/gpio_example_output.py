#
#  GPIO Example Output:
#  The following is an example of using the GPIO library to configure a
#  GPIO pin as an output as an output and toggle the pin high and low several
#  times before leaving it high upon exit.
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# Tested Setup:
# Raspberry Pi GPIO PIN -->|
#                          |
#                          |
#                         LED
#                          |
#                          |
#                       RESISTOR
#                          |
#                          |
# Raspberry Pi GND PIN  <--|
#
# RESISTOR = 470 R
#

import gpyo
import time

GPIO_PIN = 25

if __name__ == "__main__":

    gpyo.pin_function(GPIO_PIN, "output") 

    gpyo.pin_state(GPIO_PIN, "high")

    time.sleep(1)

    gpyo.pin_state(GPIO_PIN, "low")

    time.sleep(1)

    gpyo.pin_state(GPIO_PIN, "high")

    time.sleep(1)

    gpyo.pin_state(GPIO_PIN, "low")

    time.sleep(1)

    gpyo.pin_state(GPIO_PIN, "high")

