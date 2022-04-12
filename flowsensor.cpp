byte sensorpin = 0;
float calibrationfactor = 4.5;  //4.5 pluses / sec -- >> 1 l /min

volatile byte pulsecount;
float flowrate;
unsigned int flowMilliliter;
unsigned int totalmilliliters;

unsigned int flowliter;
unsigned long oldtime = 0;

void setup() {
Serial.begin(9600);
pulsecount = 0;
flowrate = 0;
flowMilliliter = 0;

flowliter = 0;
oldtime =0;

/// Interupt
attachInterrupt(sensorpin,pulsecounter,RISING);

}

void loop() {
  
// detach
if((millis()-oldtime) > 1000){
  detachInterrupt(sensorpin);
  flowrate = ((1000.0/(millis()-oldtime))*pulsecount)/calibrationfactor;
  oldtime = millis();
  flowMilliliter = (flowrate / 60 ) * 1000;

  totalmilliliters +=flowMilliliter;

  flowliter = flowMilliliter / 1000;

  Serial.print(" Flow rate = ");
  Serial.print(int(flowrate));
  Serial.print("L/ Min");

  Serial.print("\t");

  Serial.print("output Liquid quantity = ");
  Serial.print(totalmilliliters);
  Serial.print("mL");

  Serial.print("\t");
  
  Serial.print(flowliter);
  Serial.println("L");

  pulsecount = 0;
  attachInterrupt(sensorpin,pulsecounter,RISING);};
}

void pulsecounter (){
  pulsecount++; 
}
