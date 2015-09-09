#!/bin/bash
cd "$(dirname "$0")"
install_name_tool -change "liblua53.dylib" "@executable_path/liblua53.dylib" GAM200_Project 