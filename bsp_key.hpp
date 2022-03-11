
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


#ifndef __BSP_KEY_HPP
#define __BSP_KEY_HPP
#include "stm32f1xx.h"
#include "main.h"


/*****			�����ఴ�����캯��				******/
class Key
{
	public:
		GPIO_TypeDef* GPIO_Port;	//�����ṹ��˿ں�
		uint16_t Pin;				//�����ṹ�����ź�

		uint8_t State;			//ʵʱ��ʱ�İ����������

		//��Ա����
		Key(void){};
		Key(GPIO_TypeDef* GPIO_Port, uint16_t Pin);	
		void read(void);
	protected:
		
};



/*****			�����ఴ�����캯��				******/
class Button:public Key
{
	public:
		uint16_t time_check;			//����ʱ���ж���
		uint8_t Button_State;				//ʵ����Ҫ���õ�״̬	
		//��Ա����
		Button(GPIO_TypeDef* GPIO_Port, uint16_t Pin,uint16_t time_check);
		void update(void);
	protected:	
	private:
		//���㴢����
		uint32_t time_flag;		//�����жϱ�־λ
		uint8_t Ture_State;		//������ʾ��״������,���ڳ���ʱ����ڱ����ж�,Ŀǰ����δʹ������ʱ��ʹ��
		uint8_t Last_State;		//��һ�μ��״̬
};


#endif
