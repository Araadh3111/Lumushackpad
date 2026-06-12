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

(paste schematic screenshot here)

PCB:-

(paste PCB screenshot here)

Case:-

(paste case render here)

----------------------------------
BOM:-

-1x Seeed XIAO RP2040

-5x MX-style Switches

-5x DSA Keycaps

-1x EC11 Rotary Encoder (with push button)

-1x 0.91" 128x32 OLED Display (I2C)

-5x SK6812 MINI RGB LEDs

-1x Resistor (RGB data line)

-6x 100nF Capacitors

-1x Case (3 printed parts: bottom tray, spacer, switch plate)

No diodes needed — every switch has its own pin (direct wiring).

----------------------------------
Firmware:-

Compiled automatically by GitHub Actions on every push.
Grab the latest lumuspad_firmware artifact from the Actions tab,
hold the BOOT button on the XIAO while plugging in USB,
and drag the .uf2 onto the RPI-RP2 drive.
