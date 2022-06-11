/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   -------------------------------------------------------------------------------------
                              CONFIGURACIÓN HX711_ADC 
   -------------------------------------------------------------------------------------
*/
/**********************************************************************************************
***********************************     SAMPLES        **************************************
**********************************************************************************************
Los valores permitidos para "SAMPLES" son:
[1, 2, 4, 8, 16, 32, 64, 128]
Este parámetro está ligado directamente al resultado del FILTRO_PASA_BAJO.
A Valores alto de "SAMPLES" por Ejemplo:
SAMPLES = 64  o SAMPLES = 128
 -Se comportará mucho mejor a la relación señal/ruido y espurios. 
 -Será suabe la respuesta a las fluctuaciones de valor y eliminará las oscilaciones muy brusca de las medidas.
 -Tendra  mejor respuesta integral, por lo contrario una peor respuesta deribativa y proporcional
 -Demandará mucha mas memoria cuanto mas alto sea el valor de SAMPLE y el tiempo de respuesta se alargará considerablemente 
 
 A Valores bajos de "SAMPLES" por Ejemplo:
SAMPLES = 1  o SAMPLES = 8 y cuanto mas bajo sea el valor de SAMPLE
  -Las medidas pueden ser mucho mas sensibles a la perturbación de ruidos y expurios
  -Será sensible las respuestas a las fluctuaciones de valor y mostrará las oscilaciones muy brusca de las medidas.
  -Tendra  mejor respuesta derivativa y proporcional por lo contrario  una  respuesta peor integral
  -Demandará mucha menos memoria cuanto más bajo sea el valor de SAMPLE y el tiempo de respuesta se acortara  

El TIEMPO_DE_RESPUESTA se puede calcular así;
TIEMPO_DE_RESPUESTA = (SAMPLES + IGN_HIGH_SAMPLE + IGN_LOW_SAMPLE) / SPS

Example on calculating settling time using the values
SAMPLES = 16,
IGN_HIGH_SAMPLE = 1, 
IGN_LOW_SAMPLE = 1, 
SPS=10
(16+1+1)/10 = 1.8 seconds settling time.

Tenga en cuenta que también puede cambiar el número de muestras en uso en cualquier momento con la función:
setSamplesInUse(samples).

*/
/**********************************************************************************************
***********************************     SAMPLES        **************************************
**********************************************************************************************

SAMPLES es el número de muestras en el conjunto de datos de promedio móvil o media movil, 
los valores que se esperan pueden ser 1, 2, 4, 8, 16, 32, 64 or 128.

La media móvil es un Filtro digital PASA_BAJOS utilizado para analizar un conjunto de datos 
en modo de una serie de Puntos Temporales para crear series de promedios en formas de subconjuntos de valores.
Así las medias móviles son una lista de números en la cual cada uno es el promedio de un subconjunto de los datos originales.
Por ejemplo, si se tiene un conjunto de 128 datos distribuidos homogeniamente en el tiempo, a períodos regulares 
o que tiendan a ser regulares.
El primer valor de la serie de medias móviles podría ser el promedio de los primeros 32 términos, 
luego el promedio de los términos 2 al 33, el tercer elemento de los términos 3 al 34 y así,
hasta por último el promedio de los últimos 32 números del 96 al 128.
Una serie de medias móviles puede ser calculada para cualquier serie de tiempo.
Por lo tanto los PID, las transformada de fourier y Laplace pueden ser sensibles a este filtro si la serie es demaciado larga.
Se usa para demanda estable, sin tendencia ni estacionalidad;  suaviza las fluctuaciones de plazos cortos,
resaltando así las tendencias o ciclos de plazos largos.
Como se puede ver utilizar 128 valores demandará mucha memoria RAM y procesos de la ALU
*/
#define SAMPLES 					16		//Valor por defecto al inicializar: 16



/**********************************************************************************************
**********************     IGN_HIGH_SAMPLE &  IGN_LOW_SAMPLE        ***************************
***********************************************************************************************/
//agrega muestra(s) adicional(es) al conjunto de datos e ignora la muestra peak alta/baja, el valor debe ser 0 o 1
#define IGN_HIGH_SAMPLE 			1		//Valor por defecto al inicializar: 1
#define IGN_LOW_SAMPLE 				1		//Valor por defecto al inicializar: 1

/**********************************************************************************************
***********************************     SCK_DELAY        **************************************
***********************************************************************************************/
//retraso de microsegundos después de escribir pin sck alto o bajo. 
//Este retraso podría ser necesario para MICROCONTROLADORES más rápidos.
//Hasta ahora, el único MICROCONTROLADOR informado que necesita este retraso es el ESP32 (problema  35), 
//tanto el Arduino Due como el ESP8266 parecen funcionar bien sin él.
//Cambiar el valor a '1' para habilitar el retraso.

#define SCK_DELAY					0		//default value: 0


/**********************************************************************************************
*********************    Administración de las interrupciones      ****************************
***********************************************************************************************
si tiene otras rutinas de interrupción que consumen mucho tiempo (> 60 μs) que se activan mientras el pin sck está alto,
esto podría configurar involuntariamente el HX711 en el modo de "apagado"
si es necesario, puede cambiar el valor a '1' para deshabilitar las interrupciones al escribir en el pin sck
*/

#define SCK_DISABLE_INTERRUPTS		0		//default value: 0

