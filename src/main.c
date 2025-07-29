#include "main.h"
#include "util.h"
#include "fnd.h"
#include "sysclock.h"
#include "systick.h"
#include "uart.h"
#include "led.h"
#include "xprintf.h"
#include "push_button.h"
#include "buzzer.h"


#define idle    			0
#define mode1					1


#define go		  			4
#define stop					5
#define reset					6
#define paused				7
#define emergency_mode 9



#define idle_r  			20



#define BUFFER_SIZE   32 

volatile uint16_t stop_time = 0;
volatile int state = idle;
volatile uint16_t segment_counter,led_counter;
volatile uint8_t digit3, digit2, digit1, digit0;
volatile int i = 1;

volatile int buzzer_played = 0;
volatile int uart_me = 0;

volatile uint8_t ledstate = 0;

volatile uint32_t curTicks; 
volatile uint32_t prevTicks,prevTicks_blink;
volatile uint8_t blink_led = 0;
volatile uint8_t fixed_led = 0x00; 
volatile int increment= 0;

int8_t cbuf[100];

uint8_t USART2_Buffer_Rx[BufferSize] = {0xFF};
uint32_t Rx2_Counter = 0;
uint8_t newline_flag = 0;




void Buzzer_PlayCompleteSoun(void) {
    int i;
    for (i = 0; i < 3; i++) {
        Buzzer_On();
        TimeDelay(5000000); 
        Buzzer_Off();
        TimeDelay(5000000); 
    }
}


void reset_buffer() {
    xmemset(USART2_Buffer_Rx, 0xFF, BUFFER_SIZE);
    Rx2_Counter = 0;
}


int main(void){

	 int increment = 0; 
	
	System_Clock_Init(); // Switch System Clock = 180 MHz
	
	SysTick_Init();
	Led_Initialize();
	UART_Initialize(USART2);
	Fnd_Initialize();
	Buzzer_Init();
	
  //pb_init
	pb_initialize();
	pb_interrupt_init();
	
	
	xdev_out(UART_xPutChar);
	xdev_in(UART_xGetChar);
	xprintf("Would you like to bring an AED? \r\n");

     
	while(1) {
		if (state == idle_r) {
			xprintf("Would you like to bring an AED?\r\n");
			state = idle;
		}

//main
		if (newline_flag == 1) {
			newline_flag = 0;
			
			switch(*USART2_Buffer_Rx ){
				case 'y':{
					xprintf("I brought an AED.\n");
					state = mode1;
					reset_buffer();
					buzzer_played = 0;
					Led_display(0x00);
					blink_led = 0;
					prevTicks_blink = 0;
					fixed_led = 0x00; 
					uart_me = 0;
					increment = 0;
					
			
					while(1){
						if (newline_flag == 1){
							newline_flag = 0;
							if (*USART2_Buffer_Rx == 'r') {
								reset_buffer();
								state = idle_r;
								segment_counter = 0;
								buzzer_played = 0;  
								uart_me =0; 
								Fnd_Zero();
								Led_display(0x00); 
								increment = 0;
								break;
							}  
							if (*USART2_Buffer_Rx == 'p' && segment_counter == 1000) {
                    reset_buffer();
                    segment_counter = 0;    
                    uart_me = 0;           
                    state = mode1;          
                    xprintf("It was shocking. Charging restarted\n");
                    Led_display(0x00); 
										blink_led = 0;
										prevTicks_blink = 0;
										fixed_led = 0x00; 
										buzzer_played =0;
										uart_me = 0;
										increment = 0;
                }
							 if (*USART2_Buffer_Rx == 'n' && segment_counter == 1000) {
                    if (state != paused) {  // Only pause if not already paused
												state = paused;  // Set state to paused
												xprintf("Charging paused. State is now held.\n");
												reset_buffer();
												continue;
											
										}
                    xprintf("Charging paused. State is now held.\n");
									
                }
							 if (*USART2_Buffer_Rx == 'p') {
                     if (state == paused || segment_counter == 1000) { 
													xprintf("It was shocking. Charging restarted\n");
													reset_buffer();
													state = mode1; 
													segment_counter = 0;    
													uart_me = 0;            
													state = mode1;         
													Led_display(0x00);     
													blink_led = 0;
													buzzer_played =0;
													prevTicks_blink = 0;
													fixed_led = 0x00;
													increment = 0;
													continue;
												
													        
            }         
                }
							
							else {
						  }
							reset_buffer();
						} 
						 if (state == paused) {
								continue;  // Do nothing if paused
							}
					curTicks = GetTick();
						if (curTicks - prevTicks >= 10){
								prevTicks = curTicks;
		
                 if (state ==go || state == emergency_mode ) 
									 {
										 increment = (state == emergency_mode) ? 10 : 1;  // Faster increment in emergency mode
										 segment_counter += increment;
										 if (segment_counter >= 1000) {
                           segment_counter = 1000;
										
											}
										 if (segment_counter == 1000) {
											if(buzzer_played==0){
													Buzzer_SetFrequency(2000);
													Buzzer_PlayCompleteSoun();  // Call buzzer function
													buzzer_played = 1;
											}
												if(uart_me == 0){
													 xprintf("Charging is complete. Do you want to shock? push(p)/no(n) \n");
													 uart_me  = 1;
											 }
												
										 }
                      else {
                           
                     }
										}
										digit3 =  segment_counter / 1000;
										digit2 = (segment_counter / 100) % 10;
										digit1 = (segment_counter /10 ) % 10;
										digit0 = segment_counter % 10;
										
										
								if (curTicks - prevTicks_blink >= 200 && (state == go ||state == emergency_mode)) {
                    prevTicks_blink = curTicks;
                    blink_led = ~blink_led; 
                }

                if (segment_counter < 200) {
                    fixed_led = 0x00;                      
                    Led_display(blink_led & 0x01);        
                } else if (segment_counter < 400) {
                    fixed_led = 0x01;                    
                    Led_display(fixed_led | ((blink_led & 0x01) << 1)); 
                } else if (segment_counter < 600) {
                    fixed_led = 0x03;                    
                    Led_display(fixed_led | ((blink_led & 0x01) << 2)); 
                } else if (segment_counter < 800) {
                    fixed_led = 0x07;                    
                    Led_display(fixed_led | ((blink_led & 0x01) << 3)); 
                } else if (segment_counter < 1000) {
                    fixed_led = 0x0F;                  
                    Led_display(fixed_led | ((blink_led & 0x01) << 4)); 
                } else if (segment_counter == 1000) {
                    Led_display(blink_led & 0x1F); 
                }
                    	 
							 }
							else if(state == stop){
								segment_counter = stop_time;
								
							}
							
					}
				break;

				}
				
				case 'r': {
					state = idle_r;
					break;
				}
				default:
					
					state = idle;
			}
			
		reset_buffer(); // Clear Buffer Count		
		}
	}
}


void EXTI2_IRQHandler(void) {  
  if ((EXTI->PR & EXTI_PR_PR2) == EXTI_PR_PR2) {
		
		if(state == mode1)
		{
			xprintf("Charging. Please wait a moment.\n");
			state = go;
		}
		else if(state == go)
		{
			if(segment_counter !=1000){
				xprintf("pause!\n");
				state = stop;
				stop_time = segment_counter;
			}
		}
		else if(state == stop)
		{
			if(segment_counter != 1000){
				xprintf("Charging. Please wait a moment.\n");
				state = go;
			}
			
		}
		else if(state == paused)
		{	
			if(segment_counter !=1000){
				xprintf("ReCharging. Please wait a moment.\n");
				state = go;
			}
		}

		else if (state == idle_r) {
			state = idle;
		}
    EXTI->PR |= EXTI_PR_PR2;
  }
}

void EXTI4_IRQHandler(void) {  
  if ((EXTI->PR & EXTI_PR_PR4) == EXTI_PR_PR4) {
	
		if(state == go)
		{ 
		 if(segment_counter!=1000){	
				xprintf("paused.\n");
				state = paused;
		 }
			
		}
		else if(state == paused)
		{
			if(segment_counter !=1000){
			xprintf("emergency_mode!\n");
			state = emergency_mode;
			}
		
		}
		else if(state == stop)
		{
			xprintf("reset!\n");
			state = mode1;
			reset_buffer();
			state = mode1; 
			segment_counter = 0;    
			uart_me = 0;           
			state = mode1;         
			Led_display(0x00);      
			blink_led = 0;
			buzzer_played =0;
			prevTicks_blink = 0;
			fixed_led = 0x00;
			increment = 0;
		
		}
		else if (state == idle_r) {
			state = idle;
		}
    EXTI->PR |= EXTI_PR_PR4;
  }
}

