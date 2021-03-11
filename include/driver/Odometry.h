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

#ifndef _DRIVER_ODOMETRY_H_
#define _DRIVER_ODOMETRY_H_

#include <initializer_list>
#include <cstdint>

struct OdometryStatus
{
  int x;
  int y;
  int angle;
  int status;
  bool ok;
};

class Odometry
{
public:
  Odometry(void);
  virtual ~Odometry(void);

  enum Direction
  {
    DirectionForward = 1,
    DirectionBackward = -1
  };

  OdometryStatus getInfo(void);

  bool setMaxSpeed(int speed);
  bool setPosition(int x, int y, int orientation);

  bool hardStop(void);
  bool softStop(void);

  OdometryStatus moveForward(int distance);
  OdometryStatus moveBackward(int distance);
  OdometryStatus rotate(int angle);
  OdometryStatus rotateAbsolute(int angle);
  OdometryStatus gotoXY(int x, int y, int speed, Direction direction);
  OdometryStatus arc(int xc, int yc, int fi, Direction direction);

  void endMatch(void);

private:
  bool waitUntilDone(OdometryStatus *odometryStatus = nullptr);
};

#endif // _DRIVER_ODOMETRY_H_
