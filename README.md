[![Linux and Mac Build Status](https://travis-ci.com/romatrix/glopp.svg?branch=master)](https://travis-ci.com/romatrix/glopp)

glopp - the fast, smart log explorer
=====================================

glopp is a multi-platform GUI application that helps browse and search
through long and complex log files.  It is designed with programmers and
system administrators in mind and can be seen as a graphical, interactive
combination of grep and less.

## Main features inherited from glogg

* Runs on Unix-like systems
* Provides a second window showing the result of the current search
* Reads UTF-8 and ISO-8859-1 files
* Supports grep/egrep like regular expressions
* Colorizes the log and search results
* Displays a context view of where in the log the lines of interest are
* Is fast and reads the file directly from disk, without loading it into memory
* Is open source, released under the GPL

## Features of glopp (not officially relased, still on branch)
* Python plugin support, that allowes: custom search option egrep based, like context of found lines, removing of chosen columns, redirecting search results to new tab and work on it like regular file, do another search, etc
* Marking lines in selection
* Filters selecting only on matching pattern
* Option of copying file from toolbar
* Adding line number option while copying selected line




