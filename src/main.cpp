// #include <Arduino.h>
// #include "SmartServoBus.hpp"
// #include "robotka.h"
// #include "arm_commands.h"

// void setup()
// {
//     rkConfig cfg;
//     rkSetup(cfg);
//     servoBus.begin(1, UART_NUM_1, GPIO_NUM_27);
//     servoBus.setAutoStop(0, true);

//     while (true)
//     {
//         if (rkButtonIsPressed(BTN_UP))
//         {
//             test();
//         }
//     }
// }

#include <Arduino.h>
#include "SmartServoBus.hpp"
#include "robotka.h"
#include "arm_commands.h"
#include "motors_commands.h"
///////////////////////
float g_US = 1;

///////////////////////
void encodery()
{
    Serial.printf("L: %f, R: %f", rkMotorsGetPositionLeft(), rkMotorsGetPositionRight());
    // rkMotorsGetPositionLeft();
    // rkMotorsGetPositionRight();
}
void Skoback()
{
    forward(1000);
    turn(90);
    forward(450);
    turn(90);
    forward(500);
    turn(-90);
    forward(400);
    turn(-90);
    forward(850);
}

void update_sensors()
{
    g_US = rkUltraMeasure(1);
    printf(" g_US: %f \n", g_US);
    // std::cout << " " << std::endl;
}

//////////////////
void setup()
{
    rkConfig cfg;
    rkSetup(cfg);
    servoBus.begin(1, UART_NUM_1, GPIO_NUM_27);
    servoBus.setAutoStop(0, true);
    // ceka na stisknuti up, pak zacne program
    while (true)
    {
        if (rkButtonIsPressed(BTN_UP))
        {
            break;
        }
    }

    /////////////////////////////////////
    while (true)
    {
        // printf("state= %u \n", state);
        delay(20);
        switch (state)
        {
        case 1:
            state = 2;
            // jizda eskem
            arm_up();
            back_button();
            forward(500);
            state = 3;
            break;
        case 3:
            state = 4;
            // jizda eskem
            curve(150, 180, 5, true);
            break;
        case 5:
            state = 6;
            // jizda eskem
            forward(50);
            state = 7;
            break;
        case 7:
            state = 8;
            // jizda eskem
            curve(150, 150, 9, false);
            break;
        case 9:
            state = 10;
            forward(1750);
            // otocka do hriste
            turn_by_wall();
            // jizda doprostred hriste
            forward(550);
            turn(-90);
            back_button();
            // jizda pro kostku
            forward(700);
            //tady se rozhodne na jakou barvu robot pojede 
            // tady se pozna barva a pojede se do spravneho pole
            back_button();
            // jizda zpet ke zdi nakonec eska
            forward(220);
            turn(93);
            back_button();
            forward(50);
            turn(75);
            back_button();
            // cesta z rohu eskem zpet
            forward(100);
            turn_by_wall();
            back_button();
            forward(300);
            state = 11;
            break;
        case 11:
            state = 12;
            // musi se dopocitat
            curve(150, 90, 13, true);
            break;
        case 13:
            state = 14;
            // musi se dopocitat
            curve(150, 180, 15, true);
            break;
        case 15:
            state = 16;
            forward(500);
            state = 17;
            break;
        }
    }
}