#include <WiFi.h>
/* 1 测试wifi扫描*/


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  if(WiFi.status() == WL_NO_SHIELD){
      Serial1.println("WiFi shield not present");
      while(true);
  }
}




void loop() {
  // put your main code here, to run repeatedly:
}
