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
#include "timestamp.h"
using namespace std;
vector<Region> regions;
void commandLoop();
void runCommand(string command);
int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <server.log>" << endl;
    return 1;
  }
  char interactive;
  if (argc == 3) { 
    interactive = 0;
  } else {
    interactive = 1;
    cout << "Loading log file (this may take a while)" << endl;
  }
  std::string line;
  std::ifstream text (argv[1]);
  int regionnum = 0;
  int success = 0;
  if (text.is_open()) {
    while (text.good()) { // Read file line by line
      getline(text,line);
      float x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0; // Region corners
      int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; // Time
      char player[16] = "none", mat[50] = "none", mat2[50] = "none", world[32] = "world"; // Things
      //Replace              Time                             Player      World       Material           Corner 1       Corner 2
      sscanf (line.c_str(), "%d-%d-%d %d:%d:%d [INFO] WorldEdit: %s (in \"%[^\"]\"): /replace %s %s - Region: (%f, %f, %f) - (%f, %f, %f)", 
	      &year, &month, &day, &hour, &min, &sec, player, world, mat, mat2, &x1, &y1, &z1, &x2, &y2, &z2);
      if (strstr(mat2, "none") == NULL) { // It is replace
      if(__builtin_expect((x1+x2+y1+y2+z1+z2) != 0, 0)) {
	  success = 1;
	  Location one, two;
	  one.x = x1; one.y = y1; one.z = z1;
	  two.x = x2; two.y = y2; two.z = z2;
      __builtin_prefetch(&one, 1, 1);
      __builtin_prefetch(&two, 1, 1);
	  Timestamp ts;
	  ts.year = year; ts.month = month; ts.day = day;
	  ts.hour = hour; ts.min = min; ts.sec = sec;
	  stringstream op; op << "replaced " << mat << " with " << mat2;
	  Region reg(world, player, op.str(), ts, one, two);
	  regions.push_back(reg);
	}
	continue;
      }
      //Set                  Time                             Player      World       Material           Corner 1       Corner 2
      sscanf (line.c_str(), "%d-%d-%d %d:%d:%d [INFO] WorldEdit: %s (in \"%[^\"]\"): /set %s - Region: (%f, %f, %f) - (%f, %f, %f)", 
	      &year, &month, &day, &hour, &min, &sec, player, world, mat, &x1, &y1, &z1, &x2, &y2, &z2);
      if (strstr(mat, "none") == NULL) { // It is set      
	if ((x1+x2+y1+y2+z1+z2) != 0) {
	  success = 1;
	  Location one, two;
	  one.x = x1; one.y = y1; one.z = z1;
	  two.x = x2; two.y = y2; two.z = z2;
	  Timestamp ts;
	  ts.year = year; ts.month = month; ts.day = day;
	  ts.hour = hour; ts.min = min; ts.sec = sec;
	  stringstream op; op << " set to material " << mat;
	  Region reg(world, player, op.str(), ts, one, two);
	  regions.push_back(reg);
	}
	continue;
      }
    }
    text.close();
    if (!success) {
      cerr << "Could not find any WorldEdit commands in the file (it should be your regular server log file). " <<
	"Have you enabled WorldEdit command logging in the configuration? (plugins/WorldEdit/config.yml)" << endl;
      return 1;
    }
    if (interactive) commandLoop();
    if (!interactive) runCommand(argv[3]);
    //if (interactive) cout << "Final memory: " << sizeof(regions) << " bytes" << endl;
    return 0;
  } else {
    cerr << "Unable to open the file " << argv[1] << "." << endl;
  }
}
void commandLoop() {
  cout << "Loaded in " << ((float)clock())/CLOCKS_PER_SEC << " seconds" << endl;
  while (1) {
    cout << "Continue (y/n, default y)> ";
    char opt[16] = "y";
    __builtin_prefetch(opt);
    scanf("%s", opt);
    if (strcmp(opt, "n") == 0) {
      break;
    }
    cout << "World> ";
    char world[16] = "none";
    scanf("%s", world);
    if (strcmp(world, "none") == 0) {
      cout << "Bad input" << endl;
      continue;
    }
    cout << "Player> ";
    char player[16] = "none";
    scanf("%s", player);
    if (strcmp(player, "none") == 0) {
      cout << "Bad input" << endl;
      continue;
    }
    cout << "X Y Z> ";
    float x = 1234, y = 5678, z = 9101;
    scanf("%f %f %f", &x, &y, &z);
    if (x+y+z == 16013) {
      cout << "Bad input" << endl;
      continue;
    }
    // cout << "Radius> ";
    // int radius = 0;
    // scanf("%d", &radius);
    // if (radius == 0) {
    //   cout << "Bad input" << endl;
    //   continue;
    // }
    // TODO: add time option
    // cout << "Time (amount space days/hours/minutes)> ";
    // int radius = 0;
    // char unit[16] = "none";
    // scanf("%d %s", &radius);
    // if (radius == 0 || strcmp(unit, "none") == 0) {
    //   cout << "Bad input" << endl;
    //   continue;
    // }
    cout << "Searching..." << endl; 
    Location loc; loc.x = x; loc.y = y; loc.z = z;
    for (int i = 0; i < regions.size(); i++) {
      Region reg = regions.at(i);
      if (reg.hasLocation(loc)) {
	cout << ts2str(reg.ts) << "  (in " << reg.world << ") " << reg.player << " " << reg.operation << endl;
      }
    }
  }
}
void runCommand(std::string cmd) {
  float x = 1234, y = 5678, z = 9101;
  sscanf(cmd.c_str(), "%f %f %f", &x, &y, &z);
  if (__builtin_expect((x == 1234) && (y == 5678) && (z == 9101), 0)) {
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
