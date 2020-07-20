#include <Arduino.h>

struct TaskParams
{
  int16_t hoge;
  int16_t piyo;
};

TaskHandle_t th[2];
TaskParams tParams;

void initialize_params(TaskParams &params)
{
  params.hoge = 0;
  params.piyo = 0;
}

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

void test_for_structure(void *param)
{
  while(1)
  {
    TaskParams *temp_param = (TaskParams *)param;

    (*temp_param).hoge += 1;
    (*temp_param).piyo -= 1;
    Serial.print("hoge in test():" + String((*temp_param).hoge));
    Serial.println(", piyo in test():" + String((*temp_param).piyo));
    delay(100);
  }
}

void setup()
{
  initialize_params(tParams);
  // put your setup code here, to run once:
  Serial.begin(115200);
  // xTaskCreatePinnedToCore(test, "test", 4096, NULL, 10, &th[0], 0);
  // xTaskCreatePinnedToCore(test, "test", 4096, &hoge, 10, &th[0], 0);
  xTaskCreatePinnedToCore(test_for_structure, "test_for_structure", 4096, &tParams, 10, &th[0], 0);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Serial.println("hoge in loop():" + String(hoge));
  Serial.print("hoge in loop():" + String(tParams.hoge));
  Serial.println(", piyo in loop():" + String(tParams.piyo));
  delay(1000);
}