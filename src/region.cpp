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
#include "region.h"
#include <iostream>
Region::Region(std::string world, Location one, Location two) {
  this->world = world;
  this->one = one;
  this->two = two;
  //  std::cout << one.x << ' ' << two.x << std::endl;
}
char Region::hasLocation(Location loc) {
  int x = loc.x, y = loc.y, z = loc.z;
  return x <= this->getMaxX() && x >= this->getMinX() && y <= this->getMaxY() && y >= this->getMinY() && z <= this->getMaxZ() && z >= this->getMinZ();  
}
Location Region::getMinXBlock() {
  if (this->one.x < this->two.x) {
    return one;
  }
  return two;
}

Location Region::getMinYBlock() {
  if (this->one.y < this->two.y) {
    return one;
  }
  return two;
}

Location Region::getMinZBlock() {
  if (this->one.z < this->two.z) {
    return one;
  }
  return two;
}

int Region::getMinX() {
  return this->getMinXBlock().x;
}

int Region::getMinY() {
  return this->getMinYBlock().y;
}

int Region::getMinZ() {
  return this->getMinZBlock().z;
}

Location Region::getMaxXBlock() {
  if (this->one.x < this->two.x) {
    return two;
  }
  return one;
}

Location Region::getMaxYBlock() {
  if (this->one.y < this->two.y) {
    return two;
  }
  return one;
}

Location Region::getMaxZBlock() {
  if (this->one.z < this->two.z) {
    return two;
  }
  return one;
}

int Region::getMaxX() {
  return this->getMaxXBlock().x;
}

int Region::getMaxY() {
  return this->getMaxYBlock().y;
}

int Region::getMaxZ() {
  return this->getMaxZBlock().z;
}

int Region::getSizeX() {
  return this->getMaxX() - this->getMinX() + 1;
}

int Region::getSizeY() {
  return this->getMaxY() - this->getMinY() + 1;
}

int Region::getSizeZ() {
  return this->getMaxZ() - this->getMinZ() + 1;
}
