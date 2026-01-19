# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)
set(BOARD bruno_nrf52832_nrf52832)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ssd1306_display)

target_sources(app PRIVATE src/main.c)
set(ssd1306_128x64)
