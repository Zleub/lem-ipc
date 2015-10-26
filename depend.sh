#!/bin/sh
git submodule init ;
git submodule update ;

env ;
(cd glfw && cmake . && unset CFLAGS ; unset CC ; env ; make) ;
