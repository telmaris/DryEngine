#!/bin/bash
cmake --debug-output -S . -B build/
cd build/
MSBuild.exe DryEngine.sln
