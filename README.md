Último lanzamiento y registro de cambios originales en ingles aquí: https://github.com/olkal/HX711_ADC/releases

Esta es una biblioteca Arduino para el ADC de 24 bits HX711 para básculas de peso.
La recuperación de datos del HX711 se realiza sin detener el mcu, también en la configuración de velocidad de 10SPS y con múltiples conversiones de HX711 que realizan simultáneamente.
La función de tara también se puede realizar sin detener el mcu.
 
Filtrado y suavizado: el método de "media móvil" de un conjunto de datos móviles combinado con la eliminación de valores atípicos altos / bajos se utiliza para el valor recuperado.

Valores seleccionables en el archivo config.h:
- Conjunto de datos de media móvil de 1, 2, 4, 8, 16, 32, 64 o 128 muestras (predeterminado: 16).
- Ignorar valores atípicos altos; se agrega una muestra al conjunto de datos, el valor máximo de todas las muestras en el conjunto de datos se ignora (predeterminado: 1)
- Ignorar los valores atípicos bajos; se agrega una muestra al conjunto de datos, el valor pico bajo de todas las muestras en el conjunto de datos se ignora (predeterminado: 1)
- Habilite el retraso para escribir en el pin sck. Esto podría ser necesario para mcu más rápidos como el ESP32 (predeterminado: sin demora)
- Deshabilita las interrupciones cuando el pin sck está alto. Esto podría ser necesario para evitar el "modo de apagado" si tiene otras rutinas de interrupción que consumen mucho tiempo (> 60 µs) en ejecución (predeterminado: interrupciones habilitadas)

Precaución: el uso de una gran cantidad de muestras suavizará muy bien el valor de salida, pero también aumentará el tiempo de estabilización y el tiempo de arranque / tara (pero no el tiempo de respuesta). También comerá algo de memoria.

Importante: La frecuencia de muestreo del HX711 se puede configurar en 10SPS o 80SPS (muestras por segundo) tirando del pin 15 alto (80SPS) o bajo (10SPS), ref. Hoja de datos HX711.
En los módulos HX711 fabricados, generalmente hay un puente de soldadura en la PCB para el pin 15 alto / bajo. La configuración de la tasa se puede verificar midiendo el voltaje en el pin 15.
El ruido de ADC es peor en la tasa de 80SPS. A menos que se requiera un tiempo de estabilización muy rápido, 10SPS debería ser la mejor frecuencia de muestreo para la mayoría de las aplicaciones.

Inicio y tara: desde el inicio / reinicio, la función de tara parece ser más precisa si se llama después de un período de "precalentamiento" ejecutando conversiones continuamente durante unos segundos. Ver archivos de ejemplo.

Ruido de hardware y ADC:
Los cables entre el HX711 y la celda de carga deben retorcerse y mantenerse lo más cortos posible.
La mayoría de los módulos HX711 disponibles parecen seguir el diseño de referencia, pero tenga en cuenta que algunos módulos están mal diseñados con condensadores de tamaño insuficiente y lecturas ruidosas.
El módulo Sparkfun parece diferir de la mayoría de los otros módulos disponibles, ya que tiene algunos componentes adicionales para reducir el ruido.

Para comenzar: instale la biblioteca desde Arduino Library Manager. Comience con el archivo de ejemplo Calibration.ino, luego continúe con el archivo de ejemplo Read_1x_load_cell.ino.



This an Arduino library for the HX711 24-bit ADC for weight scales.
Data retrieval from the HX711 is done without halting the mcu, also on the 10SPS rate setting and with Multiple HX711's performing conversions simultaneously.
Tare function can also be performed without halting the mcu.
 
Filtering and smoothing: "Moving average" method from a rolling data set combined with removal of high/low outliers is used for the retrieved value.

Selectable values in the config.h file:
- Moving average data set of 1, 2, 4, 8, 16, 32, 64 or 128 samples (default:16).
- Ignore high outlier; one sample is added to the data set, the peak high value of all samples in the data set is ignored (default:1)
- Ignore low outlier; one sample is added to the data set, the peak low value of all samples in the data set is ignored (default:1)
- Enable delay for writing to sck pin. This could be required for faster mcu's like the ESP32 (default: no delay)
- Disable interrupts when sck pin is high. This could be required to avoid "power down mode" if you have some other time consuming (>60µs) interrupt routines running (default: interrupts enabled)

Caution: using a high number of samples will smooth the output value nicely but will also increase settling time and start-up/tare time (but not response time). It will also eat some memory.

Important: The HX711 sample rate can be set to 10SPS or 80SPS (samples per second) by pulling pin 15 high (80SPS) or low (10SPS), ref HX711 data sheet.
On fabricated HX711 modules there is usually a solder jumper on the PCB for pin 15 high/low. The rate setting can be checked by measuring the voltage on pin 15.
ADC noise is worst on the 80SPS rate. Unless very quick settling time is required, 10SPS should be the best sample rate for most applications.

Start up and tare: from start-up/reset, the tare function seems to be more accurate if called after a "pre-warm-up" period running conversions continuously for a few seconds. See example files.

Hardware and ADC noise:
Wires between HX711 and load cell should be twisted and kept as short as possible.
Most available HX711 modules seems to follow the reference design, but be aware that some modules are poorly designed with under-sized capacitors, and noisy readings.
The Sparkfun module seems to differ from most other available modules as it has some additional components for noise reduction. 

To get started: Install the library from Arduino Library Manager. Begin with the Calibration.ino example file, then move on to the Read_1x_load_cell.ino example file.
