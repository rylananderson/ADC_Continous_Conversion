# ADC Continuous Conversion Driver

## Overview
*	Convert data from Analog to Digital and receive the transmitted data using the UART communication protocol.
*	ADC module configured for single channel continuous conversion mode.
*	Includes the UART RX/TX driver to make it easy to communicate data from sensor to microcontroller.

## Dependencies
*	STM32F4 Datasheet, Reference Manual, and Nucleo64 Board User manual
*	CMSIS header files
*	Realterm Serial/TCP Terminal <br/>
[Datasheet]: Search “STM32F4[your version] Datasheet” <br/>
[Reference Manual]: Search “STM32F4[your version] Reference Manual” <br/>
[Nucleo64 Board User Manual]: Search “Nucleo64 Board User Manual” <br/>
** Always download from ST Microelectronics 


## Steps for Getting CMSIS Header Files
*	Go to st.com and navigate to the home page. Once there click on the search bar at the top of the page and search for “stm32f4”
*	Filter the results by clicking on the “Tools and Software” tab located at the top left corner of the search screen.
*	The software package download should be the fourth option down from the top. Check to make sure the Part Number is STM32CubeF4, Status is Active, Type is Embedded Software, Category is Mcu mpu embedded software, and the description is as follows: “STM32Cube MCU Package for STM32F4 series (HAL, Low-Layer APIs and CMSIS, USB, TCP/IP, File system, RTOS, Graphic - and examples running on ST boards)”
*	Download this software package, extract the Zip file, rename it to chip headers, and place it inside of your project folder

## Steps for Including CMSIS Header Files Inside Project
*	Inside the Cube IDE, over on the left side of the screen on the file explorer, right click on the project name and click “properties”
*	Within in the property’s menu, navigate to C/C++ General, then click Paths and Symbols
*	In the Paths and Symbols menu, make sure the “Include” tab is selected
*	In the Include tab, click Add, File System, and paste the path to your chip headers folder for both the include folders that exist in this software package.
*	In the Symbols tab, you will need to add a symbol for your version of the STM32F4 you are using. (Ex: STM32F4446RE)

## Installation and Setup
*	Download the package, open the files in STM32 CubeIDE and make sure to follow the instructions above to set up and include the CMSIS header files in your project
*	Open the Src folder and write your code in the “main.c”, “uart.c” or “adc.c” files.
*	Add your own C files to the source folder and remember to include them in the “Include” file.
*	Hardware: Connect a jumper wire to PA1 (see Nucleo64 Board User Manual to find this location on your board) and then plug into the sensor you are using. Note: For simple test connect PA1 to ground (GND) on the Nucleo Board.




