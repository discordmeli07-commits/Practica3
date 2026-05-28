#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ProjectesSMX";
const char* password = "Hola1234";

const int pinLDR = 35;
const int pinLM35 = 34;
const int LED = 27;

WebServer server(80);

void enviarPaginaPrincipal() {
  int valorLDR = analogRead(pinLDR);
  float tempC = (analogRead(pinLM35) * 5.0 / 4095.0) * 100.0;

  String colorTemp = "#28a745";
  digitalWrite(LED, LOW); 

  if (tempC > 24.0) { 
    colorTemp = "#dc3545";
    digitalWrite(LED, HIGH);
  }

  String html = "<html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; background-color: #f0f2f5; }";
  html += ".card { padding: 30px; color: white; display: inline-block; border-radius: 15px; margin: 20px; box-shadow: 0 4px 8px rgba(0,0,0,0.2); }";
  html += "h1 { color: #333; }";
  html += "</style></head><body>";
  html += "<h1>Monitorització Sala CPD</h1>";
  html += "<div class='card' style='background-color:" + colorTemp + ";'>";
  html += "<h2>Temperatura</h2>";
  html += "<h1>" + String(tempC, 1) + " °C</h1>";
  html += "</div>";
  html += "<div class='card' style='background-color: #007bff;'>";
  html += "<h2>Nivell Llum (LDR)</h2>";
  html += "<h1>" + String(valorLDR) + "</h1>";
  html += "</div>";
  html += "<br><br><a href='/credits' style='text-decoration:none; color:blue;'>Veure Crèdits</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void credits() {
  String html = "<html><head><meta charset='UTF-8'></head><body style='text-align:center; font-family:sans-serif;'>";
  html += "<h1>Informació del Projecte</h1>";
  html += "<p>Aquest dashboard ha estat creat per l'equip de SMX.</p>";
  html += "<h3>Desenvolupador: Dani</h3>";
  html += "<a href='/'>Tornar al Dashboard</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
