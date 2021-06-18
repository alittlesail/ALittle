#include <wiringPi.h>
#include <softPwm.h>

// LED Pin - wiringPi pin 0 是 BCM_GPIO 17。
// 利用 wiringPiSetupSys 进行初始化时必须使用 BCM 编号
// 选择其他 pin 编号时，请同时使用 BCM 编号
// 更新 Property Pages - Build Events - Remote Post-Build Event 命令
// 它使用 gpio 导出进行 wiringPiSetupSys 的设置
#define	LED	17

#define uchar unsigned char
#define PinRed 0
#define PinGreen 1

void Init(void)
{
	softPwmCreate(PinRed, 0, 100);
	softPwmCreate(PinGreen, 0, 100);
}

void ColorSet(uchar r, uchar g)
{
	softPwmWrite(PinRed, r);
	softPwmWrite(PinGreen, g);
}

int main(void)
{
	if (wiringPiSetup() == -1)
	{
		return 0;
	}

	Init();

	while (true)
	{
		ColorSet(0xff, 0x00);
		delay(500); // 毫秒
		ColorSet(0x00, 0xff);
		delay(500);
	}
	return 0;
}