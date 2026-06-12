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

<img width="1918" height="1078" alt="Screenshot 2026-06-10 171732" src="https://github.com/user-attachments/assets/dd743aaf-9dbd-44a6-9534-21997aae61de" />


PCB:-

<img width="1918" height="1078" alt="Screenshot 2026-06-10 171314" src="https://github.com/user-attachments/assets/d0124367-176a-4c26-a277-385636e77f26" />
<img width="1918" height="1078" alt="Screenshot 2026-06-10 181058" src="https://github.com/user-attachments/assets/9ad145b0-6f9f-4df6-a94d-e99155c95f49" />


Case:-

<img width="1918" height="1031" alt="Screenshot 2026-06-10 184015" src="https://github.com/user-attachments/assets/1b725197-a6c8-4eb8-8dbc-55cf225d29a7" />


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
----------------------------------
