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

static void _stackDump(lua_State *L);                   // For debugging

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
    lua_getglobal(m_lua, "__references__");

    for (auto entry : m_luaPositionEtries)
    {
        luaL_unref(m_lua, -1, entry.callbackLuaRef);
    }

    for (auto entry : m_luaPositionEtries)
    {
        luaL_unref(m_lua, -1, entry.callbackLuaRef);
    }

    if (m_lua)
    {
        lua_close(m_lua);
    }
}

int RobotFramework::run(void)
{
    LOG_INFO("Service start");

    lua_getglobal(m_lua, "__references__");
    for (auto entry : m_luaPositionEtries)
    {
        lua_rawgeti(m_lua, -1, entry.callbackLuaRef);
        int status = lua_pcall(m_lua, 0, 1, 0);
        if (status != LUA_OK)
        {
            LOG_ERROR("Error while executeing lua funtions: ", status);
            break;
        }
        if (!lua_toboolean(m_lua, -1))
        {
            break;
        }
        lua_pop(m_lua, 1);
    }
    lua_pop(m_lua, 1);

    LOG_INFO("Service end");

    return 0;
}

void RobotFramework::loadScript(void)
{
    std::string scriptName = "test.lua";

    luaL_dofile(m_lua, scriptName.c_str());

    lua_newtable(m_lua);
    lua_setglobal(m_lua, "__references__");

    extractPositions();
    extractTimers();
}

void RobotFramework::extractPositions(void)
{
    lua_getglobal(m_lua, "__references__");
    lua_getglobal(m_lua, "positions");
    lua_pushnil(m_lua);
    while (lua_next(m_lua, -2))
    {
        LuaPositionEntry entry;

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.x = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 2);
        lua_gettable(m_lua, -2);
        entry.y = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 3);
        lua_gettable(m_lua, -2);
        entry.callbackLuaRef = luaL_ref(m_lua, 1);

        m_luaPositionEtries.push_back(entry);
        lua_pop(m_lua, 1);
    }
    lua_pop(m_lua, 1);
    lua_pop(m_lua, 1);
}

void RobotFramework::extractTimers(void)
{
    lua_pop(m_lua, 1);
    lua_pop(m_lua, 1);

    lua_getglobal(m_lua, "__references__");
    lua_getglobal(m_lua, "positions");
    lua_pushnil(m_lua);
    while (lua_next(m_lua, -2))
    {
        LuaTimerEntry entry;

        lua_pushnumber(m_lua, 1);
        lua_gettable(m_lua, -2);
        entry.tick = static_cast<int>(lua_tonumber(m_lua, -1));
        lua_pop(m_lua, 1);

        lua_pushnumber(m_lua, 3);
        lua_gettable(m_lua, -2);
        entry.callbackLuaRef = luaL_ref(m_lua, 1);

        m_luaTimerEntries.push_back(entry);
        lua_pop(m_lua, 1);
    }
    lua_pop(m_lua, 1);
    lua_pop(m_lua, 1);
}

static void _stackDump(lua_State *L)
{
    int i=lua_gettop(L);
    printf(" ----------------  Stack Dump ----------------\n" );
    while(  i   ) {
    int t = lua_type(L, i);
    switch (t) {
    case LUA_TSTRING:
        printf("%d:`%s'\n", i, lua_tostring(L, i));
        break;
    case LUA_TBOOLEAN:
        printf("%d: %s\n",i,lua_toboolean(L, i) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        printf("%d: %g\n",  i, lua_tonumber(L, i));
        break;
    default: printf("%d: %s\n", i, lua_typename(L, t)); break;
    }
        i--;
    }
    printf("--------------- Stack Dump Finished ---------------\n" );
}
