#ifndef _BSP_ENCODER_H_
#define _BSP_ENCODER_H_


#define Encoder_FUN_TIMX_RCC_CLOCK_CMD				RCC_APB1PeriphClockCmd
#define Encoder_RCC_Periph										RCC_APB1Periph_TIM4		
#define Encoder_TIM_X													TIM4
#define Encoder_TIM_Prescaler									0
#define Encoder_TIM_Period										65535




#define Encoder_CH1_RCC_Periph								RCC_APB2Periph_GPIOB
#define Encoder_CH1_PORT											GPIOB
#define Encoder_CH1_PIN												GPIO_Pin_6

#define Encoder_CH2_RCC_Periph								RCC_APB2Periph_GPIOB
#define Encoder_CH2_PORT											GPIOB
#define Encoder_CH2_PIN												GPIO_Pin_7


void Encoder_Init_TIM_X(void);


#endif

