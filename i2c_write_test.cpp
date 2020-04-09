#include <iostream>
#include <thread>
#include <chrono>
#include <wiringPiI2C.h>

#define DEVICE_ID 0x04
#define REG_POWER_CTL   0x2D
#define REG_DATA_X_LOW  0x32
#define REG_DATA_X_HIGH 0x33
#define REG_DATA_Y_LOW  0x34
#define REG_DATA_Y_HIGH 0x35
#define REG_DATA_Z_LOW  0x36
#define REG_DATA_Z_HIGH 0x37

int main (int argc, char **argv){
	
	// Setup I2C communication
	int fd = wiringPiI2CSetup(DEVICE_ID);
	if (fd == -1) {
		std::cout << "Failed to init I2C communication.\n";
		return -1;
	}
	std::cout << "I2C communication successfully setup.\n";
	
	
	int i = 1;
	while (1){
		
		wiringPiI2CWrite(fd, i);
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		wiringPiI2CWrite(fd, 2*i);
		i  = i + 1;
		if (i == 125){
			i = 0;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
		wiringPiI2CWrite(fd, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "end sequence\n";
	}

	// Switch device to measurement mode
	//wiringPiI2CWriteReg8(fd, REG_POWER_CTL, 0b00001000);
	//while (1) {
		//int dataX = wiringPiI2CReadReg16(fd, REG_DATA_X_LOW);
		//dataX = -(~(int16_t)dataX + 1);
		//int dataY = wiringPiI2CReadReg16(fd, REG_DATA_Y_LOW);
		//dataY = -(~(int16_t)dataY + 1);
		//int dataZ = wiringPiI2CReadReg16(fd, REG_DATA_Z_LOW);
		//dataZ = -(~(int16_t)dataZ + 1);
		//std::cout << "x: " << dataX << ", y: " << dataY << ", z: " << dataZ << "\n";
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//}
	return 0;
}
