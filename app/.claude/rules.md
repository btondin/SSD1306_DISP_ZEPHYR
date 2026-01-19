# Project Rules - Zephyr RTOS Development

## Context7 Usage

Always use context7 for any Zephyr RTOS related queries including:

- Kernel APIs and configuration
- Device drivers (GPIO, I2C, SPI, UART, etc.)
- Threading and scheduling
- Memory management
- Device Tree configuration
- Kconfig options
- Build system (CMake, West)

Automatically invoke Context7 tools without requiring explicit "use context7" in prompts.

## Project Context

This is a Zephyr RTOS project for SSD1306 OLED display driver.

- Target: nRF52832 (custom board files located in C:\nordic\myboards\boards\Bruno\bruno_nrf52832)
- Display: SSD1306 OLED (128x64 monochrome)
- Communication: I2C or SPI (configurable)
- Based on: ST7789V driver architecture, adapted for monochrome OLED

## File Access Rules

- Automatically allow read access to files within the folder: C:\nordic\myboards\boards\Bruno\bruno_nrf52832
- Never modify any file outside the folder: C:\nordic\myapps\SSD1306_DISP_ZEPHYR
- **NEVER modify the file: src/main.c** - This file must remain unchanged under all circumstances
