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

class Serial
{
public:
    Serial(const Serial &) = delete;
    void operator=(const Serial &) = delete;
    ~Serial(void);

    Serial &serial(void);

    inline void setBlocking(bool blocking) { m_blocking = blocking; }

    bool open(void);
    bool close(void);

    bool send(uint8_t msg);
    bool sendReceive(uint8_t msg, bool &ok);

private:
    Serial(void);

    bool m_blocking;
    std::function<void(uint8_t )> m_receiveCallback;
};

#endif // _CORE_SERIAL_H_
