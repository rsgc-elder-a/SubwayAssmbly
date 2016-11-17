/*
Author: Andrew Elder
Teacher: Mr D'arcy
Course: TEI4M
*/

uint8_t data = 2;
uint8_t clock = 3;
uint8_t latch = 4;

uint8_t shiftOuut = 0b101010101;




void setup() {
  // put your setup code here, to run once:
  asm(
    "setup: \n"

    "ser r30\n" //sets all the bits high in R 30
    "out 0x0A, r30\n" //sets all the I/O pins to output
    //hex B is the port D address for turning on pins

    //    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    //    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    //
    //    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    //    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    //
    //    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch
    //    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch
    //    "ldi r16, 0xAA \n\t rcall delay \n" // delay
    //    "rcall delay \n" // delay

    "intz: \n"
    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch
    //    "ldi r17, 8 \n"//loups for on register
    //68 works for some reason?
    //"ldi r18, 0b10100010 \n" //value for shift out
    "lds 18, shiftOuut \n"
    "ldi r20, 128 \n" //value and mask

    "comp: \n"
    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    "rcall delay \n" // delay

    //will be what ever you want to shift with either data low or high
    "tst r20 \n"
    "breq end \n"
    "mov r19, r18 \n" //coping register
    "and r19, r20 \n" //anding to get sing bit
    "breq zero \n" //if zero branch
    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    "lsr r20 \n" //divde by 2
    "rjmp clockend \n"

    "zero: \n"
    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    "lsr r20 \n" //divde by 2
    "clockend: \n"

    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    "rcall delay \n" // delay
    "rjmp comp \n" //go back for anothe rround

    "delay:\n" //allows to jump to line
    "dec r8\n" //takes one aways from r8 from 255
    "brne delay\n" //jumps back to delay if r8 is not 0
    "dec r9\n" //takes one aways from r9 from 255
    "brne delay\n"  //jumps back to delay if r9 is not 0
    "ret\n"  //returns back to where delay was called

    "end: \n"

    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch

  );



}

void loop() {
  // put your main code here, to run repeatedly:

}