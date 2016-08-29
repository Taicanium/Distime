# Distime

This program takes input from the user on a planetary system, and based on this data calculates the distortion of time (Time Dilation) relative to two observers at different positions in the system.

There are differing forms of time dilation which are all caused by different things, including motion of the observers, motion of the planets they stand on, and mass of the planets they stand on. The data that is required to calculate total time dilation using this program is as follows:

- Mass of each planet (and the star) in E-notation (base * 10^exponent, NOT base^exponent)
- Distance of each planet from the center of the system (including the star)
- Orbital speed of each planet around the center of the system (The program will ask you for the orbital speed of the star; I subtlely recommend entering 0)
- The planet of reference for a "local" observer
- The planet of reference for a "control" observer (not to be confused with the "coordinate" observer, which is a theoretical observer who has a distortion of 0, and whom we are measuring the distortion against)
- Distance of the local observer from the center of their planet of reference (keep in mind, 0 will cause a divide-by-zero error; this will NOT crash the program as far as I know, but it will cause the numbers at the end to display incorrectly)
- Distance of the control observer from the center of their planet of reference
- Speed of the local observer relative to their planet; if the observer is in a vehicle moving at 3 m/s, enter 3.
- Speed of the control observer relative to their planet

Distances should be in meters.
Speeds should be in meters per second.
The numbers that are output are formatted as the number of seconds that pass for the coordinate observer for every second that passes for the local or control observer: If the output for the local observer is 1.009, then for every second that passes for the local observer, 1.009 seconds pass for the coordinate observer.

Unless otherwise specified, all numbers should be in their raw forms. The program will tell you when to use E-notation; if it doesn't, enter the entire number including all zeros.

A text file is included with the release, containing information for the solar system that can be copied and pasted into the program. If you choose to use this file, all you need to type in is the reference bodies, distances from the reference bodies, and observer speeds.

Some useful information:

An observer on the surface of the earth would be 6371000 meters from its center.
The speed of light in a vacuum is 299792458 meters per second.
Ninety-nine percent of the speed of light in a vacuum is about 296794533 meters per second.