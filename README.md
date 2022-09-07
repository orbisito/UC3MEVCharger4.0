﻿# CARGADOR_COCHE
# UC3MEVCharger4.0
//El UC3MEVCharger4.0 es un proyecto de un prototipo de cargador de coche eléctrico inteligente que ha sido programado íntegramente por Sergio Orbis García como trabajo final de grado (TFG) de la titulación Ingeniería en Tecnologías Industriales en la Universidad Carlos III de Madrid.
//El microcontrolador empleado es un STM32 NUCLEO-WL55JC.
//Para programar el código se han empleado STM32CubeMX para configurarlo y generar el código base y STM32CubeIDE para programar.
//El UC3MEVCharger4.0 emplea el protocolo de comunicación LoRaWAN para conectarse a un gateway, es por esto que fue necesario implementar el sistema operativo de FreeRTOS y tener en pararelo funcionando en un hilo LoRa y en otro todo lo relativo al cargador de coche, la lectura de la pantalla LCD, el envío de datos a Cayenne, en otros.
//El código sigue la normativa ITC-BT 52 en cuanto a estados de carga de los vehículos.
//Adicionalmente se han incluido funciones de lectura para LCD.
//Los datos enviados por el microcontrolador son recibidos en el gateway, que los sube a la nube, a los servidores de TheThingsNetwork y a los que, posteriormente, accede Cayenne mediante un webhook y actúa de endnode, con app para el teléfono móvil donde se actualizan 4 datos del estado de la carga: Temperatura, Voltaje_CP que entra al microcontrolador, ruido en la señal y la tensión de referencia interna en el microcontrolador.
//Pueden encontrar el TFG completo con el código explicado al detalle en la base de datos abierta de la universidad Carlos III de Madrid.
