# 
#  GPIO Example Input
#  
#  The following is an example of using the GPIO library to configure a pin 
#  with a pullup resistor and put it into input mode.
#  The pin is then read at 1 second intervals for 10 seconds.
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
#  Tested Setup:
#  Raspberry Pi GPIO PIN -->|
#                           |
#                           |
#                         SWITCH
#                           |
#                           |
#  Raspberry Pi GND PIN  <--|

import time
import gpyo

GPIO_PIN = 25

if __name__ == "__main__":
     
    gpyo.pin_function(GPIO_PIN, "input")
    
    gpyo.pin_resistor(GPIO_PIN, "pullup")

    for ctr in range(10):
        state = gpyo.pin_read(GPIO_PIN)
        print("State was %s" %( "high" if state else "low"))
        time.sleep(1)



