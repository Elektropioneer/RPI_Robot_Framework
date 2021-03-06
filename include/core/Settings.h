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

#ifndef _CORE_SETTINGS_H_
#define _CORE_SETTINGS_H_

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Settings
{
public:
    Settings(void);
    virtual ~Settings(void);

    inline json &jsonSettings(void) { return m_json; }

private:
    json m_json;

    static const char *s_settingsPath;
};


#endif // _CORE_SETTINGS_H_
