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

#ifndef _CORE_SERIAL_MESSAGE_H_
#define _CORE_SERIAL_MESSAGE_H_

#include <vector>
#include <initializer_list>
#include <cstdint>

class SerialMessage
{
public:
    SerialMessage(void);
    SerialMessage(const std::initializer_list<uint8_t> &msg);
    ~SerialMessage(void);

    uint8_t getCommand1(bool *ok = nullptr);
    uint8_t getCommand2(bool *ok = nullptr);
    uint8_t at(int index, bool *ok = nullptr);
    bool set(int index, uint8_t value);

private:
    std::vector<uint8_t> m_message;
};

#endif // _CORE_SERIAL_MESSAGE_H_
