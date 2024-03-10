#!/bin/bash

nm -a "${1}" > nm_out; ./ft_nm -a "${1}" > ft_out; diff nm_out ft_out