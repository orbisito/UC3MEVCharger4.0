/**
 ******************************************************************************
 * @file      cargador_coche.c
 * @author    Sergio Orbís García
 * @brief     programa de cargador eléctrico de coche
 *
 *            For more information about which c-functions
 *            need which of these lowlevel functions
 *            please consult the Newlib libc-manual
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 UC3M.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes */
#include "cargador_coche.h"
//#include "adc_if.h"
//#include "adc.h"
#include "sys_app.h"
#include "lora_app.h"

#include <stdio.h>
#include <stdlib.h>


/* Variables */

typedef enum{
    STANDBY,
    VEHICULO_DETECTADO,
    CARGANDO,
	VENTILACION,
    NO_POWER,
	FALLO,
} ESTADO_CARGADOR;

uint16_t voltaje_CP=0;


ESTADO_CARGADOR estado;


void decodifica_estado(uint16_t voltaje_CP)
{
	if ( voltaje_CP > 2800 ) // 3299mV -> +12V
			{
				estado = STANDBY;
			}

	else if  (voltaje_CP > 1900  && voltaje_CP < 2800 )  // 2250mV -> +9V +-1
			{
				estado = VEHICULO_DETECTADO;
			}

	else if ( voltaje_CP > 1000  && voltaje_CP < 1900 ) // 1500mV -> + 3V +-1
			{
				estado = CARGANDO;
			}

	else if ( voltaje_CP > 600  && voltaje_CP < 1000 ) // 750mV -> + 6V +-1
			{
				estado = VENTILACION;
			}

	else if ( voltaje_CP > 50  && voltaje_CP < 600 ) //  0V
			{
				estado = NO_POWER;
			}
	else
			{
				estado = FALLO; //  - 12V
			}

}





/* Functions */


void cargador_coche_inicio()
{


	//while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)){

	voltaje_CP=GetLectura_CP();

	//}

	decodifica_estado(voltaje_CP);


	    switch (estado) {
	        case STANDBY:

	        	HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
	        	HAL_Delay(1000);
	        	HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
	            HAL_Delay(1000);

	            break;

	        case VEHICULO_DETECTADO:


	            break;
	        case CARGANDO:

	            break;
	        case VENTILACION:

	        	HAL_GPIO_TogglePin(GPIOB, LED2_Pin);
	        	HAL_Delay(1000);
	        	HAL_GPIO_TogglePin(GPIOB, LED2_Pin);
	        	HAL_Delay(1000);

	            break;

	        case NO_POWER:

	        	break;
	        case FALLO:


	       	    break;
	        default:
	            break;
	    }
}















