#include "bsp_Encoder.h"
#include "stm32f10x.h"


void Encoder_Init_TIM_X(void)
{
	/*使能编码器接口的GPIO时钟，初始化为相应配置*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(Encoder_CH2_RCC_Periph, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Encoder_CH1_PIN;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(Encoder_CH1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = Encoder_CH2_PIN;
	GPIO_Init(Encoder_CH2_PORT, &GPIO_InitStructure);
	
	/*使能编码器相关定时器的时钟，并配置好定时器的模式为编码器模式3，双输入，均检测*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(Encoder_CH1_RCC_Periph, ENABLE);
	Encoder_FUN_TIMX_RCC_CLOCK_CMD(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = Encoder_TIM_Prescaler; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = Encoder_TIM_Period; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(Encoder_TIM_X, &TIM_TimeBaseStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure; 
	TIM_EncoderInterfaceConfig(Encoder_TIM_X, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(Encoder_TIM_X, &TIM_ICInitStructure);
	TIM_ClearFlag(Encoder_TIM_X, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(Encoder_TIM_X, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(Encoder_TIM_X,0);
	TIM_Cmd(Encoder_TIM_X, ENABLE); 
}
