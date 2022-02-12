#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>

int sw = 22;
int ledb = 5;
int ldr1 = 33;
int ldr2 = 34;
int led1 = 4;
int led2 = 13;

const char* ssid = "Ponk-2.4G";
const char* password ="9199218932";
const char* urlpost = "https://ecourse.cpe.ku.ac.th/exceed09/api/change/";

char str[50];
static int ledbstatus = 0;
static int led1status = 0;
static int led2status = 0;

const int _size = 2*JSON_OBJECT_SIZE(4);

StaticJsonDocument<_size> JSONPost;

void setup() {
  xTaskCreatePinnedToCore(
    Task1,
    "Task 1",
    1024*32,
    NULL,
    1,
    NULL,
    0
  );
  xTaskCreatePinnedToCore(
    Task2,
    "Task 2",
    1024*32,
    NULL,
    1,
    NULL,
    1
  );
  pinMode(sw, INPUT);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(ledb , OUTPUT);
  pinMode(led1 , OUTPUT);
  pinMode(led2 , OUTPUT);
  digitalWrite(ledb,HIGH);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  Serial.begin(115200);
}

void test(){
  Serial.print("room1: ");
  Serial.println(ledbstatus);
  Serial.print("room2: ");
  Serial.println(led1status);
  Serial.print("room3: ");
  Serial.println(led2status);
  Serial.println();
}
void WiFi_Connect(){
  WiFi.disconnect();
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi.....");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

void _post(int a_post,int b_post,int c_post){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    http.begin(urlpost);
    http.addHeader("Content-Type", "application/json");

    JSONPost["room1"] = a_post;
    JSONPost["room2"] = b_post;
    JSONPost["room3"] = c_post;
    serializeJson(JSONPost, str);
    int httpCode = http.POST(str);

    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }
    else{
      Serial.println(httpCode);
      Serial.println("ERROR on HTTP Request");
    }
  }
  else{
    WiFi_Connect();
  }
  delay(100);
}

void Task1(void *parameter){
  while(1){
    if(analogRead(ldr1) > 3500){
      digitalWrite(led1, HIGH);
      Serial.println("2IN");
      led1status = 1;
      test();
      _post(ledbstatus,led1status,led2status);
      delay(100);
      while(analogRead(ldr1) > 3500){
        delay(200);
        if(analogRead(ldr1) < 3500){
          led1status = 0;
          test();
          _post(ledbstatus,led1status,led2status);
          delay(100);
          Serial.println("2OUT");
          break;
        }
      }
    }
    else{
      digitalWrite(led1, LOW);
      led1status = 0;
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void Task2(void *parameter){
  while(1){
    digitalWrite(ledb, !digitalRead(sw));
    if(digitalRead(sw) == 1){
      ledbstatus = 1;
      test();
      _post(ledbstatus,led1status,led2status);
      delay(100);
      Serial.println("1IN");
    }
    while(digitalRead(sw) !=  0){
        delay(200);
        if(digitalRead(sw) == 0){
          ledbstatus = 0;
          test();
          _post(ledbstatus,led1status,led2status);
          delay(100);
          Serial.println("1OUT");
          break;
        }
      }
  ledbstatus = 0;
  vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void loop() {
      if(analogRead(ldr2) > 2500){
      led2status = 1;
      digitalWrite(led2, HIGH);
      Serial.println("3IN");
      test();
      _post(ledbstatus,led1status,led2status);
      delay(100);
      while(analogRead(ldr2) > 2500){
        delay(200);
        if(analogRead(ldr2) < 2500){
          led2status = 0;
          test();
         _post(ledbstatus,led1status,led2status);
          delay(100);
          Serial.println("3OUT");
          break;
        }
      }
    }
    else{
      led2status = 0;
      digitalWrite(led2, LOW);
    }
    delay(100);
}
