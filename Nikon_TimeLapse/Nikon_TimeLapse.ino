/*Copyright 2016 Luca Angioloni

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

  #define LEDPin 3
  #define FREQ 38400  // IR frequence
  #define LapseTime 5000 //time between each shot in milliseconds. Should be > 500
   
  //shutter sequence (on,off,on,off ... in microsecond)
  unsigned long sequence[] = {2000,27830,390,1580,410,3580,400,63200,2000,27830,390,1580,410,3580,400,0};
  int seq_l;
   
  //oscd is a delay in microsecond used at each oscillation.
  int oscd;
   
  void oscillate(int pin, unsigned long n, int shine){
    int ir_status=0;
    while(n>0){
      n--;
      delayMicroseconds(oscd);
      ir_status  =  !ir_status; 
      digitalWrite(pin,  ir_status && shine);  
    }
  }
   
  void snap(){
    int i;
    for(i=0;i<seq_l;i++){
      oscillate(LEDPin, sequence[i], i%2==0);
    }
    digitalWrite(LEDPin,  0);
  }
   
  void setup() {  
    int min=1, max=100, i;
    int last_oscd=0;
    unsigned long before, intervalle;
    oscd=max;
   
    seq_l = sizeof(sequence)/sizeof(unsigned long);
   
    pinMode(LEDPin, OUTPUT);
    pinMode(5, OUTPUT);
   
    //this "while" will process the best "oscd"
    while(last_oscd!=oscd){
      last_oscd=oscd;
      oscd=(min+max)>>1;
   
      before=millis();
      oscillate(LEDPin, FREQ, 1);
      intervalle=millis()-before;
   
      if(intervalle >= 1000) max=oscd;
      else min=oscd;
    }
   
    //rewrite the sequence array, we replace all values in microsecond by the number of oscillation
    for(i=0;i<seq_l;i++){
      sequence[i] = (sequence[i] * FREQ) / (intervalle * 1000);
    }
  }
   
   
  void loop() {
    digitalWrite(5, HIGH);
    snap();
    delay(500);
    digitalWrite(5, LOW);
    delay(LapseTime-500);
  }
