directory & files
/dev
	device & on-board sensors
	- acc-sensor : for the onboard MMA accelerometer sensor
	- button-sensor : for user button
	- ctn-sensor : for the onboard ctn sensor
	- light-sensor : for the on board chip apds luminosity sensor 	
	- modified for onboard i2c : TI_USCI_I2C.. todo transform in i2c driver..
/extsensor
	external sensor, connected to J7 connector
	example sht15 (see in example/wismote/testsht51)
/arch
	architecture specific file for compatibility with contiki
	files for node_id		