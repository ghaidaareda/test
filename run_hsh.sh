#!/bin/bash

./hsh 2>&1 | sed 's/.*: No such file or directory/\.\/hsh: No such file or directory/'
