/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"
#include "Keys.h"
#include "Application.h"

static void AppTask(void* param) {
  const int *whichLED = (int*)param;

  (void)param; /* avoid compiler warning */
  for(;;) {
    if (*whichLED==1) {
      LED1_Neg();
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(100));
    } else if (*whichLED==2) {
      LED2_Neg();
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(500));
    }
    /* \todo handle your application code here */

  }
}

void RTOS_Init(void) {
  static const int led1 = 1;
  static const int led2 = 2;

  EVNT_SetEvent(EVNT_STARTUP); /* set startup event */
  /*! \todo Create tasks here */
  if (FRTOS1_xTaskCreate(AppTask, (uint8_t *)"App1", configMINIMAL_STACK_SIZE, (void*)&led1, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error case only, stay here! */
  }

  if (FRTOS1_xTaskCreate(AppTask, (uint8_t *)"App2", configMINIMAL_STACK_SIZE, (void*)&led2, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error case only, stay here! */
  }
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

void RTOS_Run(void){
	RTOS_Init();
	//vTaskStartScheduler();
}

#endif /* PL_CONFIG_HAS_RTOS */
