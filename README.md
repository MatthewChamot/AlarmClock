# AlarmClock
Simple alarm clock | Work in progress.

A library has been written for the 7 segment display to control current draw from the Teensy LC < 5mA.

The alarm has been coded to work completely off of interrupts by using interval timer.  The alarm plays the beginning of Midnight City by M83 in a square wave tone.  One speaker for the bass, the other for the treble part.  The initial idea was to use the DAC on the Teensy but it had a low current output and was not outputting a full 3.3 V.

Because of the interrupt driven speakers, the 7 segment display and both speakers can run simultaneously.


#### Future Work
* Code for a button needs to be written.

* One button to control alarm on/off, snooze, set time and set alarm functionality.

* Time is controlled through delays, may need to upgrade to a RTC.
