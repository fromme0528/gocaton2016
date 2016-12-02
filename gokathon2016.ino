
#include <LiquidCrystal.h>
#define MAX 3
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int key1 =10; // key1 : stop/play
int key2 =9; // key2 : next song

byte sharpminor[8] = {
  B01010,
  B11111,
  B01010,
  B11111,
  B01010,
  B00000,
  B11111,
  B00000
};

byte flatminor[8] = {
   B10000,
   B10000,
   B11111,
   B10001,
   B11111,
   B00000,
   B11111,
   B00000
};

void setup() {
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  
  lcd.begin(8,2);
  Serial.begin(9600);

  //Example Songs
  char song[MAX][230] = {"5.4.3.2.1.....EX......Fm........EX....Fm........FO....E...CO..FO......AX......C#........Fm....BX........FO......C#......Fm....BX......F#FO....B...C#..", // cheer up
                        "5.4.3.2.1.....G.......D.......E-......D.......C.......D.......G.......D.......G.......D.......G.......D.......C.......D.......G.......",//걱정말아요그대
                        "5.4.3.2.1.....G.........D.......E-......G.......C.......G.......A-......D.......G.................E-......B-......C.......G.......A-......D...........G...D.......E-..........G.....C.......G.......A.A-......D.......G......."};//너에게난
                        
//  char c[600];  //= "FO..BX......F#......EX......F-........EX......F-Ab..FO..B...E.......FO......AX......C#......F-......BX........FO......C#......F.F-..Bb......F#........";   
  // b- == X #-==O
  char buf[8];
  char buf2[8];
  int i,j;
  int songnum=0;

  lcd.createChar(0, sharpminor); // byte(0)
  lcd.createChar(1, flatminor); //byte(1)

  
  j=0;
while(1){

  //Stoping
  while(1){
    delay(200);
    //stop -> play

  if(songnum==0){
    lcd.setCursor(0,0);
     lcd.print("Cheer Up");
     lcd.setCursor(0,1);
     lcd.print("        ");
    }else if(songnum==1){
    lcd.setCursor(0,0);
     lcd.print("Don't Wo");
     lcd.setCursor(0,1);
     lcd.print("rry     ");
    }

    else if(songnum==2){
    lcd.setCursor(0,0);
     lcd.print("Me To Yo");
     lcd.setCursor(0,1);
     lcd.print("u       ");
    }

    if(digitalRead(key1) ==HIGH){
            break;
    }
    //Next song and Play
    if(digitalRead(key2) == HIGH){
      songnum=(songnum+1)%MAX;
      digitalWrite(key1,LOW);        
    }
    Serial.print(digitalRead(key2));
    delay(300);
  }

  
  //Playing
  j=0;
  while(1)
  {    
    if(song[songnum][j]=='\0')
      break;

    for(i=0;i<8;i++)
    {
      buf[i]=song[songnum][j+i];
      buf2[i]=song[songnum][j+i+8];
    }
    j=j+2;
    lcd.setCursor(0,0);
     for(i=0;i<8;i++)
    {
       if(buf[i]=='X')
          lcd.write(byte(1));
       else if(buf[i]=='O')
          lcd.write(byte(0));
       else
          lcd.print(buf[i]);
    }
    lcd.setCursor(0,1);
    for(i=0;i<8;i++)
    {
       if(buf2[i]=='X')
          lcd.write(byte(1));
       else if(buf2[i]=='O')
          lcd.write(byte(0));
       else
          lcd.print(buf2[i]);
    }
    delay(400);

    Serial.print(digitalRead(key2));
//     //play -> stop
//    if(digitalRead(key1) ==HIGH){
//      break;
//    }
    //Next song

    //Next song and Play
    if(digitalRead(key2) == HIGH){
      songnum=(songnum+1)%MAX;
      digitalWrite(key1,LOW);
      break;
    }

    /*if(digitalRead(key2) == LOW){
      //Change Arr C!!!!
    }*/
  }


}
}

void loop() {
  // put your main code here, to run repeatedly:
}
