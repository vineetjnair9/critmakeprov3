int irledPin = 13; // choose the pin for the IR emettor
int ledPin = 12; // choose the pin for the green LED
int inPin = 6;   // choose the input pin (for a pushbutton)
int val_button = 0;     // variable for reading the pin status
int val_ir = 0;     // variable for reading the pin status

void setup() {
  Serial.begin(9600);
  pinMode(irledPin, OUTPUT);  // declare IR emittor as output
  pinMode(ledPin, OUTPUT);  // declare green LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
  pinMode(A3, INPUT);       // declare IR reciever as input
}

void loop(){
  digitalWrite(ledPin, LOW);  // turn LED OFF
  val_button = digitalRead(inPin);  // read input value
  if (val_button == LOW) {         // check if the input is HIGH (button released)
    digitalWrite(irledPin, LOW);  // turn LED OFF
  } else {
    digitalWrite(irledPin, HIGH);  // turn LED ON
  }
  val_ir = analogRead(A3);  // read input value
  if (val_ir < 1000) {      // check if the IR sensor recieve something
    //Serial.println("Data recieved");
    digitalWrite(ledPin, HIGH);  // turn LED ON 
    delay(2000);    // is checking every 2s
  }
  //Serial.println(analogRead(A3));
  delay(10);
}
