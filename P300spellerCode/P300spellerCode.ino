int xAccelPin = A0;
int yAccelPin = A1;

<<<<<<< HEAD
const int ARRAY_SIZE = 60;
const int COLS = 6;
const int DELAY = 1500;
=======
const int ARRAY_SIZE = 30;
const int COLS = 6;
>>>>>>> origin/master
double THRESH = 0.03;

double magVals[ARRAY_SIZE];
double magAvg = 0.0;
double magDiff = 0.0;

unsigned long millisNow;

String message = "Message: ";

bool CAPS = true;
bool AVGD = false;
bool post1sec = false;

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
}

void loop(){
  if (magAvg != 0 && post1sec){ //highlight next column or row only after 1 sec
    post1sec = false;
    Serial.println(message);
    Serial.println();
    millisNow = millis();
    Serial.print("Vector: ");
    Serial.println(vector);
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
    else //vector=12 - highlight row 7
    {
      Serial.println("_ E A H R W\nT < I L M K\nN O C G V X\nS D Y B J ?\nU F P Q Z .\n1 2 3 4 5 6\n[7][8][9][0][^][!]");
    }
    Serial.println();
    Serial.print("MagDiff: ");
    Serial.print(magDiff);
    Serial.print(" MagAvg: ");
    Serial.println(magAvg);
  }
  
  // read the input of acceleration in x axis (as a voltage):
  double xAccelValue = analogRead(xAccelPin)*((float)5/1023);
  // read the input of acceleration in y axis (as a voltage):
  double yAccelValue = analogRead(yAccelPin)*((float)5/1023);
  // for debugging
  magVals[counter] = sqrt(pow(xAccelValue,2) + pow(yAccelValue,2));
  magDiff = magVals[counter]-magAvg;

  /*As far as I can tell, there is an issue with the logic of this IF/ELSE statement.
  / After a column has been selected, the ELSE component gets run as well
  / This means that the VECTOR varianle starts at 7 (the second row). Setting VECTOR to
  / -1 after selecting a row avoids this in the second case (starts on column 1), but 
  / I'm still working on getting it to not jump a row. Workaround: move last row to top.*/
  if (AVGD && magDiff > THRESH)
  {
    Serial.println("Eyebrow moved!");
    //Save column or row number
    if(vector<6){
      col = vector;
      vector = 6; //advance to highlighting 1st row next
    }
    else{
      row = vector - 6;
      vector = -1; //advance to highlighting 1st column next; -1 not 0 because bug
    }
    Serial.print("Row = ");
    Serial.print(row);
    Serial.print(" Col = ");
    Serial.println(col);
<<<<<<< HEAD
    delay(DELAY);
  }
  else //no eyebrow movement
  {
    if(AVGD && (millis()-millisNow) > DELAY) //highlight next column or row only after specified amount of time sec
=======
    delay(1000);
  }
  else //no eyebrow movement
  {
    if((millis()-millisNow) > 1000) //highlight next column or row only after 1 sec
>>>>>>> origin/master
    {
      post1sec = true;
      if(vector == 5) //reached last column
      {
        //cycle through columns again
        vector = 0;
      }
      else if(vector == 12)
      {
        //cycle through rows again
        vector = 6;
      }
      else
      {
        //advance to next column or row
        vector++;
      }
    }
  }
  
  counter++;

  //Take a running average w/ overlapping windows
  if (AVGD && (counter%(ARRAY_SIZE/10)==0)){
    for (int index = 0; index < ARRAY_SIZE; index++){
      magAvg += magVals[index];
    }
    magAvg = magAvg / ARRAY_SIZE;
  }
  else if (counter%ARRAY_SIZE==0){
    AVGD = true;
    for (int index = 0; index < ARRAY_SIZE; index++){
      magAvg += magVals[index];
    }
    magAvg = magAvg / ARRAY_SIZE;
  }
  
  if (counter >= ARRAY_SIZE){
    counter = 0;
  }
  
  
  // if a column and row number were selected
  if (row!=-1 && col!=-1){
    if (lowChars[row][col] == '_'){ //add space
      message += ' ';
<<<<<<< HEAD
    }
    else if(lowChars[row][col] == '<'){ //delete last character
      message.remove(message.length() - 1);
    }
    else if(lowChars[row][col] == '^'){ //set next character as upperCase
      CAPS = true;
      //do not print this character, wait until next character is selected, and print it as upperCase
    }
=======
    }
    else if(lowChars[row][col] == '<'){ //delete last character
      message.remove(message.length() - 1);
    }
    else if(lowChars[row][col] == '^'){ //set next character as upperCase
      CAPS = true;
      //do not print this character, wait until next character is selected, and print it as upperCase
    }
>>>>>>> origin/master
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
    delay(DELAY/10);
  }
}
