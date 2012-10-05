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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include "region.h"
using namespace std;
  vector<Region> regions;
//long lineCount(string file);
void commandLoop();
void runCommand(string command);
int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " <logfile> <worldname> [command]" << endl;
    return 1;
  }
  char interactive;
  if (argc == 4) { 
    interactive = 0;
  } else {
    interactive = 1;
    /*  cout << "WELog  Copyright (C) 2012  Connor Monahan" << endl;
    cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'." << endl;
    cout << "This is free software, and you are welcome to redistribute it" << endl;
    cout << "under certain conditions; type `show c' for details." << endl;
*/  }
  std::string line;
  std::ifstream text (argv[1]);
  int regionnum = 0;
  if (text.is_open()) {
    while (text.good()) {
      getline(text,line);
      float x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0;
      char plr[16] = "npe", mat[50] = "";
      stringstream read;
      read << "%s (in \"" << argv[2] << "\"): /set %s - Region: (%f, %f, %f) - (%f, %f, %f)";
      sscanf (line.c_str(), read.str().c_str(), plr, mat, &x1, &y1, &z1, &x2, &y2, &z2);
      if ((x1+x2+y1+y2+z1+z2) != 0) {
	Location one, two;
	one.x = x1; one.y = y1; one.z = z1;
	two.x = x2; two.y = y2; two.z = z2;
	stringstream ss; ss << plr << " set to material " << mat;
	Region reg(ss.str(), one, two);
	regions.push_back(reg);
	//cout << regionnum++ << ": Player "<<plr<<" set "<<mat<<" at " << x1 << ' ' << y1 << ' ' << z1 << "   " << x2 << ' ' << y2 << ' ' << z2 << endl;
      }
    }
    text.close();
    if (interactive) commandLoop();
    if (!interactive) runCommand(argv[3]);
    if (interactive) cout << "Final memory: " << sizeof(regions) << " bytes" << endl;
  } else {
    std::cout << "Unable to open file" << std::endl << std::endl;
  }
}
void commandLoop() {
  char active = 1;
  while (active) {
    cout << "X Y Z> ";
    float x = 1234, y = 5678, z = 9101;
    scanf("%f %f %f", &x, &y, &z);
    //    cin >> x; cout << "Y> "; cin >> y; cout << "Z> "; cin >> z;
    if ((x == 1234) && (y == 5678) && (z == 9101)) {
      cout << "Bad input, guessing that means exit..." << endl;
      return;
    }
    cout << endl << "Searching at X" << x << " Y"<<y<<" Z"<<z<<"..."<<endl; 
    Location loc; loc.x = x; loc.y = y; loc.z = z;
    for (int i = 0; i < regions.size(); i++) {
      Region reg = regions.at(i);
      if (reg.hasLocation(loc)) {
	cout << reg.world << endl;
      }
    }
  }
}
void runCommand(std::string cmd) {
  float x = 1234, y = 5678, z = 9101;
  sscanf(cmd.c_str(), "%f %f %f", &x, &y, &z);
  if ((x == 1234) && (y == 5678) && (z == 9101)) {
    return;
  }
  Location loc; loc.x = x; loc.y = y; loc.z = z;
  for (int i = 0; i < regions.size(); i++) {
    Region reg = regions.at(i);
    if (reg.hasLocation(loc)) {
      cout << reg.world << endl;
    }
  }
}
/*
long lineCount(string file) {
  std::ifstream text (file);
  int lc = 0;
  string line;
  if (text.is_open()) {
    while (text.good()) {
      getline(text,line);
      lc++;
    }
  }
  return lc;
}
*/
