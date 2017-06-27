#include "stm32f10x.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_Encoder.h"

int main(void)
{
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        
				systick_init();
        usart_init();
				Encoder_Init_TIM_X();
        
        while(1)
        {
                
								printf("[%s][%d]", __func__, __LINE__);
								printf("编码器的数值为%d\n",(u16)TIM4->CNT);
								delay_ms(100);
        }
}
