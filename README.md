# Minecraft Damage Buzzer

In short, this project contains three parts, a node.js web-server, a Minecraft
Java Plugin, and ESP32 C/C++ code.

The first part is the web-server, which was hosted on a Raspberry Pi 4. This
web-server would listen for GET and POST requests to the `/hurt` sub-directory,
providing and incrementing `hurtCounter` respectively. The code for this part
could be found in the `raspi-web-server` directory.

The second part is the Minecraft Plugin (made for spigot 1.16.1), which would
send a POST request to this web server whenever any player in the server would
take damage. The code for this part could be found in the `dmg-buzzer`
directory.

Finally, the third part is the ESP32 code. The ESP32 is connected to an active
piezoelectric buzzer to `pin 33`. The ESP32 would repeatedly make GET requests
to the web-server and detect whenever there was a change in parity. If a change
in parity was detected, it would activate the buzzer for a designated amount of
time. The code for this part can be found in the `esp-buzzer` directory.

This project was inspired by "Minecraft but..." videos which rose in popularity
in 2020. In this case, this project was meant to be "Minecraft but a Buzzer goes
off when I take damage."
