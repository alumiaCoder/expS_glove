const long baudRate = 9600; 

int pinb1 = 4;
int pinb2 = 5;
int pinb3 = 6;
int pinb4 = 7;

int l1val = 0;
int l2val = 0;
int l3val = 0;
int l4val = 0;
int jyval;

int l1val_last = 0;
int l2val_last = 0;
int l3val_last = 0;
int l4val_last = 0;
int jyval_last = 0;

void setup() {
  // Begin the Serial at 9600 Baud
  Serial1.begin(baudRate);
  pinMode(pinb1, INPUT_PULLUP);
  pinMode(pinb2, INPUT_PULLUP);
  pinMode(pinb3, INPUT_PULLUP);
  pinMode(pinb4, INPUT_PULLUP);
  pinMode(A1, INPUT);
  
}

void loop() {
  
  l1val = !digitalRead(pinb1);
  l2val = !digitalRead(pinb2);
  l3val = !digitalRead(pinb3);
  l4val = !digitalRead(pinb4);

  jyval = analogRead(A1);

//JOYSTICK Y
  if (jyval > 650) { //que maior que quinhentos mas o valor de descida não pode contar

    jyval = map(jyval, 650, 900, 1, 4);

    if(jyval_last != jyval)
    {
      jyval_last = jyval;
      
      Serial1.print("<");
      Serial1.print(7);
      Serial1.print(" ");
      Serial1.print(jyval);
      Serial1.print(">");
    }
       
  } else if (jyval < 450) {

    jyval = map(jyval, 250, 450, -4, -1);

    if(jyval_last != jyval)
    {
      jyval_last = jyval;
      
      Serial1.print("<");
      Serial1.print(7);
      Serial1.print(" ");
      Serial1.print(jyval);
      Serial1.print(">");
    }
    
  } else {

    if(jyval_last != 0)
    {
      jyval_last = 0;
      
      Serial1.print("<");
      Serial1.print(7);
      Serial1.print(" ");
      Serial1.print(0);
      Serial1.print(">");      
    }
  }


//BOTAO 1 -------------//------------
  if (l1val == 1 && l1val_last == 0)
  {
    l1val_last = 1;

    Serial1.print("<");
    Serial1.print(5);
    Serial1.print(" ");
    Serial1.print(l1val);
    Serial1.print(">"); 
    
  } else if (l1val == 0 && l1val_last == 1)
  {
    
    l1val_last = 0;
    
    Serial1.print("<");
    Serial1.print(5);
    Serial1.print(" ");
    Serial1.print(l1val);
    Serial1.print(">"); 
    
  }

//BOTAO 2 -------------//------------
  if (l2val == 1 && l2val_last == 0)
  {
    l2val_last = 1;

    Serial1.print("<");
    Serial1.print(6);
    Serial1.print(" ");
    Serial1.print(l2val);
    Serial1.print(">");
    
  } else if (l2val == 0 && l2val_last == 1)
  {
    
    l2val_last = 0;

    Serial1.print("<");
    Serial1.print(6);
    Serial1.print(" ");
    Serial1.print(l2val);
    Serial1.print(">"); 
    
  }

//BOTAO 3 -------------//------------
  if (l3val == 1 && l3val_last == 0)
  {
    l3val_last = 1;

    Serial1.print("<");
    Serial1.print(8);
    Serial1.print(" ");
    Serial1.print(l3val);
    Serial1.print(">");
    
  } else if (l3val == 0 && l3val_last == 1)
  {
    
    l3val_last = 0;

    Serial1.print("<");
    Serial1.print(8);
    Serial1.print(" ");
    Serial1.print(l3val);
    Serial1.print(">"); 
    
  }
  
//BOTAO 4 -------------//------------
  if (l4val == 1 && l4val_last == 0)
  {

    l4val_last = 1;
    Serial1.print("<");
    Serial1.print(9);
    Serial1.print(" ");
    Serial1.print(l4val);
    Serial1.print(">");
    
  } else if (l4val == 0 && l4val_last == 1)
  {
    
    l4val_last = 0;

    Serial1.print("<");
    Serial1.print(9);
    Serial1.print(" ");
    Serial1.print(l4val);
    Serial1.print(">");  
    
  }
delay(10);
}
