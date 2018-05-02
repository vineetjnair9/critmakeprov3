#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <IRremote.h> // Include the IRremote library

/* Connect the output of the IR receiver diode to pin 11. */
#define RECV_PIN 5;
#define SEND_PIN 9;
/* Initialize the irrecv part of the IRremote  library */
IRrecv irrecv(RECV_PIN, SEND_PIN);
decode_results results; // This will store our IR received codes

IRsend irsend; // Enables IR transmit on pin 9

void setup() {
     Serial.begin(9600);
     irrecv.enableIRIn(); // Start the receiver
     Serial.println("Enter a word or a phrase:");
   }

   void loop() {
      if (Serial.available() > 0) {
          serialinput = Serial.read();
      }
      /*then i want here to use an irsend to put the serialinput and send it, 
      via ir to the other arduino 
      and see it in the serial monitor of the receiver. */
      // something like this: irsend.sendSony(serialinput, 20)
      }
   }


// setup() initializes serial and the Infrared receiver.
void setup()


// loop() checks for a received IR code.
void loop()
{
  if (irrecv.decode(&results)) 
}

