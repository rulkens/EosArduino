/**
serial functions

**/

#define SERIAL_SPEED 19200

#define MESSAGE_SET_STATE 0
#define MESSAGE_SET_COLOR 1

/* GLOBALS */
String last_read_message;

void initSerial() {
  Serial.begin(SERIAL_SPEED);
  log("EOS Interface Ready");
}
/*
set the general state by the messages coming in */
void loopSerial() {
  
  if (Serial.available())  {
     last_read_message = Serial.readString();
     
     parseMessage();
     
     // echo
     log(last_read_message);
  }
}

void parseMessage(){
  int message = 0;
  String arg1;
  // TODO: Parse string
  if(last_read_message.startsWith("setState")){
    message = MESSAGE_SET_STATE;
    // we remove one extra character, which can be a space
    last_read_message.remove(0,9);
    //last_read_message.trim();
    arg1 = last_read_message;
    
  } else if(last_read_message.startsWith("setColor")){
    message = MESSAGE_SET_COLOR;
    // we remove one extra character, which can be a space
    last_read_message.remove(0,9);
    arg1 = last_read_message;
  }
  
  switch(message){
    case MESSAGE_SET_STATE:
      // setting the application state
      log("[S] setting state");
      log(arg1.toInt());
      setState(arg1.toInt());
      break;
    case MESSAGE_SET_COLOR:
      log("[S] setting color for OK state");
      c_ok = hex2int(arg1.c_str(), arg1.length());
      log("c_ok");
      log(c_ok);
      break;
  }
}

void log(String text) {
  Serial.print("# ");
  Serial.println(text);
}

void log(int number){
  Serial.print("# ");
  Serial.println(String(number));
}

void log(long number){
  Serial.print("# ");
  Serial.println(String(number));
}

// strangely enough, this matches the String text event
// so when we add this, events with normal String values will not get fired....
//void log(boolean b){
//  Serial.print("# ");
//  Serial.println(b ? "true" : "false");
//}

//void log(String s, boolean b){
//  Serial.print("# ");
//  Serial.print(s);
//  Serial.print(" ");
//  Serial.println(b ? "true" : "false");
//}

/**
several overloading versions of the event function which sends and event string down the wire.
**/
void event(String type){
  Serial.print("event ");
  Serial.println(type);
}

void event(String type, String value){
  Serial.print("event ");
  Serial.print(type);
  Serial.print(" ");
  Serial.println(value);
}

void event(String type, int value){
  Serial.print("event ");
  Serial.print(type);
  Serial.print(" ");
  Serial.println(String(value));
}

void event(String type, int v1, int v2){
  Serial.print("event ");
  Serial.print(type);
  Serial.print(" ");
  Serial.print(String(v1));
  Serial.print(" ");
  Serial.println(String(v2));
}

/**
  event with multiple string values
*/
void event(String type, String v1, String v2){
  Serial.print("event ");
  Serial.print(type);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.print(v1);
  Serial.println();
}
