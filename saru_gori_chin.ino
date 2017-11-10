// saru gorira chinpanji- game
// taniguchi kotaro
// https://www.youtube.com/channel/UCBqoH73F31mbhyLkG3wj1HA

#include <EEPROM.h>
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 display;
ArduboyPlaytune tunes(display.audio.enabled);

void setup() {
  display.begin();

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
  // if not a DevKit
  tunes.initChannel(PIN_SPEAKER_2);
#else
  // if it's a DevKit
  tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
  tunes.toneMutesScore(true);       // mute the score when a tone is sounding
#endif
}

#define EEPROM_SCORES EEPROM_STORAGE_SPACE_START

#define ONPU_HI_16    0
#define ONPU_LO_16   64
#define ONPU_HI_8     0
#define ONPU_LO_8   128
#define ONPU_HI_53    0
#define ONPU_LO_53  192
#define ONPU_HI_4     1
#define ONPU_LO_4     0
#define ONPU_HI_26    1
#define ONPU_LO_26  128
#define ONPU_HI_2     2
#define ONPU_LO_2     0
#define ONPU_HI_1     4
#define ONPU_LO_1     0

// 【アルトサックス用無料楽譜】アルフォード作曲『ボギー大佐』
// 趣味のトランペット　無料の移調楽譜もいっぱい　ヘ音もあるよ
// http://chankon2.seesaa.net/article/420299436.html

PROGMEM const byte saruoto_1 [] = {
0x90, 79, ONPU_HI_8,  ONPU_LO_8,
0x90, 76, ONPU_HI_26, ONPU_LO_26,
0x80, 0xf0
};
PROGMEM const byte saruoto_2 [] = {
//0x80,    ONPU_HI_8,  ONPU_LO_8, 
0x90, 76, ONPU_HI_8,  ONPU_LO_8,
0x90, 77, ONPU_HI_8,  ONPU_LO_8,
0x90, 79, ONPU_HI_8,  ONPU_LO_8,
0x80, 0xf0
};
PROGMEM const byte saruoto_3 [] = {
0x90, 88, ONPU_HI_4,  ONPU_LO_4,
0x90, 88, ONPU_HI_4,  ONPU_LO_4,
0x90, 84, ONPU_HI_2,  ONPU_LO_2,
0x80, 0xf0
};
PROGMEM const byte saruoto_4 [] = {
0x90, 79, ONPU_HI_8,  ONPU_LO_8,
0x90, 76, ONPU_HI_4,  ONPU_LO_4,
0x80, 0xf0
};
PROGMEM const byte saruoto_5 [] = {
//0x80,    ONPU_HI_8,  ONPU_LO_8, 
0x90, 76, ONPU_HI_8,  ONPU_LO_8,
0x90, 77, ONPU_HI_8,  ONPU_LO_8,
0x90, 76, ONPU_HI_8,  ONPU_LO_8,
0x80, 0xf0
};
PROGMEM const byte saruoto_6 [] = {
0x90, 79, ONPU_HI_4,  ONPU_LO_4,
0x90, 79, ONPU_HI_4,  ONPU_LO_4,
0x90, 77, ONPU_HI_2,  ONPU_LO_2,
0x80, 0xf0
};
PROGMEM const byte saruoto_7 [] = {
0x90, 77, ONPU_HI_8,  ONPU_LO_8,
0x90, 74, ONPU_HI_26, ONPU_LO_26,
0x80, 0xf0
};
PROGMEM const byte saruoto_8 [] = {
//0x80,    ONPU_HI_8,  ONPU_LO_8, 
0x90, 74, ONPU_HI_8,  ONPU_LO_8,
0x90, 76, ONPU_HI_53, ONPU_LO_53,
0x90, 77, ONPU_HI_16, ONPU_LO_16,
0x80, 0xf0
};
PROGMEM const byte saruoto_9 [] = {
0x90, 79, ONPU_HI_8, ONPU_LO_8,
0x90, 76, ONPU_HI_26, ONPU_LO_26,
0x80, 0xf0
};
PROGMEM const byte saruoto_10 [] = {
//0x80,    ONPU_HI_8, ONPU_LO_8, 
0x90, 76, ONPU_HI_8, ONPU_LO_8,
0x90, 78, ONPU_HI_53, ONPU_LO_53,
0x90, 76, ONPU_HI_16, ONPU_LO_16,
0x80, 0xf0
};
PROGMEM const byte saruoto_11 [] = {
0x90,74, ONPU_HI_8, ONPU_LO_8,
0x90,79, ONPU_HI_4, ONPU_LO_4,
0x80,0xf0
};
PROGMEM const byte saruoto_12 [] = {
0x90,76, ONPU_HI_8, ONPU_LO_8,
0x90,78, ONPU_HI_53, ONPU_LO_53,
0x90,74, ONPU_HI_53, ONPU_LO_53,
0x80,0xf0
};
PROGMEM const byte saruoto_13 [] = {
0x90,81, ONPU_HI_8, ONPU_LO_8,
0x90,79, ONPU_HI_1, ONPU_LO_1,
0x80,0xf0
};

void loop() {
  enum game_state {
    state_menu,
    state_ranking,
    state_game,
  };
  enum game_fase {
    fase_start,
    fase_1_saru,
    fase_2_gorira,
    fase_3_chinpanji,
    fase_4_saru,
    fase_5_gorira,
    fase_6_chinpanji,
    fase_7_saru,
    fase_8_gorira,
    fase_9_saru,
    fase_10_gorira,
    fase_11_saru,
    fase_12_gorira,
    fase_13_saru,
  };
  enum game_state state = state_menu;

  unsigned int hi_score[10 + 1] = {0};

  int count = 0;
  bool now_push = false;
  enum game_fase fase = fase_start;
  unsigned int score = 0;
  unsigned int bonus = 1;
  bool super_bonus = false;

  unsigned long currTime;
  unsigned long prevTime = 0;
  #define FPSDELAY      1000/30

//  for (int i = 0; i < 10; i++) {
//    EEPROM.update(i*2+EEPROM_SCORES,   0xFF);
//    EEPROM.update(i*2+1+EEPROM_SCORES, 0xFF);
//  }

  for (int i = 0; i < 10; i++) {
    hi_score[i] = EEPROM.read(i*2+EEPROM_SCORES);
    hi_score[i] <<= 8;
    hi_score[i] += EEPROM.read(i*2+1+EEPROM_SCORES);
    if (hi_score[i] == 0xFFFF) {
      hi_score[i] = 0;
      break;
    }
  }

  while (true) {
    currTime = millis();
    if ( currTime > prevTime + FPSDELAY ) {
      prevTime = currTime;
      count++;
      byte input = display.buttonsState();
      display.clear();
      switch (state) {
        case state_menu:
          if (count > 100) {
            state = state_ranking;
            count = 0;
            break;
          }
          display.setCursor(50,10); display.print(F("SARU"));
          display.setCursor(45,20); display.print(F("GORIRA"));
          display.setCursor(35,30); display.print(F("CHINPANJI-"));
          display.setCursor(50,40); display.print(F("GAME"));
          if (input & B_BUTTON) {
            state = state_game;
            count = 0;
            fase = fase_start;
            score = 0;
            bonus = 1;
            super_bonus = false;
          }
          break;
       case state_ranking:
          if (input & A_BUTTON) {
            state = state_menu;
            count = 0;
            break;
          }
          display.setCursor(35,0); display.print(F("HIGH SCORE"));
          display.setCursor(0,10); display.print(F("1:"));display.print(hi_score[0]);
          display.setCursor(0,20); display.print(F("2:"));display.print(hi_score[1]);
          display.setCursor(0,30); display.print(F("3:"));display.print(hi_score[2]);
          display.setCursor(0,40); display.print(F("4:"));display.print(hi_score[3]);
          display.setCursor(0,50); display.print(F("5:"));display.print(hi_score[4]);
          display.setCursor(65,10); display.print(F(" 6:"));display.print(hi_score[5]);
          display.setCursor(65,20); display.print(F(" 7:"));display.print(hi_score[6]);
          display.setCursor(65,30); display.print(F(" 8:"));display.print(hi_score[7]);
          display.setCursor(65,40); display.print(F(" 9:"));display.print(hi_score[8]);
          display.setCursor(65,50); display.print(F("10:"));display.print(hi_score[9]);
          break;
       case state_game:
         if (count > 40) {
           fase = fase_start;
           bonus = 1;
           if (count > 100) {
             bool save_flag = false;
             for (int i = 9; i >= 0; i--) {
               if (score > hi_score[i]) {
                 hi_score[i + 1] = hi_score[i];
                 hi_score[i] = score;
                 save_flag = true;
               }
             }
             if (save_flag) {
               for (int i = 0; i < 10; i++) {
                 EEPROM.update(i*2+EEPROM_SCORES,   ((hi_score[i]) >> 8 & 0xFF));
                 EEPROM.update(i*2+1+EEPROM_SCORES, hi_score[i] & 0xFF);
               }
             }
             state = state_ranking;
             count = 0;
             break;
           }
         }
         //display.setCursor(0,10); display.print(F("COUNT:"));display.print(count);

         if (input & (A_BUTTON | B_BUTTON)) {
           if (!tunes.playing()) {
             if (!now_push) {
               count = 0;
               switch (fase) {
                 case fase_start:
                 case fase_13_saru:
                   super_bonus = false;
                   if (input & B_BUTTON) {
                     fase = fase_1_saru;
                     tunes.playScore(saruoto_1);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_1_saru:
                   if (input & B_BUTTON) {
                     fase = fase_2_gorira;
                     tunes.playScore(saruoto_2);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_2_gorira:
                   if (input & B_BUTTON) {
                     fase = fase_3_chinpanji;
                     tunes.playScore(saruoto_3);
                     score = score + bonus;
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_3_chinpanji:
                   if (input & B_BUTTON) {
                     fase = fase_4_saru;
                     tunes.playScore(saruoto_4);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_4_saru:
                   if (input & B_BUTTON) {
                     fase = fase_5_gorira;
                     tunes.playScore(saruoto_5);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_5_gorira:
                   if (input & B_BUTTON) {
                     fase = fase_6_chinpanji;
                     tunes.playScore(saruoto_6);
                     score = score + bonus;
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_6_chinpanji:
                   if (input & A_BUTTON) {
                     fase = fase_7_saru;
                     tunes.playScore(saruoto_7);
                     super_bonus = true;
                   } else {
                     fase = fase_1_saru;
                     tunes.playScore(saruoto_1);
                     bonus = 1;
                   }
                   break;
                 case fase_7_saru:
                   if (input & A_BUTTON) {
                     fase = fase_8_gorira;
                     tunes.playScore(saruoto_8);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_8_gorira:
                   if (input & A_BUTTON) {
                     fase = fase_9_saru;
                     tunes.playScore(saruoto_9);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_9_saru:
                   if (input & A_BUTTON) {
                     fase = fase_10_gorira;
                     tunes.playScore(saruoto_10);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_10_gorira:
                   if (input & A_BUTTON) {
                     fase = fase_11_saru;
                     tunes.playScore(saruoto_11);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_11_saru:
                   if (input & A_BUTTON) {
                     fase = fase_12_gorira;
                     tunes.playScore(saruoto_12);
                   } else {
                     fase = fase_start;
                   }
                   break;
                 case fase_12_gorira:
                   if (input & A_BUTTON) {
                     fase = fase_13_saru;
                     tunes.playScore(saruoto_13);
                     bonus++;
                   } else {
                     fase = fase_start;
                   }
                   break;
                 }
               now_push = true;
             }
           } else {
             if (super_bonus) {
               score += bonus;           
             }
           }
         }
         else {
           now_push = false;
         }

         display.setCursor(0,0); display.print(F("SCORE:"));display.print(score);
         display.print(F(" (x"));display.print(bonus);display.print(F(")"));
         switch (fase) {
           case fase_1_saru:
           case fase_4_saru:
             display.setCursor(50,30); display.print(F("SARU"));
             break;
           case fase_2_gorira:
           case fase_5_gorira:
             display.setCursor(45,30); display.print(F("GORIRA"));
             break;
           case fase_3_chinpanji:
           case fase_6_chinpanji:
             display.setCursor(35,30); display.print(F("CHINPANJI-"));
             break;
           case fase_7_saru:
           case fase_9_saru:
           case fase_11_saru:
           case fase_13_saru:
             display.setCursor(35,30); display.print(F("SUPER SARU"));
             break;
           case fase_8_gorira:
           case fase_10_gorira:
           case fase_12_gorira:
             display.setCursor(30,30); display.print(F("SUPER GORIRA"));
             break;
         }
         break;
      }
      display.display();  
    }
  }
}

