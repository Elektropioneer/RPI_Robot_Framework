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

#include "core/RobotFramework.h"

#include <iostream>                                     // TODO: Only for debug

#include "core/Log.h"

RobotFramework::RobotFramework(int argc, char *argv[])
    : m_lua(nullptr)
{
    LOG_INFO("Initialization start");

    m_lua = luaL_newstate();
    loadScript();

    LOG_INFO("Initialization end");
}

RobotFramework::~RobotFramework(void)
{
    if (m_lua)
    {
        lua_close(m_lua);
    }
}

int RobotFramework::run(void)
{
    LOG_INFO("Service start");

    for (auto posEntry : m_luaPositionEtries)
    {
        /*
         * TODO: Go to x, y and call lua function
         */
    }

    LOG_INFO("Service end");

    return 0;
}


void RobotFramework::loadScript(void)
{
    std::string scriptName = "test.lua";

    luaL_dofile(m_lua, scriptName.c_str());

    extractPositions();
    extractTimers();
}

void RobotFramework::extractPositions(void)
{
    lua_getglobal(m_lua, "positions");
    lua_pushnil(m_lua);
    while (lua_next(m_lua, -2))
    {
        LuaPositionEntry entry;

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.x = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.x = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.callback = lua_tostring(m_lua, -1);
        lua_pop(m_lua, 1);

        m_luaPositionEtries.push_back(entry);
        lua_pop(m_lua, 1);
    }
}

void RobotFramework::extractTimers(void)
{
    lua_getglobal(m_lua, "timers");
    lua_pushnil(m_lua);
    while (lua_next(m_lua, -2))
    {
        LuaPositionEntry entry;

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.x = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.x = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.callback = lua_tostring(m_lua, -1);
        lua_pop(m_lua, 1);

        m_luaPositionEtries.push_back(entry);
        lua_pop(m_lua, 1);
    }
}
