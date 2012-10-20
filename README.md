Introduction
------------
WELog is a program designed as a sort of "WorldEdit LogBlock". It parses server log files for WorldEdit commands and re-creates the changes virtually. Then, via a interactive command line environment, you can search for any block change made by someone using WorldEdit.  
It does not roll back edits made by WorldEdit. I recommend using the "snapshot" feature of WorldEdit to restore.
Usage
-----
WorldEdit command logging must be enabled first!  
Either compile the code in the repository with `make` first or download a binary from the downloads section.  
WELog runs off your normal server.log file. That is the parameter required when running.  
Copy the `welog` executable to your server's root directory and run `./welog server.log`
License
-------
WELog is licensed under the GNU GPL version 3. A copy of this license is available in "LICENSING".  
Copying and distribution of this file, with or without modification, are permitted in any medium without royalty provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.
