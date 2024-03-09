#!/bin/bash

source rsc/sh/color.sh

ascii_nm() {
    echo -e "${LIGHT_CYAN} .-----------------.\t .----------------. ${RESET}"
    echo -e "${LIGHT_CYAN}| .--------------. |\t| .--------------. |${RESET}"
    echo -e "${LIGHT_CYAN}| | ____  _____  | |\t| | ____    ____ | |${RESET}"
    echo -e "${LIGHT_CYAN}| ||_   \|_   _| | |\t| ||_   \  /   _|| |${RESET}"
    echo -e "${LIGHT_CYAN}| |  |   \ | |   | |\t| |  |   \/   |  | |${RESET}"
    echo -e "${LIGHT_CYAN}| |  | |\ \| |   | |\t| |  | |\  /| |  | |${RESET}"
    echo -e "${LIGHT_CYAN}| | _| |_\   |_  | |\t| | _| |_\/_| |_ | |${RESET}"
    echo -e "${LIGHT_CYAN}| ||_____|\____| | |\t| ||_____||_____|| |${RESET}"
    echo -e "${LIGHT_CYAN}| |              | |\t| |              | |${RESET}"
    echo -e "${LIGHT_CYAN}| '--------------' |\t| '--------------' |${RESET}"
    echo -e "${LIGHT_CYAN} '----------------' \t '----------------' ${RESET}"
}

ascii_nm