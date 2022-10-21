#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);
InterruptIn button(BUTTON1);
DigitalOut led(LED1);
DigitalOut interLED(LED2);
EventQueue q((32 * EVENTS_EVENT_SIZE));
Thread thread;

void lcdText(){
    uLCD.color(GREEN);
    uLCD.printf("\nThe program has \nbeen interupted!\n");
}

void flash(){
    interLED =! interLED;
    // to be called immediately by queue
    q.call(lcdText);
}

int main()
{
    thread.start(callback(&q, &EventQueue::dispatch_forever));
    button.rise(&flash); //interupt when the button is pressed
    while (true) {
        led =! led;
        ThisThread::sleep_for(1s);
    }
}

