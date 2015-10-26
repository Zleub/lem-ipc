#!/bin/sh
git submodule init ;
git submodule update ;

env ;
unset CFLAGS ;
unset CC ;
unset MAKEFLAGS ;
unset MFLAGS ;
(cd glfw && cmake . && make) ;
