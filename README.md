# Sprinkler
Home Sprinkler Controller 


1. Components Required:
- Arduino Board (e.g., Arduino Maga) (Any will work)
- 4 x Relays (capable of handling 24V)
- Real-Time Clock (RTC) module (e.g., DS3231)
- Jumper wires
- 24V power source

2. Connections:
- Connect the RTC Module:
- VCC to Arduino 5V
- GND to Arduino GND
- SDA to Arduino A4 (or SDA pin on boards that have one)
- SCL to Arduino A5 (or SCL pin on boards that have one)
-Connect the Relays:
- Connect the control pins of the 4 relays to 4 digital pins on the Arduino (e.g., D2, D3, D4, D5).
- Connect each relay's common (COM) terminal to the 24V power source.
- Connect each relay's normally open (NO) terminal to each of the 4 sprinklers. 
- Connect the ground of the 24V source to all the sprinklers.

3. Procedure:
1. Connect all the components as per the connections mentioned.
2. Load the Arduino code to the Arduino.
3. Set the current time in the RTC module (this can be done using various RTC libraries and code).
4. Once the time is set, the Arduino will automatically activate the sprinklers sequentially at 8 am every day for 5 minutes each.

4. Additional Considerations:
1. Make sure to protect the 24V connections, especially if they are outdoors. Using waterproof containers or enclosures can help.
2. Always check the rating of the relay before connecting to ensure it can handle 24V and the current required by the sprinklers.
3. It's good practice to test the setup with one sprinkler before connecting them all.


