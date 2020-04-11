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

#ifndef _CORE_SERIAL_H_
#define _CORE_SERIAL_H_

#include <string>
#include <functional>
#include <unordered_map>
#include <thread>
#include <mutex>

#include "SerialMessage.h"

class Serial
{
public:
    Serial(const Serial &) = delete;
    void operator=(const Serial &) = delete;
    ~Serial(void);

    static Serial &serial(void);

    bool open(void);
    bool close(void);

    bool send(const SerialMessage &msg);
    SerialMessage sendReceive(const SerialMessage &msg);

    void subscribe(uint8_t cmd1, uint8_t cmd2, const std::function<void(const SerialMessage &msg)> &callback);

private:
    Serial(void);
    void startAsyncReader(void);

    static const std::string s_port;
    static const int s_baud;
    static const int s_readBufferMaxSize;

    int m_fd;

    std::unordered_map<uint16_t, std::function<void(const SerialMessage &msg)>> m_readWaitCallbacks;
    std::unordered_map<uint16_t, std::function<void(const SerialMessage &msg)>> m_readSubscribeCallbacks;

    std::thread m_readerThread;
    std::mutex m_readerMutex;

    std::vector<uint8_t> m_readBuffer;
    uint8_t m_readBufferSize;
};

#endif // _CORE_SERIAL_H_
