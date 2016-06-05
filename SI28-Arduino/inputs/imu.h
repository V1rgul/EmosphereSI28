#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#include "i2cdevlib_teensy/Arduino/I2Cdev/I2Cdev.h"
#include "i2cdevlib_teensy/Arduino/MPU6050/MPU6050.h"
//#include "helper_3dmath.h"

#include "../com.h"
#include "../filters.h"


#define IMU_RANGE_CONFIG MPU6050_ACCEL_FS_2
#define IMU_G_PER_LSB ( ((double)1)/16384 )
//  2G : 16384
//  4G : 8192
//  8G : 4096
// 16G : 2048

#define IMU_RANGE_G 1.0F //how much range do you want

#define IMU_LOWPASS 3.0F
#define IMU_PEAKDETECT .08F


const bool IMU_DEBUG = 0;


class IMU {
	MPU6050 mpu;
	int16_t last[6]; //accel x,y,z; gyro x,y,z
	Lowpass lpL;
	PeakDetect pdL;

public:
	float outL_raw = 0;
	float &outL = pdL.out;

	IMU() :
		lpL(IMU_LOWPASS), pdL(IMU_PEAKDETECT) {
		//nothing here
	}

	void init(){
		Wire.begin();
		ComDebugF("Initializing IMU... ");
		mpu.initialize();
		ComDebugF( mpu.testConnection() ? "IMU OK !" : "IMU ERROR /!\\");
		ComDebugF('\n');
		mpu.setFullScaleAccelRange(IMU_RANGE_CONFIG);
		mpu.setDLPFMode( MPU6050_DLPF_BW_5 ); //Digital LowPass Filter at 5Hz
	}

	void compute(const float step){
		//gyro is actually speed
		double tmp;

		//max 16:32767
		tmp =	pow(last[0]*IMU_G_PER_LSB, 2) +
				pow(last[1]*IMU_G_PER_LSB, 2) +
				pow(last[2]*IMU_G_PER_LSB, 2);
		tmp = sqrt(tmp);

		//ComDebug("SQ:"); ComDebug(tmp, 20);
		tmp -= 1;				// -1 :remove Earth gravity
		tmp /= IMU_RANGE_G;		// max choosen range

		outL_raw = constrain(tmp, 0, 1); 

		if(IMU_DEBUG){ ComDebug(" AR:"); ComDebug(outL_raw); }

		lpL.next(outL_raw, step);

		if(IMU_DEBUG){ ComDebug(" LP:"); ComDebug(lpL.out); }
		pdL.next(abs(lpL.out), step);
		if(IMU_DEBUG){ ComDebug(" PD:"); ComDebug(pdL.out); ComDebug('\n'); }
		outL = pdL.out;
	}

	void read(){		
		mpu.getMotion6(&last[0], &last[1], &last[2], &last[3], &last[4], &last[5]);
	}

	void debug(){
		ComDebug("IMU: ");
		ComDebug(last[0]); ComDebug('\t');
		ComDebug(last[1]); ComDebug('\t');
		ComDebug(last[2]); ComDebug('\t');
		ComDebug(last[3]); ComDebug('\t');
		ComDebug(last[4]); ComDebug('\t');
		ComDebug(last[5]); ComDebug('\n');
	}



};


#endif