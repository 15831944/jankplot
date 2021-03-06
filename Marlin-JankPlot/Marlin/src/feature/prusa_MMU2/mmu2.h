/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "../../inc/MarlinConfig.h"

struct E_Step;

class MMU2 {
public:
  MMU2();

  static void init();
  static void reset();
  static void mmuLoop();
  static void toolChange(uint8_t index);
  static void toolChange(const char* special);
  static uint8_t getCurrentTool();
  static void setFilamentType(uint8_t index, uint8_t type);

  #if HAS_LCD_MENU && ENABLED(MMU2_MENUS)
    static bool unload();
    static void loadFilament(uint8_t);
    static void loadAll();
    static bool loadFilamentToNozzle(uint8_t index);
    static bool ejectFilament(uint8_t index, bool recover);
  #endif

private:
  static bool rx_str_P(const char* str);
  static void tx_str_P(const char* str);
  static void tx_printf_P(const char* format, int argument);
  static void tx_printf_P(const char* format, int argument1, int argument2);
  static void clear_rx_buffer();

  static bool rx_ok();
  static bool rx_start();
  static void checkVersion();

  static void command(const uint8_t cmd);
  static bool getResponse(void);
  static void manageResponse(bool move_axes, bool turn_off_nozzle);

  #if HAS_LCD_MENU && ENABLED(MMU2_MENUS)
    static void loadToNozzle();
    static void filamentRamming();
    static void executeExtruderSequence(const E_Step * sequence, int steps);
  #endif

  static void filamentRunout();

  static bool enabled, ready, mmu_print_saved;
  static uint8_t cmd, cmd_arg, last_cmd, extruder;
  static int8_t state;
  static volatile int8_t finda;
  static volatile bool findaRunoutValid;
  static int16_t version, buildnr;
  static millis_t next_request, next_response;
  static char rx_buffer[16], tx_buffer[16];
};

extern MMU2 mmu2;
