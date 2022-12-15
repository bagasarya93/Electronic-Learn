
#include <Arduino.h>
#include <WiFi.h>

// Replace with your network credentials 
const char* ssid = "Redmi"; 
const char* password = "12345678"; 

// Set web server port number to 80 
WiFiServer server(80);

// Variable to store the HTTP request String header;
String header;
String linkcanvas = "https://cdn.rawgit.com/Mikhus/canvas-gauges/gh-pages/download/2.1.7/all/gauge.min.js";
// Declare the pins to which the LEDs are connected 
int greenled = 26;
int redled = 27; 

String greenstate = "off";// state of green LED
String redstate = "off";// state of red LED

//NTC
int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
String TempC ="0";

void setup() {
  Serial.begin(115200);
 // Set the pinmode of the pins to which the LEDs are connected and turn them low to prevent flunctuations
  pinMode(ThermistorPin, INPUT);
  pinMode(greenled, OUTPUT);
  pinMode(redled, OUTPUT);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
  //connect to access point
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// this will display the Ip address of the Pi which should be entered into your browser
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /green/on") >= 0) {
              Serial.println("green on");
              greenstate = "on";
              digitalWrite(greenled, HIGH);
            } else if (header.indexOf("GET /green/off") >= 0) {
              Serial.println("green off");
              greenstate = "off";
              digitalWrite(greenled, LOW);
            } else if (header.indexOf("GET /red/on") >= 0) {
              Serial.println("red on");
              redstate = "on";
              digitalWrite(redled, HIGH);
            } else if (header.indexOf("GET /red/off") >= 0) {
              Serial.println("red off");
              redstate = "off";
              digitalWrite(redled, LOW);
            }

            else if (header.indexOf("GET /") >= 0) {
               //NTC
                Vo = analogRead(ThermistorPin);
                R2 = R1 * (4095.0 / (float)Vo - 1.0);
                logR2 = log(R2);
                T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
                Tc = T - 273.15;
                Tf = (Tc * 9.0)/ 5.0 + 32.0;
                TempC = String(Tc);}

            // Edit Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            //head.begin
            client.println("<head>");
            client.println("<title>ESP32 WebServer</title>");
          
            //--JS--
            client.print("<script");
            client.print("src=""https://cdn.rawgit.com/Mikhus/canvas-gauges/gh-pages/download/2.1.7/all/gauge.min.js\">");
            client.println("</script>");
            //--CSS--
            client.println("<style>");
            client.println("html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color:#ffffff;} ");
            client.println("button {background-color: #195B6A; border: none; color: white; padding: 16px 40px;} ");
            client.println(".button2 {background-color: #77878A;} ");
            client.println(".tittle-Temp{font-style:italic;} ");
            client.println("</style>");
            //head.end
          
            //body.begin
            client.println("<h1>ESP 32 Web Server </h1> ");

             // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>green - State " + greenstate + "</p>");
            // If the green LED is off, it displays the ON button       
            if (greenstate == "off") {
              client.println("<p><a href=\"/green/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/green/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27 
            client.println("<p>red - State " + redstate + "</p>");
            // If the red LED is off, it displays the ON button       
            if (redstate == "off") {
              client.println("<p><a href=\"/red/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/red/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //Display Temperature Gauge
            client.println(" <h2>Measure Temperature</h2> ");

            client.println("<img src=""https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRhFjL98mtVQ72T7sDMrj7OHWzreA7h7PZGuA&usqp=CAU\">");
            client.println("");
            client.println("<p>Temperature(C) = " "");
            client.print(TempC);
            client.println("</p>");


            
            client.println("</body>");
            client.println("</html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    Serial.println(Tc);
    
  }
}

