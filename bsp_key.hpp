
/**
 * @file bsp_Key.cpp
 * @brief Key板级支持包
 * @author Tony_Wang
 * @version 1.2
 * @date 2022-3-11
 * @copyright 
 * @par 日志:
 *   V1.0 基本Cube配置与基本设置
 *	 V1.1 重构为C++库，派生各类Key，并可用系统时钟调用长按
 *	 V1.2 Button长按修改为不松开仍然生效
 */	


#ifndef __BSP_KEY_HPP
#define __BSP_KEY_HPP
#include "stm32f1xx.h"
#include "main.h"


/*****			自锁类按键构造函数				******/
class Key
{
	public:
		GPIO_TypeDef* GPIO_Port;	//按键结构体端口号
		uint16_t Pin;				//按键结构体引脚号

		uint8_t State;			//实时当时的按键按下情况

		//成员函数
		Key(void){};
		Key(GPIO_TypeDef* GPIO_Port, uint16_t Pin);	
		void read(void);
	protected:
		
};



/*****			派生类按键构造函数				******/
class Button:public Key
{
	public:
		uint16_t time_check;			//长按时间判断域
		uint8_t Button_State;				//实际需要调用的状态	
		//成员函数
		Button(GPIO_TypeDef* GPIO_Port, uint16_t Pin,uint16_t time_check);
		void update(void);
	protected:	
	private:
		//运算储存区
		uint32_t time_flag;		//长按判断标志位
		uint8_t Ture_State;		//按键表示的状况标致,用于长按时间段内标致判断,目前仅由未使用内置时钟使用
		uint8_t Last_State;		//上一次检测状态
};


#endif
