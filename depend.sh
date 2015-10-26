#!/bin/sh
git submodule init
git submodule update
cd glfw && cmake . && make
