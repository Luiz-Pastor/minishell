/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:55:37 by abarrio-          #+#    #+#             */
/*   Updated: 2024/02/20 10:44:57 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

// RGB color (with values from[0-255])
// for text	\x1B[38;2;R;G;Bm
// for background  \x1B[48;2;R;G;Bm

// color (with V from [0-255])
// for text \x1B[38;5;Vm
// for background \x1B[48;5;Vm

// 38 for costum color
// https://htmlcolorcodes.com/es/

// text color

# define C_RED				"\x1B[31m"
// #define GREEN			"\x1B[32m"
# define C_GREENFOSFI		"\x1B[38;2;17;245;120m"
// #define	PURPLE			"\033[0;35m"
// #define BLACK  			"\x1B[30m"
// #define YELLOW 			"\x1b[33m"
// #define BLUE   			"\x1b[34m"
// #define MAGENTA			"\x1b[35m"
# define C_CYAN   			"\x1b[36m"
// #define WHITE  			"\x1B[37m"
// #define ORANGE 			"\x1B[38;2;255;128;0m"
// #define ROSE   			"\x1B[38;2;255;151;203m"
// #define LBLUE  			"\x1B[38;2;53;149;240m"
// #define GRAY  			"\x1B[38;2;176;174;174m"
// #define GOLD				"\x1B[38;2;212;175;55m"

// // background color

// #define BG_BLACK  		"\x1B[40m"
// #define BG_RED    		"\x1B[41m"
// #define BG_GREEN  		"\x1B[42m"
// #define BG_YELLOW 		"\x1B[43m"
// #define BG_BLUE   		"\x1B[44m"
// #define BG_MAGENTA		"\x1B[45m"
// #define BG_CYAN   		"\x1B[46m"
// #define BG_WHITE  		"\x1B[47m"
// #define BG_ORANGE 		"\x1B[48;2;255;128;0m"
// #define BG_LBLUE  		"\x1B[48;2;53;149;240m"
// #define BG_GREENFOSFI 	"\x1B[48;2;17;245;120m"
// #define BG_GRAY   		"\x1B[48;2;176;174;174m"
// #define BG_ROSE  		"\x1B[48;2;255;151;203m"
// #define BG_GOLD			"\x1B[48;2;212;175;55m"

//text color

# define RED 0xFF0000
# define GREEN 0x00FF00
# define GREENFOSFI 0x11F578
# define PURPLE 0x800080
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define BLUE 0x0000FF
# define MAGENTA 0xFF00FF
# define CYAN 0x00FFFF
# define WHITE 0xFFFFFF
# define ORANGE 0xFF8000
# define ROSE 0xFF97CB
# define LBLUE 0x3595F0
# define GRAY 0xB0AEAE
# define GOLD 0xD4AF37

// Background color

# define BG_BLACK 0x000000
# define BG_RED 0xFF0000
# define BG_GREEN 0x00FF00
# define BG_YELLOW 0xFFFF00
# define BG_BLUE 0x0000FF
# define BG_MAGENTA 0xFF00FF
# define BG_CYAN 0x00FFFF
# define BG_WHITE 0xFFFFFF
# define BG_ORANGE 0xFF8000
# define BG_LBLUE 0x3595F0
# define BG_GREENFOSFI 0x11F578
# define BG_GRAY 0xB0AEAE
# define BG_ROSE 0xFF97CB
# define BG_GOLD 0xD4AF37

# define CLEAR "\033[0m"

#endif