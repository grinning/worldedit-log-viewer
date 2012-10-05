/*
    WELog
    Copyright (C) 2012 Connor Monahan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef WELOG_REGION_H
#define WELOG_REGION_H
#include <string>
struct Location {
  std::string world;
  int x;
  int y;
  int z;
};
class Region {
 public:
  std::string world;
  Location one;
  Location two;
  Region(std::string world, Location one, Location two);
  char hasLocation(Location loc);
  Location getMinXBlock();
  Location getMinYBlock();
  Location getMinZBlock();
  int getMinX();
  int getMinY();
  int getMinZ();
  Location getMaxXBlock();  
  Location getMaxYBlock();
  Location getMaxZBlock();
  int getMaxX();
  int getMaxY();
  int getMaxZ();
  int getSizeX();
  int getSizeY();
  int getSizeZ();
  

};
#endif
