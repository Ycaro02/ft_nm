#!/bin/bash

nm "$@" 2> /dev/null | wc -l
./ft_nm "$@" 2> /dev/null | wc -l