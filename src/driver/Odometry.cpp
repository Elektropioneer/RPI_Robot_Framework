/* 
 * This file is part of the RPI Robot Framework distribution (https://github.com/Elektropioneer/RPI_Robot_Framework).
 * Copyright (c) 2020 Miloš Zivlak (milos.zivlak@sensa-group.net).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "driver/Odometry.h"

#include "core/Serial.h"

#define _ODOMETRY_COMMAND_1         'o'
#define _ODOMETRY_COMMAND_2         'd'

#define _ODOMETRY_CMD               _ODOMETRY_COMMAND_1, _ODOMETRY_COMMAND_2

Odometry::Odometry(void)
{
}

Odometry::Odometry::~Odometry(void)
{
}

OdometryStatus Odometry::getInfo(void)
{
}

bool Odometry::setMaxSpeed(int speed)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'V';
    msg << (uint8_t)(speed & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::setPosition(int x, int y, int orientation)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'I';
    msg << (uint8_t)((x >> 8) & 0xFF);
    msg << (uint8_t)(x & 0xFF);
    msg << (uint8_t)((y >> 8) & 0xFF);
    msg << (uint8_t)(y & 0xFF);
    msg << (uint8_t)((angle >> 8) & 0xFF);
    msg << (uint8_t)(angle & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::hardStop(void)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'S';

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::softStop(void)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 's'

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::moveForward(int distance)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'D';
    msg << (uint8_t)((distance >> 8) & 0xFF);
    msg << (uint8_t)(distance & 0xFF);
    msg << (uint8_t)(DirectionForward);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::moveBackward(int distance)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'D';
    msg << (uint8_t)((distance >> 8) & 0xFF);
    msg << (uint8_t)(distance & 0xFF);
    msg << (uint8_t)(DirectionBackward);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::rotate(int angle)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'T';
    msg << (uint8_t)((angle >> 8) & 0xFF);
    msg << (uint8_t)(angle & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::rotateAbsolute(int angle)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'A';
    msg << (uint8_t)((angle >> 8) & 0xFF);
    msg << (uint8_t)(angle & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::gotoXY(int x, int y, int speed, Direction direction)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'Q';
    msg << (uint8_t)((x >> 8) & 0xFF);
    msg << (uint8_t)(x & 0xFF);
    msg << (uint8_t)((y >> 8) & 0xFF);
    msg << (uint8_t)(y & 0xFF);
    msg << (uint8_t)(speed & 0xFF);
    msg << (uint8_t)(direction & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}

bool Odometry::arc(int xc, int yc, int fi, Direction direction)
{
    Serial &serial = Serial::serial();
    SerialMessage msg{ _ODOMETRY_CMD };

    msg << 'Q';
    msg << (uint8_t)((xc >> 8) & 0xFF);
    msg << (uint8_t)(xc & 0xFF);
    msg << (uint8_t)((yc >> 8) & 0xFF);
    msg << (uint8_t)(yc & 0xFF);
    msg << (uint8_t)((fi >> 8) & 0xFF);
    msg << (uint8_t)(fi & 0xFF);
    msg << (uint8_t)(direction & 0xFF);

    if (!serial.send(msg))
    {
        return false;
    }
}
