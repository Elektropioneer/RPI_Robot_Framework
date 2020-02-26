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

#include "core/Log.h"

#include <spdlog/sinks/basic_file_sink.h>

#include "core/Settings.h"

Log::Log(void)
{
    /*
     * TODO: Implement logg levl configuration (using map)
     */
    try
    {
        auto settings = Settings().jsonSettings()["Logging"];
        std::string logName = settings["Name"];
        std::string logFile = settings["File"];
        //std::string logLevel = settings["Level"];

        m_logger = spdlog::basic_logger_mt(logName, logFile);
        m_logger->set_level(spdlog::level::trace);
    }
    catch (...)
    {
    }
}

Log::~Log(void)
{
}

Log &Log::log(void)
{
    static Log log;
    return log;
}
