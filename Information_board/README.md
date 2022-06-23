# Information_board
This folder contains files used for creating the info board. 

Infoboard_Arduino contains the project for the final software for the board, it is currently unfinished. 

Infoboard_demo contains the project used to showcase the board at the symposium. Values for the dot matrices were static hard coded and no internet connection was used. An Arduino Uno was used because the feather died.

InformationBoard_MQTT_data_supplier is the python project that reads data from the database on the raspberry pi in the lab and sends it over mqtt to the feather. It should run on any windows machine, preferably at the lab. This code has not been tested for a long period of time, accessing the database over and over might result in the raspberry crashing.

