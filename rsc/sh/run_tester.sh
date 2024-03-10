#!/bin/bash

if [ ! -d "ft_nmTester" ]; then
	git clone https://github.com/Ycaro02/ft_nmTester.git
fi
./ft_nmTester/call_tester.sh 0
./ft_nmTester/call_tester.sh 1
./ft_nmTester/call_tester.sh 0 1
./ft_nmTester/call_tester.sh 1 1
./ft_nmTester/call_tester.sh 1 1 1