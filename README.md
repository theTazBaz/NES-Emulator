# 🕹️ NES Emulator – Cycle-Accurate Nintendo Entertainment System Simulation

A low-level emulator that recreates the **Nintendo Entertainment System (NES)** by simulating its core hardware components — including the CPU, PPU, APU, and memory buses — with cycle accuracy. Built entirely in **C++** with **SDL2** for rendering and input, the project demonstrates deep understanding of hardware-level operations and operating system concepts like memory-mapped I/O, interrupt handling, and timing synchronization.

---

## 📌 Features

- 🧠 **Cycle-Accurate 6502 CPU Emulation**: Supports all instructions, addressing modes, and hardware interrupts (IRQ, NMI).
- 🖼️ **PPU Graphics Rendering**: Emulates sprite/background rendering, palettes, scrolling, and NTSC timing.
- 🔊 **APU Audio Synthesis**: Implements all 5 NES audio channels with waveform mixing and audio output.
- 🧩 **Memory-Mapped I/O**: Recreates the NES memory map with accurate address decoding and device interaction.
- 🎮 **Controller Support**: Uses SDL2 to simulate NES controller input from keyboard or gamepad.
- 🛠️ **Debugging Tools**: Integrated tools for inspecting registers, stepping through instructions, and testing components.

---

## 🧪 Performance

| Game Title          | Compatibility | Average FPS | Audio Accuracy |
|---------------------|---------------|-------------|----------------|
| Super Mario Bros.   | ✅ Full        | 60 FPS      | High           |
| The Legend of Zelda | ✅ Full        | 60 FPS      | High           |
| Donkey Kong         | ✅ Full        | 60 FPS      | High           |

---

## 🛠️ Tech Stack

- **Language**: C++
- **Graphics/Input**: SDL2
- **Debugging**: GDB
- **Docs/Specs**: 6502 CPU Manual, NESDev Wiki
- **Testing**: Test ROMs, Reference Games (e.g., Super Mario Bros.)

---
