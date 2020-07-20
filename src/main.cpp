#include <Arduino.h>

int hoge = 1;
int piyo = 10;

TaskHandle_t th[2];

void test(void *param)
{
  while(1)
  {
    int *temp_hoge = (int *)param;

    *temp_hoge = *temp_hoge + 1;
    Serial.println("hoge in test():" + String(*temp_hoge));
    delay(100);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // xTaskCreatePinnedToCore(test, "test", 4096, NULL, 10, &th[0], 0);
  xTaskCreatePinnedToCore(test, "test", 4096, &hoge, 10, &th[0], 0);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("hoge in loop():" + String(hoge));
  delay(1000);
}