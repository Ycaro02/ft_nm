#!/bin/bash

BIN=$1

nm ${BIN} | cut -d ' ' -f 1,3 > nm_out ; ./ft_nm ${BIN} | cut -d ' ' -f 1,3 > out ; diff out nm_out && echo Diff ok
rm nm_out out