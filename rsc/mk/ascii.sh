#!/bin/bash

source rsc/sh/color.sh

ascii_nm() {
	#BLOCK
    # echo -e "${LIGHT_CYAN} .-----------------.\t .----------------. ${RESET}"
    # echo -e "${LIGHT_CYAN}| .--------------. |\t| .--------------. |${RESET}"
    # echo -e "${LIGHT_CYAN}| | ____  _____  | |\t| | ____    ____ | |${RESET}"
    # echo -e "${LIGHT_CYAN}| ||_   \|_   _| | |\t| ||_   \  /   _|| |${RESET}"
    # echo -e "${LIGHT_CYAN}| |  |   \ | |   | |\t| |  |   \/   |  | |${RESET}"
    # echo -e "${LIGHT_CYAN}| |  | |\ \| |   | |\t| |  | |\  /| |  | |${RESET}"
    # echo -e "${LIGHT_CYAN}| | _| |_\   |_  | |\t| | _| |_\/_| |_ | |${RESET}"
    # echo -e "${LIGHT_CYAN}| ||_____|\____| | |\t| ||_____||_____|| |${RESET}"
    # echo -e "${LIGHT_CYAN}| |              | |\t| |              | |${RESET}"
    # echo -e "${LIGHT_CYAN}| '--------------' |\t| '--------------' |${RESET}"
    # echo -e "${LIGHT_CYAN} '----------------' \t '----------------' ${RESET}"

	# Varsity
	# echo -e " ${LIGHT_CYAN} ____  _____   ____    ____  ${RESET}"
	# echo -e " ${LIGHT_CYAN}|_   \|_   _| |_   \  /   _| ${RESET}"
	# echo -e " ${LIGHT_CYAN}  |   \ | |     |   \/   |   ${RESET}"
	# echo -e " ${LIGHT_CYAN}  | |\ \| |     | |\  /| |   ${RESET}"
	# echo -e " ${LIGHT_CYAN} _| |_\   |_   _| |_\/_| |_  ${RESET}"
	# echo -e " ${LIGHT_CYAN}|_____|\____| |_____||_____| ${RESET}"
	# echo -e " ${LIGHT_CYAN}                             ${RESET}"

	# ANSI Regular
	echo -e "  ${LIGHT_CYAN}                        ${RESET}"
	echo -e "  ${LIGHT_CYAN}███    ██    ███    ███ ${RESET}"
	echo -e "  ${LIGHT_CYAN}████   ██    ████  ████ ${RESET}"
	echo -e "  ${LIGHT_CYAN}██ ██  ██    ██ ████ ██ ${RESET}"
	echo -e "  ${LIGHT_CYAN}██  ██ ██    ██  ██  ██ ${RESET}"
	echo -e "  ${LIGHT_CYAN}██   ████    ██      ██ ${RESET}\n"
}





ascii_nmtester() {
	echo -e ""
	echo -e "${LIGHT_MAGENTA}███    ██    ███    ███    ████████    ███████    ███████    ████████    ███████    ██████  ${RESET}"
	echo -e "${LIGHT_MAGENTA}████   ██    ████  ████       ██       ██         ██            ██       ██         ██   ██ ${RESET}"
	echo -e "${LIGHT_MAGENTA}██ ██  ██    ██ ████ ██       ██       █████      ███████       ██       █████      ██████  ${RESET}"
	echo -e "${LIGHT_MAGENTA}██  ██ ██    ██  ██  ██       ██       ██              ██       ██       ██         ██   ██ ${RESET}"
	echo -e "${LIGHT_MAGENTA}██   ████    ██      ██       ██       ███████    ███████       ██       ███████    ██   ██ ${RESET}\n"
}

if [ "$1" == "ft_nm" ]; then
	ascii_nm
else
	ascii_nmtester
fi