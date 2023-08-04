#include <SoftwareSerial.h>
SoftwareSerial BTserial(8, 9);

const long baudRate = 9600; 
const byte numChars = 8;
char receivedChars[numChars];

int pinb1 = 4;
int pinb2 = 5;
int pinb3 = 6;
int pinb4 = 7;

int r1val = 0;
int r2val = 0;
int r3val = 0;
int r4val = 0;
int jyval;
int jxval;
int jy_last_sent;
int jx_last_sent;

int r1val_last = 0;
int r2val_last = 0;
int r3val_last = 0;
int r4val_last = 0;
int jyval_last = 0;
int jxval_last = 0;

int jblock = 0;

boolean newData = false;

int time_to_joy_burst = 50; // this is 50 counters of 10 millisecond cycles. 0.5seconds
int joy_burst_step = 5;
int joy_burst_step_counter = 0;
int joy_step_counter = 0;

int joy_loop_list[5] = {0,0,0,0,0};
int joy_loop_idx = 0;
int joy_loop_dir = 0;
int joy_loop_rep_check = 0;

void setup() 
{
  Serial1.begin(baudRate);
  Serial.begin(baudRate);
  BTserial.begin(baudRate); 
  pinMode(pinb1, INPUT_PULLUP);
  pinMode(pinb2, INPUT_PULLUP);
  pinMode(pinb3, INPUT_PULLUP);
  pinMode(pinb4, INPUT_PULLUP); 
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
}

void loop() 
{
  //código de leitura dos botões e joystick
  r1val = !digitalRead(pinb1);
  r2val = !digitalRead(pinb2);
  r3val = !digitalRead(pinb3);
  r4val = !digitalRead(pinb4);

  jyval = analogRead(A1);
  jxval = analogRead(A0);
  
//JOYSTICK Y
  if (jyval > 650) { //que maior que quinhentos mas o valor de descida não pode contar

    jyval = 1;
    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    if (joy_loop_idx == 0) { // we reseted somewhere

      joy_loop_list[0] = 4;
      joy_loop_idx = 1;
      
    } else if (joy_loop_idx < 4) { // we have not yet completed the cycle.

      if (joy_loop_idx > 1) { //we want to block all other happenings
        joy_step_counter = 0;
      };
      
      joy_loop_rep_check = 0;
      for (int i=0; i<joy_loop_idx; i++) { // see if there this number is already present
        if (joy_loop_list[i] == 4) {
          
          joy_loop_rep_check = 1;
          
        };
        
      };
      
      if (joy_loop_rep_check == 0) { // number was not present. Add this one

        joy_loop_list[joy_loop_idx] = 4;
        joy_loop_idx = joy_loop_idx + 1;
        
      };
      
    } else { // we might complete the cycle now

      joy_loop_rep_check = 0;
      for (int i=1; i<5; i++) { // see if there this number is already present
  
        if (joy_loop_list[i] == 4) {
          
          joy_loop_rep_check = 1;
          
        };
      };

      if (joy_loop_list[0] == 4 and joy_loop_rep_check == 0) { // cycle was closed

        if (joy_loop_list[3] == 6) {

          joy_loop_dir = 8; //clockwise
        
        } else {

          joy_loop_dir = 9; //counter clockwise
          
        };
        
        // simulate open
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(1);

        // simulate close
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(0);
  
        // reset variables
        joy_loop_idx = 0; 
        joy_loop_rep_check = 0;
        for (int i=0; i<5; i++) {
  
          joy_loop_list[i] = 0;
          
        };
          
      };
      
    };
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    
    if (joy_step_counter > 0) { // we are pressing the joystick
      if (joy_step_counter > time_to_joy_burst) { // we are pressing it for long enough 

        if (joy_burst_step_counter < joy_burst_step) { // waiting to send next joy
          
          joy_burst_step_counter = joy_burst_step_counter + 1;
          
        } else { // send joy
          
          joy_burst_step_counter = 0;

          // simulate close
          BTserial.print(jy_last_sent);
          BTserial.print(" ");
          BTserial.println(0);

          // simulate open
          BTserial.print(jy_last_sent);
          BTserial.print(" ");
          BTserial.println(jyval);
                    
        } 
        
      } else {
        
        joy_step_counter = joy_step_counter + 1;
        
      }
    }

    if(jyval_last != jyval && jblock == 0)
    {
      jblock = 1;
      jyval_last = jyval;
      jy_last_sent = 4;
      BTserial.print(jy_last_sent);
      BTserial.print(" ");
      BTserial.println(jyval);
      joy_step_counter = 1;
      joy_burst_step_counter = 0;

    }
       
  } else if (jyval < 450) {

    jyval = 1;

     // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    if (joy_loop_idx == 0) { // we reseted somewhere

      joy_loop_list[0] = 5;
      joy_loop_idx = 1;
      
    } else if (joy_loop_idx < 4) { // we have not yet completed the cycle
      
      if (joy_loop_idx > 1) { //we want to block all other happenings
        joy_step_counter = 0;
      };
      
      joy_loop_rep_check = 0;
      for (int i=0; i<joy_loop_idx; i++) { // see if there this number is already present

        if (joy_loop_list[i] == 5) {
          
          joy_loop_rep_check = 1;
          
        };
        
      };
      
      if (joy_loop_rep_check == 0) { // number was not present. Add this one

        joy_loop_list[joy_loop_idx] = 5;
        joy_loop_idx = joy_loop_idx + 1;
        
      };
      
    } else { // we might complete the cycle now

      joy_loop_rep_check = 0;
      for (int i=1; i<5; i++) { // see if there this number is already present
  
        if (joy_loop_list[i] == 5) {
          
          joy_loop_rep_check = 1;
          
        };
      };

      if (joy_loop_list[0] == 5 and joy_loop_rep_check == 0) { // cycle was closed
    
        if (joy_loop_list[3] == 7) {

          joy_loop_dir = 8; //clockwise
        
        } else {

          joy_loop_dir = 9; //counter clockwise
          
        };
        
        // simulate open
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(1);

        // simulate close
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(0);
  
  
        // reset variables
        joy_loop_idx = 0; 
        joy_loop_rep_check = 0;
        for (int i=0; i<5; i++) {
  
          joy_loop_list[i] = 0;
          
        };
          
      };
      
    };
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------

    if (joy_step_counter > 0) { // we are pressing the joystick
      if (joy_step_counter > time_to_joy_burst) { // we are pressing it for long enough 

        if (joy_burst_step_counter < joy_burst_step) { // waiting to send next joy
          
          joy_burst_step_counter = joy_burst_step_counter + 1;
          
        } else { // send joy
          
          joy_burst_step_counter = 0;

          // simulate close
          BTserial.print(jy_last_sent);
          BTserial.print(" ");
          BTserial.println(0);

          // simulate open
          BTserial.print(jy_last_sent);
          BTserial.print(" ");
          BTserial.println(jyval);
                    
        } 
        
      } else {
        
        joy_step_counter = joy_step_counter + 1;
        
      }
    }

    if(jyval_last != jyval && jblock == 0)
    {
      jblock = 1;
      jyval_last = jyval;
      
      jy_last_sent = 5;
      BTserial.print(jy_last_sent);
      BTserial.print(" ");
      BTserial.println(jyval);
      joy_step_counter = 1;
      joy_burst_step_counter = 0;

    }
    
  } else if (jxval > 450 && jxval < 650 && jyval > 450 && jyval < 650) {

    if(jyval_last != 0)
    {
      jblock = 0;
      jyval_last = 0;     

      BTserial.print(jy_last_sent);
      BTserial.print(" ");
      BTserial.println(0);
      joy_step_counter = 0;

      joy_loop_idx = 0; 
      joy_loop_rep_check = 0;
      for (int i=0; i<5; i++) {

        joy_loop_list[i] = 0;
        
      };
    
    }
  }

  if (jxval > 650 ) { //que maior que quinhentos mas o valor de descida não pode contar

    jxval = 1;

    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    if (joy_loop_idx == 0) { // we reseted somewhere

      joy_loop_list[0] = 7;
      joy_loop_idx = 1;
      
    } else if (joy_loop_idx < 4) { // we have not yet completed the cycle
      
      if (joy_loop_idx > 1) { //we want to block all other happenings
        joy_step_counter = 0;
      };
      
      joy_loop_rep_check = 0;
      for (int i=0; i<joy_loop_idx; i++) { // see if there this number is already present

        if (joy_loop_list[i] == 7) {
          
          joy_loop_rep_check = 1;
          
        };
        
      };
      
      if (joy_loop_rep_check == 0) { // number was not present. Add this one

        joy_loop_list[joy_loop_idx] = 7;
        joy_loop_idx = joy_loop_idx + 1;
        
      };
      
    } else { // we might complete the cycle now

      joy_loop_rep_check = 0;
      for (int i=1; i<5; i++) { // see if there this number is already present
  
        if (joy_loop_list[i] == 7) {
          
          joy_loop_rep_check = 1;
          
        };
      };

      if (joy_loop_list[0] == 7 and joy_loop_rep_check == 0) { // cycle was closed
    
        if (joy_loop_list[3] == 4) {

          joy_loop_dir = 8; //clockwise
        
        } else {

          joy_loop_dir = 9; //counter clockwise
          
        };
        
        // simulate open
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(1);

        // simulate close
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(0);
  
        // reset variables
        joy_loop_idx = 0; 
        joy_loop_rep_check = 0;
        for (int i=0; i<5; i++) {
  
          joy_loop_list[i] = 0;
          
        };
          
      };
      
    };
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------

    if(jxval_last != jxval && jblock == 0)
    {
      jblock = 1;
      jxval_last = jxval;
      jx_last_sent = 7;
      BTserial.print(jx_last_sent);
      BTserial.print(" ");
      BTserial.println(jxval);

    }
       
  } else if (jxval < 450) {

    jxval = 1;

     // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP-----------------------------------------
    if (joy_loop_idx == 0) { // we reseted somewhere

      joy_loop_list[0] = 6;
      joy_loop_idx = 1;
      
    } else if (joy_loop_idx < 4) { // we have not yet completed the cycle

      if (joy_loop_idx > 1) { //we want to block all other happenings
        joy_step_counter = 0;
      };
      
      joy_loop_rep_check = 0;
      for (int i=0; i<joy_loop_idx; i++) { // see if there this number is already present

        if (joy_loop_list[i] == 6) {
          
          joy_loop_rep_check = 1;
          
        };
        
      };
      
      if (joy_loop_rep_check == 0) { // number was not present. Add this one

        joy_loop_list[joy_loop_idx] = 6;
        joy_loop_idx = joy_loop_idx + 1;
        
      };
      
    } else { // we might complete the cycle now

      joy_loop_rep_check = 0;
      for (int i=1; i<5; i++) { // see if there this number is already present
  
        if (joy_loop_list[i] == 6) {
          
          joy_loop_rep_check = 1;
          
        };
      };
      
      if (joy_loop_list[0] == 6 and joy_loop_rep_check == 0) { // cycle was closed

        if (joy_loop_list[3] == 5) {

          joy_loop_dir = 8; //clockwise
        
        } else {

          joy_loop_dir = 9; //counter clockwise
          
        };
        
        // simulate open
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(1);

        // simulate close
        BTserial.print(joy_loop_dir);
        BTserial.print(" ");
        BTserial.println(0);
  
        // reset variables
        joy_loop_idx = 0; 
        joy_loop_rep_check = 0;
        for (int i=0; i<5; i++) {
  
          joy_loop_list[i] = 0;
          
        };
          
      };
      
    };
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    // ----------------------------------------------------------------JOY LOOP END-----------------------------------------
    
    if(jxval_last != jxval && jblock == 0)
    {
      jblock = 1;
      jxval_last = jxval;
      jx_last_sent = 6;
      BTserial.print(jx_last_sent);
      BTserial.print(" ");
      BTserial.println(jxval);

    }
    
  } else if (jxval > 450 && jxval < 650 && jyval > 450 && jyval < 650) {

    if(jxval_last != 0)
    {
      jblock = 0;
      jxval_last = 0;      

      BTserial.print(jx_last_sent);
      BTserial.print(" ");
      BTserial.println(0);

      joy_loop_idx = 0; 
      joy_loop_rep_check = 0;
      for (int i=0; i<5; i++) {

        joy_loop_list[i] = 0;
        
      };
    
    }
  }


//BOTAO 1 -------------//------------
  if (r1val == 1 && r1val_last == 0)
  {
    r1val_last = 1;

    BTserial.print(0);
    BTserial.print(" ");
    BTserial.println(r1val); 
    
  } else if (r1val == 0 && r1val_last == 1)
  {
    r1val_last = 0;    

    BTserial.print(0);
    BTserial.print(" ");
    BTserial.println(r1val); 
    
  }

//BOTAO 2 -------------//------------
  if (r2val == 1 && r2val_last == 0)
  {
    r2val_last = 1;

    BTserial.print(1);
    BTserial.print(" ");
    BTserial.println(r2val);
    
  } else if (r2val == 0 && r2val_last == 1)
  {
    
    r2val_last = 0;

    BTserial.print(1);
    BTserial.print(" ");
    BTserial.println(r2val); 
    
  }

//BOTAO 3 -------------//------------
  if (r3val == 1 && r3val_last == 0)
  {
    r3val_last = 1;

    BTserial.print(2);
    BTserial.print(" ");
    BTserial.println(r3val);
    
  } else if (r3val == 0 && r3val_last == 1)
  {
    
    r3val_last = 0;

    BTserial.print(2);
    BTserial.print(" ");
    BTserial.println(r3val); 
    
  }
  
//BOTAO 4 -------------//------------
  if (r4val == 1 && r4val_last == 0)
  {

    r4val_last = 1;

    BTserial.print(3);
    BTserial.print(" ");
    BTserial.println(r4val);
    
  } else if (r4val == 0 && r4val_last == 1)
  {
    
    r4val_last = 0;

    BTserial.print(3);
    BTserial.print(" ");
    BTserial.println(r4val);  
    
  }

  recvWithStartEndMarkers();

  if (newData == true) {
    BTserial.println(receivedChars);
    newData = false;
  }
  
  delay(10);
       
}
// ===============================
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial1.available() > 0 && newData == false) {
        rc = Serial1.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
