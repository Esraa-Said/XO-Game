#                   XO Game
We will introduce XO game using microcontroller (**tm4c123gh6pm**) **Tiva-C LaunchPad** 

<img src = "./images/tivaC.png"/>

## Hardware I/O connections

the project can run on simulator directly `keil for example`

for using hardware, these components can be used: 

- Tiva C launchPad
- Nokia5110 Screen (Blue)
- Breadboard
- Resistors
- 3 Leds
- Jumbers (connectors)
- 2 switches

#### Blue Nokia 5110 Connections

|           Signal          |           (Nokia 5110) LaunchPad pin          |
| ------------------------- | --------------------------------------------- |
|           Reset           |           (RST, pin 1) connected to PB7       |
|           SSI0Fss         |           (CE,  pin 2) connected to PB3       |
|           Data/Command    |           (DC,  pin 3) connected to PB6       |
|           SSI0Tx          |           (Din, pin 4) connected to PB5       |
|           SSI0Clk         |           (Clk, pin 5) connected to PB2       |
|           3.3V            |           (Vcc, pin 6) power                  |
|           back light      |           (BL,  pin 7) not connected          |
|           Ground          |           (Gnd, pin 8) ground                 |

#### Other connections

| component        | (Nokia 5110) LaunchPad pin  |
| ---------------- | --------------------------- |
| move switch      |   PB0                       |
| update switch    |   PB1                       |
| first player led |   PB2                       |
| second player led|   PB3                       |
| update led       |   PB7                       |


## Game veiws



<p align="center">start game 
</p>
<p align="center">
        <img src = "./images/splashScreen.png"/>
</p>


<p align="center">X take turn  </p>

<p align="center">
<img src = "./images/tunrX.png"/>
</p>


<p align="center"> O take turn   </p>

<p align="center">
<img src = "./images/turnO.png"/>
</p>

<p align="center">  X wins   </p>

<p align="center">
<img src = "./images/winnerX.png"/>
</p>

<p align="center"> O wins   </p>

<p align="center">
<img src = "./images/winnerO.png"/>
</p>

<p align="center"> Draw   </p>

<p align="center">
<img src = "./images/draw.png"/>
</p>

<p align="center"> Play agian?    </p>

<p align="center">
<img src = "./images/play_again.png"/>
</p>

<p align="center"> End Game   </p>

<p align="center">
<img src = "./images/end_game.png"/>
</p>


## Team Members
- Mahmoud Essam 
- Mahmoud Mohamed
- Khaled Ramadan
- Samar Mahmoud 
- Esraa Said 