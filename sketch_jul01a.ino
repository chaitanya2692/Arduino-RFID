//#include <SoftwareSerial1.h>

//SoftwareSerial1 rfid(7, 8);
//SoftwareSerial1 xbee(10, 9);

//Prototypes
void check_for_notag(void);
void halt(void);
void parse(void);
void print_Serial(void);
void read_Serial(void);
void seek(void);
void set_flag(void);

//Global var
int flag = 0;
int Str1[11];

//INIT
void setup()
{
  Serial.begin(9600);
  Serial.println("Start");

  // set the data rate for the Serial ports
  Serial1.begin(19200);
  delay(10);
  halt();
}

//MAIN
void loop()
{
  read_Serial();
}

void check_for_notag()
{
  seek();
  delay(10);
  parse();
  set_flag();

  if(flag = 1){
    seek();
    delay(10);
    parse();
  }
}

void halt()
{
 //Halt tag
  Serial1.write((uint8_t)255);
  Serial1.write((uint8_t)0);
  Serial1.write((uint8_t)1);
  Serial1.write((uint8_t)147);
  Serial1.write((uint8_t)148);
}

void parse()
{
  while(Serial1.available()){
    if(Serial1.read() == 255){
      for(int i=1;i<11;i++){
        Str1[i]= Serial1.read();
      }
    }
  }
}

void print_Serial()
{
  if(flag == 1){
    //print to Serial port
    Serial.println("Card Details");
    Serial.print(Str1[8], HEX);
    Serial.print(Str1[7], HEX);
    Serial.print(Str1[6], HEX);
    Serial.print(Str1[5], HEX);
    Serial.println();
    //print to XBee module
    //xbee.print(Str1[8], HEX);
    //xbee.print(Str1[7], HEX);
    //xbee.print(Str1[6], HEX);
    //xbee.print(Str1[5], HEX);
    //xbee.println();
    delay(100);
    //check_for_notag();
  }
}

void read_Serial()
{
  seek();
  delay(10);
  parse();
  set_flag();
  print_Serial();
  delay(100);
}

void seek()
{
  //search for RFID tag
  Serial.write((uint8_t)255);
  Serial.write((uint8_t)0);
  Serial.write((uint8_t)1);
  Serial.write((uint8_t)130);
  Serial.write((uint8_t)131);
  Serial.write('\n');
//  Serial.println("Finding Card");
  delay(10);
}

void set_flag()
{
  if(Str1[2] == 6){
    flag++;
  }
  if(Str1[2] == 2){
    flag = 0;
  }
}
