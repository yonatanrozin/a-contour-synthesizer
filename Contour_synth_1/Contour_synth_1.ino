//NOTE: THIS PROGRAM USES 12 CIRCUITS. pairCount, minReads, maxReads AND transistorOuts SHOULD BE ADJUSTED ACCORDINGLY TO CHANGE CIRCUIT #

const int pairCount = 12; //# of circuits

const int analogIn = A7;

const int minVal = 100; //lower threshold for counting reading

//min and max readings on each circuit for standardization
const int minReads[pairCount] = {150, 150, 150, 148, 150, 148, 148, 149, 150, 150, 130, 159}; 
const int maxReads[pairCount] = {200, 200, 200, 198, 200, 198, 198, 202, 199, 201, 194, 208};


const int transistorOuts[pairCount] = {12, 14, 11, 15, 10, 16, 17, 9, 18, 8, 19, 7};


int readings[pairCount]; //holds last readings per circuit
int currentReads[pairCount]; //readings[] but with 0s if no input


int currentPair = 0;


void setup() {

  //for each pair:
  for (int i = 0; i < pairCount; i++) {
    pinMode(analogIn, INPUT_PULLDOWN);
    pinMode(transistorOuts[i], OUTPUT);

    digitalWrite(transistorOuts[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {


  //disable current circuit
  digitalWrite(transistorOuts[currentPair], LOW);

  //update current circuit
  currentPair = (currentPair + 1) % pairCount;

  //enable new circuit
  digitalWrite(transistorOuts[currentPair], HIGH);


  //record circuit reading on new circuit
  int currentRead = analogRead(analogIn);

  //ensure there's an input:
  if (currentRead > minVal) {

    //stabilize values by averaging:
    readings[currentPair] = readings[currentPair] * .1 + currentRead * .9;

    //record new reading in official readings array
    
//    currentReads[currentPair] = readings[currentPair];
    currentReads[currentPair] = map(readings[currentPair], minReads[currentPair], maxReads[currentPair], 150, 200);
  }
  //if no input, record 0
  else currentReads[currentPair] = 0;


  //FOR SENDING TO MAXMSP:
  for (int p = 0; p < pairCount; p++) {
    Serial.write(currentReads[p] / 4);
  }

//  //FOR TESTING W/ SERIAL MONITOR:
//  for (int p = 0; p < pairCount; p++) {
//    Serial.print(currentReads[p] / 4);
//    Serial.print(",");
//  }
//  Serial.println();


  delay(10);



}
