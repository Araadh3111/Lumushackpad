# Lumuspad

A 5-key macropad with a rotary encoder, OLED screen and RGB underglow.
Based on HackClub's MacroPad Guide: https://hackpad.hackclub.com/guide

----------------------------------
What it does:-

- SW1: New tab (Ctrl+T)
- SW2: Cycles the OLED animation (Cyberpunk scanner / Equalizer / Stealth logo)
- SW3: Launches VS Code
- SW4: Opens YouTube in Brave
- SW5: Leaves the current call (Zoom / Teams / Discord)
- Knob: Volume up/down, press to mute
- 5x SK6812 RGB LEDs running a rainbow swirl

----------------------------------
File Structure:-

--CAD

  -luma_bottom_tray.step

  -luma_spacer.step

  -luma_switch_plate.step

  -luma_case_assembled.step

--Firmware (QMK, builds automatically via GitHub Actions -> .uf2)

  -keyboard.json

  -keymap.c

  -config.h

  -rules.mk

--PCB (schematics + pcb)

  -Luma pcb.kicad_pro / .kicad_sch / .kicad_pcb

----------------------------------
Schematic:-

Heres my schematic I forgot to organise :(

<img width="1918" height="1078" alt="Screenshot 2026-06-10 171732" src="https://github.com/user-attachments/assets/dd743aaf-9dbd-44a6-9534-21997aae61de" />


PCB:-
Here is my pcb I imported the silkscreen from pinterest then used inbuilt image converter to copy it and paste it on the pcb
<img width="1918" height="1078" alt="Screenshot 2026-06-10 171314" src="https://github.com/user-attachments/assets/d0124367-176a-4c26-a277-385636e77f26" />
<img width="1917" height="1078" alt="image" src="https://github.com/user-attachments/assets/6914d570-de36-4b3b-97ca-eef4bb36b984" />


Case:-
here is my case, I was aiming for one cyberpunkish case and made it its screwable from the corners(m3 screws)
<img width="1918" height="1031" alt="Screenshot 2026-06-10 184015" src="https://github.com/user-attachments/assets/1b725197-a6c8-4eb8-8dbc-55cf225d29a7" />

Assembled:-
here is the assembled file! (ps: the pins will be bended!)
<img width="1191" height="881" alt="image" src="https://github.com/user-attachments/assets/30720314-2865-4ba8-b271-b76198c6f535" />

---------------------------------
Ai usage:-
I used claude to help me make the qmk firmware! rest build was done by me
----------------------------------
BOM:-

-1x Seeed XIAO RP2040

-5x MX-style Switches

-5x DSA Keycaps

-1x EC11 Rotary Encoder (with push button)

-1x 0.91" 128x32 OLED Display (I2C)

-5x SK6812 MINI RGB LEDs

-1x Resistor (RGB data line)

-5x 100nF Capacitors and one μF Capacitor in the pcb

-1x Case (3 printed parts: bottom tray, spacer, switch plate)

No diodes needed — every switch has its own pin (direct wiring).

refer to BOM.CSV
+ pcb printing fund

----------------------------------
Firmware:-

Compiled automatically by GitHub Actions on every push.
Grab the latest lumuspad_firmware artifact from the Actions tab,
hold the BOOT button on the XIAO while plugging in USB,
and drag the .uf2 onto the RPI-RP2 drive.
----------------------------------
