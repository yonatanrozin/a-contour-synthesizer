# A Contour Synthesizer (in progress)
A musical interface that uses the shapes of objects to create and modify sound

## Introduction
Contour Synthesizer is the final project for my New Interfaces for Musical Expression and Interaction Design courses, in which physical interfaces are designed, built and used to create sound and digital interfaces are designed and built in Max/MSP, respectively. The sound synthesis performed by this project is based heavily off the contents of a third course, Hacking Audio Hardware, in which analog synthesizers are built that generate sounds from scratch.

The synthesizer receives input from 2 sources. The first is a standard MIDI keyboard/controller that sends pitch and velocity (volume, essentially) information to a Max/MSP interface, which synthesizes a note from scratch using the input from the second source: a custom-made physical interface consisting of a series of 16 resistive strips. Each of these vertical strips outputs the uppermost edge of any weight placed on top of it. When combining the data gathered from the 16 strips, the upper edge of an object can be recreated fairly accurately on screen. 

Once outputted to Max/MSP, the contour line created by this data can be used to modify sound in a number of ways. The first and most simple method is to apply an amplitude envelope. In this method, the line acts as a function of volume over time. For example, an ascending diagonal line ( / ) will create notes that begin from nothing and grow louder. A V shape will create notes that start loud and then rapidly soften and louden again. A horizontal line will produce notes that stay at a single volume.

The second method is to use the line as a graph of overtone data to perform additive synthesis. Overtones -pitches that sound simultaneously to the main "fundamental" pitch at a softer volume, whose frequency is a function of the frequency of the fundamental pitch -are produced by multiplying the fundamental frequency by 2, 3, 4, etc. Using the line data, the amplitude of these frequencies can be made a function of the position of the line at a certain point. For example, the same ascending diagonal line ( / ) will create a note with louder high overtones than lower ones, producing a thin, brittle sound. The opposite ( \ ) will create a note with more lower overtones, producing a richer, deeper texture.

The third and most unpredictable method is to use the line data as the waveform of the sound itself. In sound synthesis, the shape of a sound wave (a function of the pressure of the air it travels through over time) has a profoud effect on its timbre. For example, a sine wave produces the most pure and smooth sounding pitch. Waveforms with sharp corners such as square waves and especially sawtooth waves generate sharper, more harsh sounding pitches. A waveform visualization can be found [here](https://en.wikipedia.org/wiki/Square_wave#/media/File:Waveforms.svg) for reference. When custom waveforms are used, the timbre of the resulting pitch is an unpredictable function of the features of the wave. Using the contour of a shape as a custom waveform is therefore guaranteed to produce interesting and varied timbral results.

Finally, using simultaneous Max for Live patches, the incoming line data can be routed to a number of tracks in Ableton Live, each with their own amp envelope, additive synth and waveform data, allowing a variety of "instruments" to be played and manipulated simultaneously. 

## Physical Interface

The physical interface uses an Arduino wired to 16 analog circuits, each of which consists of a length of conductive rubber cord suspended over a strip of copper tape. The rubber cords are wired to voltage while the copper strips are grounded. The 2 components never touch until a weight is placed on the cable, lowering it down until it makes contact with the tape, completing the circuit. Since the cord is highly resistive to current, the current exiting the circuit will vary depending on how far up the cord the point of contact was made. The contour of an object placed on a surface can be extrapolated by placing these points on a graph and connecting the dots.

![A schematic of an Arduino Nano 33 IoT wired to 16 circuits in parallel, each consisting of a transistor and a variable 1-2kΩ resistor. The collector of each transistor is wired to 3.3v, the base is wired to pins D2-D17 through a fixed 4.7kΩ resistor and the variable resistor is wired to pin A17. Pin A17 is additionally wired to ground through another fixed 4.7kΩ resistor.](https://github.com/yonatanrozin/a-contour-synthesizer/blob/main/Images/Contour%20Synth%20Schematic.jpg)

**edit: in the schematic above, the label A17 should read A7 and the range of Rs should read ≈0-2kΩ.**

Since each circuit produces an analog (non-binary) signal, the circuits need to output to a single analog pin, since the Arduino Nano 33 IoT only has 7 and the number of circuits is 16. To accomplish this, a series of digital pins, of which the Arduino Nano has 20, enable and disable a series of transistors one at a time so the resistance on their corresponding analog circuit can be measured. This prevents the circuits from interfering with each other, even though they're all wired to the same pin.

## Materials

### Hardware

- A 1x1' sheet of 1/4" thick acrylic, cut and engraved using the attached [Adobe Illustrator file](https://github.com/yonatanrozin/a-contour-synthesizer/blob/main/Contour%20Synth%201.ai)
 - For engraving: 10% speed, 60% power (low speed to achieve a deep engraving - pause between slots to prevent acrylic warping)
 - For cutting: 12% speed, 100% power, 5000DPI
- 32 inline wire connectors, such as the ones harvested from these [terminal blocks](https://www.mcmaster.com/touch-safe-terminal-blocks/for-wire-gauge~12/wire-connection-type~screw-clamp-terminals/current-per-circuit~20a/length~1-3-16/)
- Roughly 9ft of 6mm-wide copper tape
- Roughly 4m of [conductive rubber stretch sensor](https://www.adafruit.com/product/519)
- An [Arduino Nano 33 IoT](https://store-usa.arduino.cc/products/arduino-nano-33-iot)
- 16 general purpose NPN transistors, such as [these](https://www.onsemi.com/pdf/datasheet/2n3903-d.pdf)

### Software

- [Max/MSP](https://cycling74.com/products/max)
- [Ableton Live](https://www.ableton.com/en/)
- The [Arduino IDE](https://www.arduino.cc/en/software)
