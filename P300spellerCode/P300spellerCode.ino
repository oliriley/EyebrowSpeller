int xAccelPin = A0;
int yAccelPin = A1;
//consider taking magnitude of X and Y together
const int ARRAY_SIZE = 150;
double THRESH = 0.03;


double magVals[ARRAY_SIZE];
double magAvg = 0.0;
double magDiff = 0.0;


long int millisNow;


int counter = 0;
//int row = 0; //use for cycling throgh rows later
//int col = 0; //use for cycling throgh columns later


void setup() {
  //set up pin configurations
  pinMode(xAccelPin, INPUT);
  pinMode(yAccelPin, INPUT);


  //start serial
  Serial.begin(9600);


  for (int index = 0; index < ARRAY_SIZE; index++){
    magVals[index] = 0;
  }
}


void loop() {
  // read the input of acceleration in x axis (as a voltage):
  double xAccelValue = analogRead(xAccelPin)*((float)5/1023);
  // read the input of acceleration in y axis (as a voltage):
  double yAccelValue = analogRead(yAccelPin)*((float)5/1023);
  magVals[counter] = sqrt(pow(xAccelValue,2) + pow(yAccelValue,2));
  magDiff = magVals[counter]-magAvg;
  // print out the values you read:
  /*Serial.print(magDiff);
  Serial.print(magAvg);*/


  if (magAvg != 0){


    for (int index = 0; index < 10; index++){
      Serial.println("");
    }
    Serial.println("e t a o i n s");
    Serial.println(". ! ? < ^ _ 0");
    Serial.println("h r d l c u m");
    Serial.println("w f g y p b v");
    Serial.println("k j x q z 1 2");
    Serial.println("3 4 5 6 7 8 9");


    if (magDiff > THRESH){
      //
    }
  }
  
  counter++;
  
  if (counter%(ARRAY_SIZE/10)==0){
    for (int index = 0; index < ARRAY_SIZE; index++){
      magAvg += magVals[index];
    }
    magAvg = magAvg / ARRAY_SIZE;
  }
  if (counter >= ARRAY_SIZE){
    counter = 0;
  }
}
