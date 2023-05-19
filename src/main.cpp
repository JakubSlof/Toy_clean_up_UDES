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
    // jizda eskem
    arm_up();
    back_button();
    forward(500);
    curve(150, 180, true);
    forward(50);
    curve(150, 150, false);
    // jizda od eska do hriste
    forward(1950);
    // otocka do hriste
    turn_by_wall();
    // jizda doprostred hriste
    forward(500);
    turn(-90);
    back_button();
    // jizda pro kostku
    forward(800);
    // tady se pozna barva a pojede se do spravneho pole
    back_button();
    // jizda zpet ke zdi nakonec eska
    forward(220);
    turn(93);
    back_button();
    forward(50);
    turn(75);
    back_button();
}