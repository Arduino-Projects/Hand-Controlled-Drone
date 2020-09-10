# Hand Controlled Drone
A drone built on a custom-made PCB that follows your hand orientation!


# What does it do
- There is a hidden custom-made PCB inside a glove that the pilot wears
- The pilot then simply tilts their hand in the intended direction of flight
- Using an onboard accelerometer, and a flex sensor, an ATMEGA328P chip is able to identify its orientation, and the requested throttle level
- Using an onboard high power radio module, the glove sends radio signals to the drone
- The drone then reads in the hand orientation coordinates through a radio on the drone's PCB
- It then converts those values into a PID loop, which processes the results, and outputs the appropriate RPM for each motor in a PWM signal
- The PWM signals are then sent to ESC's, which draw current from the battery and spin the motors up!


# How was it built
- The PCB's were made using the EasyEDA PCB editor, and ordered through JLCPCB
- The PCB Components were ordered through LCSC Electronics
- Everything was hand-soldered, and programmed manually


# Recent update
- It was flying perfectly in my school's field at a few hundred feet of height
- Then, when coming in for landing, I may have descended too fast, and landed harshly on one of the arms
- The arm broke off the drone, and it's currently not in flying condition


# Images
