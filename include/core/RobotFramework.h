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

#ifndef _CORE_ROBOT_FRAMEWORK_H_
#define _CORE_ROBOT_FRAMEWORK_H_

#include <vector>
#include <lua.hpp>

#include "core/LuaPositionEntry.h"
#include "core/LuaTimerEntry.h"

class RobotFramework
{
public:
    RobotFramework(int argc, char *argv[]);
    virtual ~RobotFramework(void);

    int run(void);

private:
    void loadScript(void);
    void extractPositions(void);
    void extractTimers(void);

    lua_State *m_lua;
    std::vector<LuaPositionEntry> m_luaPositionEtries;
    std::vector<LuaTimerEntry> m_luaTimerEntries;
};

#endif // _CORE_ROBOT_FRAMEWORK_H_
