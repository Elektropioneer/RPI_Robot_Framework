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

#include "core/Serial.h"

#include <chrono>
#include <wiringSerial.h>

#define _COM_ESC            0x1B
#define _COM_STX            0x02
#define _COM_ETX            0x03

const std::string Serial::s_port = "/dev/ttyUSB0";
const int Serial::s_baud = 9600;
const int Serial::s_readBufferMaxSize = 100;

Serial::Serial(void)
    : m_fd(0),
      m_readBuffer(s_readBufferMaxSize),
      m_readBufferSize(0)
{
}

Serial::~Serial(void)
{
}

Serial &Serial::serial(void)
{
    static Serial serial;
    return serial;
}

bool Serial::open(void)
{
    m_fd = serialOpen(s_port.c_str(), 9600);
    if (m_fd < 0)
    {
        m_fd = 0;
        return false;
    }

    startAsyncReader();

    return true;
}

bool Serial::close(void)
{
    std::unique_lock<std::mutex> lock(m_readerMutex);
    serialClose(m_fd);
    return true;
}

bool Serial::send(const SerialMessage &msg)
{
    std::unique_lock<std::mutex> lock(m_readerMutex);
    msg.iterate([&] (uint8_t m) {
        serialPutchar(m_fd, m);
    });
    return true;
}

SerialMessage Serial::sendReceive(const SerialMessage &msg)
{
    std::unique_lock<std::mutex> lock(m_readerMutex);

    bool readed = false;
    SerialMessage response;

    m_readWaitCallbacks[msg.getCommand1() << 8 | msg.getCommand2()] = [&] (const SerialMessage &res) {
        response = res;
        readed = false;
    };

    msg.iterate([&] (uint8_t m) {
        serialPutchar(m_fd, m);
    });

    int maxIterations = 100;
    while (!readed)
    {
        using namespace std::chrono_literals;

        lock.unlock();
        std::this_thread::sleep_for(5ms);
        lock.lock();

        maxIterations--;
        if (maxIterations < 0)
        {
            m_readWaitCallbacks.erase(msg.getCommand1() << 8 | msg.getCommand2());
            break;
        }
    }

    return response;
}

void Serial::subscribe(uint8_t cmd1, uint8_t cmd2, const std::function<void (const SerialMessage &)> &callback)
{
    std::unique_lock<std::mutex> lock(m_readerMutex);
    m_readSubscribeCallbacks[cmd1 << 8 | cmd2] = callback;
}

void Serial::startAsyncReader(void)
{
    m_readerThread = std::thread([&] () {
        using namespace std::chrono_literals;

        int data = serialGetchar(m_fd);
        if (data != -1)
        {
            m_readBuffer[m_readBufferSize] = static_cast<uint8_t>(data);
            m_readBufferSize++;

            if ((m_readBufferSize == 1 && m_readBuffer[0] != _COM_ESC) ||
                (m_readBufferSize == 2 && m_readBuffer[1] != _COM_STX) ||
                (m_readBufferSize > 1 && m_readBuffer[0] != _COM_ESC && m_readBuffer[1] != _COM_STX) ||
                (m_readBufferSize >= s_readBufferMaxSize))
            {
                m_readBufferSize = 0;
                return;
            }

            if (m_readBufferSize > 2 && m_readBuffer[m_readBufferSize - 2] == _COM_ESC && m_readBuffer[m_readBufferSize - 1] == _COM_STX) 
            {
                m_readBuffer[0] = _COM_ESC;
                m_readBuffer[1] = _COM_STX;
                m_readBufferSize = 2;
            }

            if (m_readBufferSize > 1)
            {
                if (m_readBuffer[m_readBufferSize - 2] == _COM_ESC && m_readBuffer[m_readBufferSize - 1] == _COM_ETX)
                {
                    std::unique_lock<std::mutex> lock(m_readerMutex);
                    uint16_t key = m_readBuffer[2] << 8 | m_readBuffer[3];

                    SerialMessage msg({m_readBuffer[2], m_readBuffer[3]});
                    for (uint8_t i = 4; i < m_readBufferSize - 2; i++)
                    {
                        msg << m_readBuffer[i];
                    }

                    if (m_readWaitCallbacks.find(key) != m_readWaitCallbacks.end())
                    {
                        m_readWaitCallbacks[key](msg);
                        m_readWaitCallbacks.erase(key);
                    }
                    if (m_readSubscribeCallbacks.find(key) != m_readSubscribeCallbacks.end())
                    {
                        m_readSubscribeCallbacks[key](msg);
                    }
                }
            }
        }
        std::this_thread::sleep_for(5ms);
    });
}
