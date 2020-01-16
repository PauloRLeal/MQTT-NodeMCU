#include <ESP8266WiFi.h>


#define ledsala 16

const char* ssid = "Francisco";
const char* senha = "francisco20181tim0042";

WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  delay(10);

  pinMode(ledsala,OUTPUT);
  digitalWrite(ledsala, HIGH);
  
  WiFi.begin(ssid, senha);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado com sucesso a rede " + String(ssid));

  server.begin();
  Serial.println("Servidor inicializado!");

  Serial.print("Utilize o seguinte IP: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop(){
  WiFiClient cliente = server.available();
  if(!cliente){
    return;
  }

  String req = cliente.readStringUntil('\r');
  cliente.flush();

  String text = "";

  text += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  text += "<head>";
  text += "<meta charset=\"utf-8\">";
  text += "</head>";
  text += "<title>Página de controle</title>";
  text += "<body style=\"background: #E06F57;\">";
  text += "<header style=\"background: #F1D7D1; position: relative; height: 60px; border-radius: 0px 0px 50px 50px; text-align: center; margin: 10px 10px 30px 10px; font-size: 24px; font-weight: bold;\">Sistemas de gerenciamento eletrônico</header>";
  text += "<article style=\"background: #C2B6B3; position: relative; height: 100px; text-align: center; font-size: 16px; border-radius: 10px 10px 10px 10px;\">Esse servidor é responsável por monitorar toda a rede eletrônica e elétrica do seu Hardware. Fique à vontade para utilizar como desejar!</article>";
  text += "<center><table border=\"0\" style=\"align-items: center; text-align: center; min-height: 300px; min-width: 800px; font-size: 16px; background: #E528A0; border-radius: 10px 10px 10px 10px;\">";
  text += "<tr><td><label style=\"font-size: 18px; font-weight: bold;\">Luz da sala: </label></td><td><a href=\"ledon\"><button style=\"width: 200px; height: 40px; background: #2F90C0; border-radius: 10px 10px 10px 10px; font-size: 16px; font-weight: bold;\">Ligar</button></a></td><td><a href=\"ledoff\"><button style=\"width: 200px; height: 40px; background: #E52831; border-radius: 10px 10px 10px 10px; font-size: 16px; font-weight: bold;\">Desligar</button></a></td></tr><br><br>";
  text += "<td colspan=\"3\"><hr></td>";
  text += "<tr><td><labell style=\"font-size: 18px; font-weight: bold;\">Gerador: </label></td><td><a href=\"geradoron\"><button style=\"width: 200px; height: 40px; background: #2F90C0; border-radius: 10px 10px 10px 10px; font-size: 16px; font-weight: bold;\">Ligar</button></a></td><td><a href=\"geradoroff\"><button style=\"width: 200px; height: 40px; background: #E52831; border-radius: 10px 10px 10px 10px; font-size: 16px; font-weight: bold;\">Desligar</button></a></td></tr><br><br>";
  text += "</table></center>";
  text += "<footer>";
  text += "<p><center><labell style=\"font-size: 18px; font-weight: bold;\">Sistema desenvolvido por Paulo Mec</label></center></p></footer>";
  text += "</body>";
  text += "</html>\n";
  cliente.print(text);
  cliente.flush();

  if(req.indexOf("ledon") != -1){
    digitalWrite(ledsala, HIGH);
  }else if(req.indexOf("ledoff") != -1){
    digitalWrite(ledsala, LOW);
  }
  cliente.stop();
}
