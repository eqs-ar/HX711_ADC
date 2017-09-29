
The is an Arduino library for the HX711 24-bit ADC for weight scales.
Data retrival is done without halting the mcu, also with 10SPS rate setting and it also allows for multiple HX711's performing conversions simultaniously. 
 
"Moving average" method from a rolling data set combined with removal of high/low outliers is used for filtering and smoothing the retrived value.

Selectable values in the .h file:
- Moving average data set of 4, 8, 16, 32, 64 or 128 samples (default 16). 
- Ignore high outlier; one sample is added to the data set, the peak high value of all samples in the data set is ignored (default 1)
- Ignore low outlier; one sample is added to the data set, the peak low value of all samples in the data set is ignored (default 1)

Caution: using a higher number of samples will reduce ADC noise but will also increase settling and startup/tare time (but not response time). It will also eat chunks of your memory.

The HX711 sample rate can be set to 10SPS or 80SPS (samples per second) by pulling pin 15 high (80SPS) or low (10SPS), ref HX711 data sheet. 
On fabricated modules there is usually a solderjumper on the PCB for pin 15 high/low. The rate setting can be checked by measuring the voltage on pin 15.
ADC noise is worst on the 80SPS rate. Unless very quick settling time is required, 10SPS should be the best sample rate for most applications.

Start up and tare; from start-up/reset, the tare function seems to be more accurate if called after a "pre-warmup" period running conversions continiously for a few seconds. See example files.

Hardware and ADC noise:
Wires between HX711 and load cell should be twisted and as kept as short as possible.
Most available HX711 modules seems to follow the reference design, but be aware that some modeles are poorly designed with under-sized capacitors, and very noisy readings. 
The Sparkfun module seems to differ from most other available modules as it has some additional components for noise reduction. 
 