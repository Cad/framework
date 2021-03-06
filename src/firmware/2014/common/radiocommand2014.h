/***************************************************************************
 *   Copyright 2015 Michael Eischer                                        *
 *   Robotics Erlangen e.V.                                                *
 *   http://www.robotics-erlangen.de/                                      *
 *   info@robotics-erlangen.de                                             *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   any later version.                                                    *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef COMMON_RADIOCOMMAND2014_H
#define COMMON_RADIOCOMMAND2014_H

#include <stdint.h>

static const uint8_t robot2014_address[] = { 0xAA, 0xC0, 0xFF, 0xEE, 0x40 };

static const int16_t RADIOCOMMAND2014_V_MAX = 32767;
static const int16_t RADIOCOMMAND2014_OMEGA_MAX = 32767;
static const uint8_t RADIOCOMMAND2014_KICK_MAX = 255;
static const uint8_t RADIOCOMMAND2014_DRIBBLER_MAX = 100;

typedef struct
{
    uint8_t counter;
    uint8_t shot_power;
    uint8_t chip:1;
    uint8_t charge:1;
    uint8_t standby:1;
    uint8_t id:4;
    uint8_t force_kick:1;
    int8_t dribbler;
    int16_t v_x; // mm/s
    int16_t v_y; // mm/s
    int16_t omega; // mrad/s
} __attribute__ ((packed)) RadioCommand2014;

typedef struct
{
    uint8_t counter;
    uint8_t id:4;
    uint8_t power_enabled:1;
    uint8_t motor_in_power_limit:1;
    uint8_t ball_detected:1;
    uint8_t cap_charged:1;
    uint8_t battery;
    uint8_t packet_loss;
    // valid if main_active
    int16_t v_s; // mm/s
    int16_t v_f; // mm/s
    int16_t omega; // mrad/s
} __attribute__ ((packed)) RadioResponse2014;

#endif // COMMON_RADIOCOMMAND2014_H
