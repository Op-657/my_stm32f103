#include "bsp_Encoder.h"
#include "stm32f10x.h"


void Encoder_Init_TIM_X(void)
{
	/*ʹ�ܱ������ӿڵ�GPIOʱ�ӣ���ʼ��Ϊ��Ӧ����*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(Encoder_CH2_RCC_Periph, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Encoder_CH1_PIN;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(Encoder_CH1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = Encoder_CH2_PIN;
	GPIO_Init(Encoder_CH2_PORT, &GPIO_InitStructure);
	
	/*ʹ�ܱ�������ض�ʱ����ʱ�ӣ������úö�ʱ����ģʽΪ������ģʽ3��˫���룬�����*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(Encoder_CH1_RCC_Periph, ENABLE);
	Encoder_FUN_TIMX_RCC_CLOCK_CMD(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = Encoder_TIM_Prescaler; // Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = Encoder_TIM_Period; //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(Encoder_TIM_X, &TIM_TimeBaseStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure; 
	TIM_EncoderInterfaceConfig(Encoder_TIM_X, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(Encoder_TIM_X, &TIM_ICInitStructure);
	TIM_ClearFlag(Encoder_TIM_X, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(Encoder_TIM_X, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(Encoder_TIM_X,0);
	TIM_Cmd(Encoder_TIM_X, ENABLE); 
}
