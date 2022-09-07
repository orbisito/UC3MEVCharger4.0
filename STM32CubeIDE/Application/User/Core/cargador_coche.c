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
#include "sys_app.h"
#include "lora_app.h"

#include <stdio.h>
#include <stdlib.h>

#include "LCD_I2C.h"
#include "sys_sensors.h"

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


void decodifica_estado(uint16_t voltaje_CP, uint16_t temperature)
{
	if ( voltaje_CP > 2800 && temperature < 60 ) // 3299mV -> +12V
			{
				estado = STANDBY;
			}

	else if  ((voltaje_CP > 1900  && voltaje_CP < 2800 )&&(temperature < 60)) // 2250mV -> +9V +-1
			{
				estado = VEHICULO_DETECTADO;
			}

	else if (( voltaje_CP > 1000  && voltaje_CP < 1900 )&&(temperature < 60)) // 1500mV -> + 6V +-1
			{
				estado = CARGANDO;
			}

	else if (( voltaje_CP > 600  && voltaje_CP < 1000 )&&(temperature < 60)) // 750mV -> + 3V +-1
			{
				estado = VENTILACION;
			}

	else if (( voltaje_CP > 50  && voltaje_CP < 600 )&&(temperature < 60)) //  0V
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

	LCD_Command (0x01); //borrar pantalla

	voltaje_CP=GetLectura_CP();
	uint16_t temperature=GetTemperatureLevel();

	decodifica_estado(voltaje_CP, temperature);


	    switch (estado) {
	        case STANDBY:
	          	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_RESET);
	        	escribir_LCD ("EN ESPERA !!!", "Con I = 0A        ");
	            HAL_Delay(1000);
	            break;

	        case VEHICULO_DETECTADO:
	        	escribir_LCD ("COCHE CONECTADO !!!", "Con I = 0A        ");
	        	HAL_Delay(3000);
	        	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_SET);
	            break;
	        case CARGANDO:
	        	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_SET);
	        	escribir_LCD ("CARGANDO !!!", "Con I = 9,6A        ");
	        	HAL_Delay(1000);
	            break;

	        case VENTILACION:
	        	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_RESET);
	        	escribir_LCD ("VENTILACION !!!", "Con I = 0A        ");
	        	HAL_Delay(1000);
	            break;

	        case NO_POWER:
	        	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_RESET);
	        	escribir_LCD ("FIN DE CARGA !!!", "Con I = 0A        ");
	        	HAL_Delay(1000);
	        	break;

	        case FALLO:
	        	HAL_GPIO_WritePin(CONTROL_CONTACTOR_GPIO_Port, CONTROL_CONTACTOR_Pin, GPIO_PIN_RESET);
	        	escribir_LCD ("FALLO !!!", "RETIRE CABLE !!!       ");
	        	HAL_Delay(1000);
	       	    break;

	        default:
	            break;
	    }
}


