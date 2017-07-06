//Prototypes
void halt(void);
void parse(void);
void print_serial(void);
void read_serial(void);
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

  // set the data rate for the SoftwareSerial ports
  Serial1.begin(19200);
  delay(10);
  halt();
}

//MAIN
void loop()
{
  read_serial();
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

void print_serial()
{
  if(flag == 1){
    //print to serial port
    Serial.print(Str1[8], HEX);
    Serial.print(Str1[7], HEX);
    Serial.print(Str1[6], HEX);
    Serial.print(Str1[5], HEX);
    Serial.println();
    delay(100);
  }
}

void read_serial()
{
  seek();
  delay(10);
  parse();
  set_flag();
  print_serial();
  delay(100);
}

void seek()
{
  //search for Serial1 tag
  Serial1.write((uint8_t)255);
  Serial1.write((uint8_t)0);
  Serial1.write((uint8_t)1);
  Serial1.write((uint8_t)130);
  Serial1.write((uint8_t)131);
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
