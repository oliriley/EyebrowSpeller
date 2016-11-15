int xAccelPin = A0;
int yAccelPin = A1;

const int ARRAY_SIZE = 50;
const int COLS = 6;
const int DELAY = 1000;

double THRESH = .006;

double magVals[ARRAY_SIZE];
double magAvg = 0.0;
double magDiff = 0.0;

unsigned long millisNow;
unsigned long millisChar;

String message = "";

bool CAPS = true;
bool AVGD = false;
bool MOVE = false;

int counter = 0; // keep track of how many magnitude samples have been recorded
int vector = -1; // use for cycling through highlighted column or row; 6 columns, 7 rows
int row = -1; //use for saving selected row later
int col = -1; //use for saving selected column later

const char capChars[][COLS] = {{'_', 'E', 'A', 'H', 'R', 'W'},{'T', '<', 'I', 'L', 'M', 'K'},{'N', 'O', 'C', 'G', 'V', 'X'},{'S', 'D', 'Y', 'B', 'J', '?'},{'U', 'F', 'P', 'Q', 'Z', '.'},{'1', '2', '3', '4', '5', '6'},{'7', '8', '9', '0', '^', '!'}};
const char lowChars[][COLS] = {{'_', 'e', 'a', 'h', 'r', 'w'},{'t', '<', 'i', 'l', 'm', 'k'},{'n', 'o', 'c', 'g', 'v', 'x'},{'s', 'd', 'y', 'b', 'j', '?'},{'u', 'f', 'p', 'q', 'z', '.'},{'1', '2', '3', '4', '5', '6'},{'7', '8', '9', '0', '^', '!'}};

void setup() {
  //set up pin configurations
  pinMode(xAccelPin, INPUT);
  pinMode(yAccelPin, INPUT);
  
  //start serial
  Serial.begin(9600);
  
  for (int index = 0; index < ARRAY_SIZE; index++){
    magVals[index] = 0;
  }

  millisNow = millis();
  millisChar = millisNow;
}

void loop(){
  // read the input of acceleration in x axis (as a voltage):
  double xAccelValue = analogRead(xAccelPin)*((float)5/1023);
  // read the input of acceleration in y axis (as a voltage):
  double yAccelValue = analogRead(yAccelPin)*((float)5/1023);
  // for debugging
  magVals[counter] = sqrt(pow(xAccelValue,2) + pow(yAccelValue,2));
  magDiff = magVals[counter]-magAvg;
  
  counter++;

  //Take a running average w/ overlapping windows
  if (AVGD && (counter%(ARRAY_SIZE/10)==0))
  {
    for (int index = 0; index < ARRAY_SIZE; index++){
      magAvg += magVals[index];
    }
    magAvg = magAvg / ARRAY_SIZE;
    //Serial.println("Avging");
  }
  else if (counter%ARRAY_SIZE==0)
  {
    AVGD = true;
    for (int index = 0; index < ARRAY_SIZE; index++){
      magAvg += magVals[index];
    }
    magAvg = magAvg / ARRAY_SIZE;
  }

  if (counter >= ARRAY_SIZE){
    counter = 0;
  }
  
  if (AVGD)
  {
    if ((magDiff > THRESH) && (millis() - millisChar > DELAY/2))// eyebrow movement far enough apart to matter
    {
      MOVE = true;
      /*Serial.print("MagDiff: ");
      Serial.print(magDiff);
      Serial.print(" MagAvg: ");
      Serial.println(magAvg);*/
      Serial.print("Row = ");
      Serial.print(row);
      Serial.print(" Col = ");
      Serial.println(col);      
      //Save column or row number
      if(vector<6){ // 0-5
        col = vector;
        vector = 6; //advance to highlighting 1st row next
      }
      else{ // 6-12
        row = vector - 6;
        vector = 0; //advance to highlighting 1st column next
      }
      millisChar = millis();
    }
    
    if (millis() - millisNow > DELAY)
    {
      vector++;
      if(vector == 6) //reached last column
      {
        //cycle through columns again
        vector = 0;
      }
      else if(vector == 13)
      {
        //cycle through rows again
        vector = 6;
      }
      else if(vector == 1 || vector == 7)
      {
        vector -= MOVE;
      }

      MOVE = false;

      Serial.print("Message: ");
      Serial.println(message);
      Serial.println();
      if(vector == 0) //highlight column 1
      {
        Serial.println("[_] E A H R W\n[T] < I L M K\n[N] O C G V X\n[S] D Y B J ?\n[U] F P Q Z .\n[1] 2 3 4 5 6\n[7] 8 9 0 ^ !");
      }
      else if(vector == 1) //highlight column 2
      {
        Serial.println("_ [E] A H R W\nT [<] I L M K\nN [O] C G V X\nS [D] Y B J ?\nU [F] P Q Z .\n1 [2] 3 4 5 6\n7 [8] 9 0 ^ !");
      }
      else if(vector == 2) //highlight column 3
      {
        Serial.println("_ E [A] H R W\nT < [I] L M K\nN O [C] G V X\nS D [Y] B J ?\nU F [P] Q Z .\n1 2 [3] 4 5 6\n7 8 [9] 0 ^ !");
      }
      else if(vector == 3) //highlight column 4
      {
        Serial.println("_ E A [H] R W\nT < I [L] M K\nN O C [G] V X\nS D Y [B] J ?\nU F P [Q] Z .\n1 2 3 [4] 5 6\n7 8 9 [0] ^ !");
      }
      else if(vector == 4) //highlight column 5
      {
        Serial.println("_ E A H [R] W\nT < I L [M] K\nN O C G [V] X\nS D Y B [J] ?\nU F P Q [Z] .\n1 2 3 4 [5] 6\n7 8 9 0 [^] !");
      }
      else if(vector == 5) //highlight column 6
      {
        Serial.println("_ E A H R [W]\nT < I L M [K]\nN O C G V [X]\nS D Y B J [?]\nU F P Q Z [.]\n1 2 3 4 5 [6]\n7 8 9 0 ^ [!]");
      }
      else if(vector == 6) //highlight row 1
      {
        Serial.println("[_][E][A][H][R][W]\nT < I L M K\nN O C G V X\nS D Y B J ?\nU F P Q Z .\n1 2 3 4 5 6\n7 8 9 0 ^ !");
      }
      else if(vector == 7) //highlight row 2
      {
        Serial.println("_ E A H R W\n[T][<][I][L][M][K]\nN O C G V X\nS D Y B J ?\nU F P Q Z .\n1 2 3 4 5 6\n7 8 9 0 ^ !");
      }
      else if(vector == 8) //highlight row 3
      {
        Serial.println("_ E A H R W\nT < I L M K\n[N][O][C][G][V][X]\nS D Y B J ?\nU F P Q Z .\n1 2 3 4 5 6\n7 8 9 0 ^ !");
      }
      else if(vector == 9) //highlight row 4
      {
        Serial.println("_ E A H R W\nT < I L M K\nN O C G V X\n[S][D][Y][B][J][?]\nU F P Q Z .\n1 2 3 4 5 6\n7 8 9 0 ^ !");
      }
      else if(vector == 10) //highlight row 5
      {
        Serial.println("_ E A H R W\nT < I L M K\nN O C G V X\nS D Y B J ?\n[U][F][P][Q][Z][.]\n1 2 3 4 5 6\n7 8 9 0 ^ !");
      }
      else if(vector == 11) //highlight row 6
      {
        Serial.println("_ E A H R W\nT < I L M K\nN O C G V X\nS D Y B J ?\nU F P Q Z .\n[1][2][3][4][5][6]\n7 8 9 0 ^ !");
      }
      else if(vector == 12) //highlight row 7 ; no default case so that weirdness with Vector will cause unexpected behavior
      {
        Serial.println("_ E A H R W\nT < I L M K\nN O C G V X\nS D Y B J ?\nU F P Q Z .\n1 2 3 4 5 6\n[7][8][9][0][^][!]");
      }
      Serial.println();
      millisNow = millis();
    }
    
    // if a column and row number were selected
    if (row!=-1 && col!=-1)
    {
      if (lowChars[row][col] == '_'){ //add space
        message += ' ';
      }
      else if(lowChars[row][col] == '<'){ //delete last character
        message.remove(message.length() - 1);
      }
      else if(lowChars[row][col] == '^'){ //set next character as upperCase
        CAPS = true;
        //do not print this character, wait until next character is selected, and print it as upperCase
      }
      else if(lowChars[row][col] == '.' || lowChars[row][col] == '?' || lowChars[row][col] == '!'){ //add punctuation
        message += lowChars[row][col];
        CAPS = true; // first letter of next sentence will be capital
      }
      else{ //print the letter or number
        if (CAPS){
          //message.concat(capChars[col][row]);
          message += capChars[row][col];
          CAPS = false;
        }
        else {
          //message.concat(lowChars[col][row]);
          message += lowChars[row][col];
        }
      }
      //reset col and row
      col = -1;
      row = -1;
    }
  }

  delay(1);
  if (vector > 12){
    vector = 0; //precaution
  }
}
