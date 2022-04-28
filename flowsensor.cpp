yte sensorpinSt = 0; //digitalpin 2
byte sensorpinEn = 1; //digitalpin 3
float calibrationfactor = 4.5;  //4.5 pluses / sec -- >> 1 l /min

volatile byte pulsecount;
float flowrateSt;
unsigned int flowMilliliterSt;
unsigned int totalmillilitersSt;
unsigned int flowliterSt;
unsigned long oldtime = 0;

float flowrateEn;
unsigned int flowMilliliterEn;
unsigned int totalmillilitersEn;
unsigned int flowliterEn;

void setup() {
Serial.begin(9600);
pulsecount = 0;
flowrateSt = 0;
flowMilliliterSt = 0;
flowliterSt = 0;
oldtime =0;

flowrateEn = 0;
flowMilliliterEn = 0;
flowliterEn = 0;

/// Interupt
attachInterrupt(sensorpinSt,pulsecounter,RISING);
attachInterrupt(sensorpinEn,pulsecounter,RISING);

}

void loop() {

// detach
if((millis()-oldtime) > 1000){
  detachInterrupt(sensorpinSt);
  detachInterrupt(sensorpinEn);
  flowrateSt = ((1000.0/(millis()-oldtime))*pulsecount)/calibrationfactor;
  flowrateEn = ((1000.0/(millis()-oldtime))*pulsecount)/calibrationfactor;
  oldtime = millis();
  flowMilliliterSt = (flowrateSt / 60 ) * 1000;
  flowMilliliterEn = (flowrateEn / 60 ) * 1000;
  totalmillilitersSt +=flowMilliliterSt;
  totalmillilitersEn +=flowMilliliterEn;
  flowliterSt = flowMilliliterSt / 1000;
  flowliterEn = flowMilliliterEn / 1000;
  
  Serial.print(" Flow rate starting = ");
  Serial.print(int(flowrateSt));
  Serial.print("L/ Min");
  Serial.print("\t");
  Serial.print("output Liquid quantity Starting = ");
  Serial.print(totalmillilitersSt/1000);
  Serial.print("L");
  Serial.println();
  Serial.print(" Flow rate Ending = ");
  Serial.print(int(flowrateEn));
  Serial.print("L/ Min");
  Serial.print("\t");
  Serial.print("output Liquid quantity Ending = ");
  Serial.print(totalmillilitersEn/1000);
  Serial.print("L");
  Serial.println();
  
  pulsecount = 0;
  attachInterrupt(sensorpinSt,pulsecounter,RISING);
  attachInterrupt(sensorpinEn,pulsecounter,RISING);};
}

void pulsecounter (){
  pulsecount++; 
}
