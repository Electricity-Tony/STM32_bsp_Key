/**
 * @file bsp_Key.cpp
 * @brief Key�弶֧�ְ�
 * @author Tony_Wang
 * @version 1.2
 * @date 2022-3-11
 * @copyright 
 * @par ��־:
 *   V1.0 ����Cube�������������
 *	 V1.1 �ع�ΪC++�⣬��������Key��������ϵͳʱ�ӵ��ó���
 *	 V1.2 Button�����޸�Ϊ���ɿ���Ȼ��Ч
 */	

#include "bsp_key.hpp"


#define WEAK __attribute__((weak)) //ʹ��WEAK�����Ƿ������������ع��ض�����
#define MICROS_ms() HAL_GetTick()  //��ʱ����λms,��1000����


/*****			�����ఴ�����캯��				******/
WEAK Key::Key(GPIO_TypeDef* GPIO_Port, uint16_t Pin)
{
	this->GPIO_Port = GPIO_Port;
	this->Pin = Pin;

}
/**
* @brief  ��ȡ��ǰ�����İ���״̬
* @details  
* @param  
* @retval  ��ȡ�����ఴ��״̬
*/
void Key::read()
{ 
	Key::State = HAL_GPIO_ReadPin(Key::GPIO_Port, Key::Pin);
}



/*****			�����ఴ�����캯��				******/
WEAK Button::Button(GPIO_TypeDef* GPIO_Port, uint16_t Pin,uint16_t time_check)
{
	this->GPIO_Port = GPIO_Port;
	this->Pin = Pin;
	this->time_check = time_check;
}



/**
* @brief  ��������ʱ�����
* @details  �������£��ɿ���Ϊ����
* @param  ����Button�����״̬State��1��0����ֵ�ࣩ��2��������
*/
void Button::update()
{
	this->read();		//Button::read();�������Ҳ��

#ifdef MICROS_ms	//ʹ������ʱ�ӿ��Ƴ����ж�
	if(this->State ==0 && this->Last_State == 1)	//��ʾ��������˲��
	{
		this->time_flag = MICROS_ms();		//��¼����ʱ��ʱ��
		this->Last_State = this->State;
	}
	else if (this->State ==1 && this->Last_State == 0)	//��ʾ�����ɿ�˲��
	{
		this->time_flag = MICROS_ms() - this->time_flag;	//���㰴���ڼ��ʱ��
		this->Last_State = this->State;
		
		if(this->time_check < this->time_flag)	//��������
		{this->Button_State = 2;}
		
		else if(this->time_check > this->time_flag && this->time_flag > 10)	//�̰�����
		{
			if(this->Button_State == 0)	this->Button_State = 1;
			else this->Button_State = 0;
		}
		
		else {}	//���������������	
	}



#else
	//����״̬�жϣ������ж��м�̬�������Ture_State�д��
	//0��ʾû�а��»��ڳ����м�̬�У�1��ʾ�̰�������2��ʾ��������
	//Ĭ��Now_StateΪ�͵�ƽ��ʾ����
	if(this->time_flag > this->time_check)
	{
		//����ʱ���־λ��������������
		if(this->State == 1) this->time_flag=0;
		this->Ture_State = 2;
	}
	else if(this->State==0) 
	{
		//�����м�̬������ʱ���־λ����
		this->time_flag++;
		this->Ture_State = 0;
	}
	else if(10< this->time_flag && this->time_flag < this->time_check)
	{
		//�̰�����
		this->time_flag=0;
		this->Ture_State = 1;
	}
	else 
	{
		this->time_flag = 0;	//��ճ�����־λ
		this->Ture_State = 0;	//һֱû�а���
	}

	//�жϰ���״̬�仯��Ĭ�϶�ֵ̬���̰�����
	if (this->Button_State != 1 && this->Ture_State == 1)
	{
		this->Button_State = 1;
	}
	else if(this->Button_State != 0 && this->Ture_State == 1)
	{
		this->Button_State = 0;
	}
	else if(this->Ture_State == 2)
	{
		this->Button_State = 2;
	}
#endif
}
