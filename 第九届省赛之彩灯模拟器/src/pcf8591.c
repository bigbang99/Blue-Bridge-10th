#include "config.h"
#include "i2.h"

#define VCC 50

u8 GetADCValue(u8 chn)
{
	u8 val;
	
	I2CStart();
	if(!I2CWrite(0x48<<1))
	{
		I2CStop();
		return 0;
	}
	I2CWrite(0x40 | chn);
	I2CStart();
	I2CWrite((0x48<<1) | 0x01);
	I2CReadACK();
	val = I2CReadNACK();
	I2CStop();
	
//	val = (val*VCC) / 255;
	return val;
}

void SetDACOut(u8 val)
{
	val = (val*255) / VCC;
	
	I2CStart();
	if(!I2CWrite(0x48<<1))
	{
		I2CStop();
		return ;//设定温度没有返回值，所以返回空
	}
	I2CWrite(0x40);
	I2CWrite(val);
	I2CStop();
}