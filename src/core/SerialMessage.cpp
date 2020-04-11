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

#include "core/SerialMessage.h"

#define ESC         0x1B
#define STX         0x02
#define ETX         0x03

SerialMessage::SerialMessage(void)
{
    m_message.push_back(ESC);
    m_message.push_back(STX);
    m_message.push_back(0x00);
    m_message.push_back(0x00);
    m_message.push_back(ESC);
    m_message.push_back(ETX);
}

SerialMessage::SerialMessage(const std::initializer_list<uint8_t> &msg)
{
    m_message.push_back(ESC);
    m_message.push_back(STX);
    for (auto b : msg)
    {
        m_message.push_back(b);
    }
    m_message.push_back(ESC);
    m_message.push_back(ETX);
}

SerialMessage::~SerialMessage(void)
{
}

uint8_t SerialMessage::getCommand1(bool *ok) const
{
    if (m_message.size() < 3)
    {
        if (ok)
        {
            *ok = false;
        }

        return 0;
    }

    if (ok)
    {
        *ok = true;
    }

    return m_message[2];
}

uint8_t SerialMessage::getCommand2(bool *ok) const
{
    if (m_message.size() < 4)
    {
        if (ok)
        {
            *ok = false;
        }

        return 0;
    }

    if (ok)
    {
        *ok = true;
    }

    return m_message[2];
}

uint8_t SerialMessage::at(int index, bool *ok) const
{
    if (m_message.size() <= index)
    {
        if (ok)
        {
            *ok = false;
        }

        return 0;
    }

    if (ok)
    {
        *ok = true;
    }

    return m_message[index];
}

bool SerialMessage::set(int index, uint8_t value)
{
    if (m_message.size() <= index)
    {
        return false;
    }

    m_message[index] = value;

    return true;
}

bool SerialMessage::append(uint8_t value)
{
    m_message.insert(m_message.end() - 3, value);
    return true;
}

void SerialMessage::iterate(const std::function<void (uint8_t)> &callback) const
{
    for (auto msg : m_message)
    {
        callback(msg);
    }
}

SerialMessage &operator<<(SerialMessage &msg, uint8_t data)
{
    msg.append(data);
    return msg;
}
