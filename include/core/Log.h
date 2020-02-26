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

#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

#include <memory>
#include <spdlog/spdlog.h>

class Log
{
public:
    Log(const Log &) = delete;
    void operator=(const Log &) = delete;
    virtual ~Log(void);

    static Log &log(void);

    inline std::shared_ptr<spdlog::logger> coreLogger() { return m_logger; }

private:
    Log(void);

    std::shared_ptr<spdlog::logger> m_logger;
};

#define LOG_ERROR(...) Log::log().coreLogger()->error(__VA_ARGS__)
#define LOG_WARN(...) Log::log().coreLogger()->warn(__VA_ARGS__)
#define LOG_INFO(...) Log::log().coreLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...) Log::log().coreLogger()->trace(__VA_ARGS__)

#endif // _CORE_LOG_H_
