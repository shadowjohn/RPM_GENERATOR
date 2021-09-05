/*
 * RPM 訊號產生器
 * Author: 羽山秋人 (https://3wa.tw)
 * Release Date: 2021-09-05
 * 0~14000rpm
 * PWM Output PIN D1
 * VR Pin A0
 */
const int PWM_PIN = D1; 
const int VR = A0;  //使用 10KΩ
int val = 0;      //類比輸入
int min_val = 100;
int max_val = 1000;
int c = 0;
int HZ = 0; //產生的 HZ，0~234 // 234 * 60 = 14040 rpm
long full_duty = 0,half_duty = 0;
int RPM = 0;


/*   
轉速   60 轉 =  每分鐘    60 轉，每秒  1    轉，1轉 = 1          秒 = 1000.000 ms = 1000000us
轉速   100 轉 = 每分鐘   100 轉，每秒  1.67 轉，1轉 = 0.598802   秒 =  598.802 ms =  598802us
轉速   200 轉 = 每分鐘   200 轉，每秒  3.3  轉，1轉 = 0.300003   秒 =  300.003 ms =  300003us
轉速   600 轉 = 每分鐘   600 轉，每秒  10   轉，1轉 = 0.1        秒 =  100.000 ms =  100000us
轉速  1500 轉 = 每分鐘  1500 轉，每秒  25   轉，1轉 = 0.04       秒 =   40.000 ms =   40000us
轉速  6000 轉 = 每分鐘  6000 轉，每秒  60   轉，1轉 = 0.01666... 秒 =   16.667 ms =   16667us
轉速 14000 轉 = 每分鐘 14000 轉，每秒 233.3 轉，1轉 = 0.0042863. 秒 =    4.286 ms =    4286us
轉速 14060 轉 = 每分鐘 14060 轉，每秒 240   轉，1轉 = 0.0041667. 秒 =    4.167 ms =    4167us
轉速 16000 轉 = 每分鐘 16000 轉，每秒 266.6 轉，1轉 = 0.0037500. 秒 =    3.750 ms =    3750us
*/  
void setup() {
  //開啟串列埠 功能，並設定鮑率 1000000
  Serial.begin(1000000);
  // put your setup code here, to run once:
  pinMode(PWM_PIN, OUTPUT);
  pinMode(VR, INPUT);
  digitalWrite(PWM_PIN,LOW);
  val = analogRead(VR);  //讀取 VR 腳的類比輸入  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  val = analogRead(VR);  //讀取 VR 腳的類比輸入 
  //自動修正可變電阻範圍
  min_val = (val<min_val)?val:min_val;
  max_val = (val>max_val)?val:max_val; 
  
  HZ = map(val,min_val,max_val,1,234); // 顯示 HZ，用來對照三用電表
  full_duty = 1000000 / HZ; // 60rpm ~ 14000rpm  
  RPM = map(val,min_val,max_val,60,14060);
  half_duty = full_duty/2;
  //正半，負半，方波
  digitalWrite(PWM_PIN,HIGH);
  delayMicroseconds(half_duty);
  digitalWrite(PWM_PIN,LOW);
  delayMicroseconds(half_duty);
  Serial.println(RPM);  
}
