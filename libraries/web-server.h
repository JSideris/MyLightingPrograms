#include <WiFi_Generic.h>
#include <WiFiClient_Generic.h>
#include <WiFiNINA_Generic.h>
#include <WiFiNINA_Pinout_Generic.h>
#include <WiFiServer_Generic.h>
#include <WiFiSSLClient_Generic.h>
#include <WiFiStorage_Generic.h>
#include <WiFiUdp_Generic.h>

// TODO: make dynamic.
static char sssd[] = "Outpost 5";     //  your network SSID (name) between the " "
static char pass[] = "sideris5";      // your network password between the " "
static WiFiServer server(80);            //server socket

class WebServer{
	public: 

		int keyIndex = 0;                 // your network key Index number (needed only for WEP)
		int status = WL_IDLE_STATUS;      //connection status

		WiFiClient client;// = server.available();

		int ledPin = 2;

		WebServer(){
		}

		void start(){
			if(WiFi.status() != WL_NO_MODULE){
				connect_WiFi();
				server.begin();
			}
		}

		void loop(){
			// If wifi is set up, then do stuff.
			if(true){
				// If wifi is disconnected, try to reconnect once every ten seconds.
				status = WiFi.status();
				if(status != WL_CONNECTED){

				}
				else{
					
				}
			}
		}

		void checkForConnections(){
			client = server.available();

			if (client) {
				printWEB();
			}
		}

		// void printWifiStatus()
		// {
		// 	// print the SSID of the network you're attached to:
		// 	// Serial.print("SSID: ");
		// 	// Serial.println(WiFi.SSID());

		// 	// print your board's IP address:
		// 	IPAddress ip = WiFi.localIP();
		// 	// Serial.print("IP Address: ");
		// 	// Serial.println(ip);

		// 	// print the received signal strength:
		// 	long rssi = WiFi.RSSI();
		// 	// Serial.print("signal strength (RSSI):");
		// 	// Serial.print(rssi);
		// 	// Serial.println(" dBm");

		// 	// Serial.print("To see this page in action, open a browser to http://");
		// 	// Serial.println(ip);
		// }

		void connect_WiFi()
		{
			// attempt to connect to Wifi network:
			while (status != WL_CONNECTED)
			{
				// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
				status = WiFi.begin(sssd, pass);

				// wait 10 seconds for connection:
				delay(10000);
			}
		}

		void printWEB()
		{

			if (client)
			{								  // if you get a client,
				Serial.println("new client"); // print a message out the serial port
				String currentLine = "";	  // make a String to hold incoming data from the client
				while (client.connected())
				{ // loop while the client's connected
					if (client.available())
					{							// if there's bytes to read from the client,
						char c = client.read(); // read a byte, then
						Serial.write(c);		// print it out the serial monitor
						if (c == '\n')
						{ // if the byte is a newline character

							// if the current line is blank, you got two newline characters in a row.
							// that's the end of the client HTTP request, so send a response:
							if (currentLine.length() == 0)
							{

								// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
								// and a content-type so the client knows what's coming, then a blank line:
								client.println("HTTP/1.1 200 OK");
								client.println("Content-type:text/html");
								client.println();

								//create the buttons
								client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
								client.print("Click <a href=\"/L\">here</a> turn the LED off<br><br>");

								int randomReading = analogRead(A1);
								client.print("Random reading from analog pin: ");
								client.print(randomReading);

								// The HTTP response ends with another blank line:
								client.println();
								// break out of the while loop:
								break;
							}
							else
							{ // if you got a newline, then clear currentLine:
								currentLine = "";
							}
						}
						else if (c != '\r')
						{					  // if you got anything else but a carriage return character,
							currentLine += c; // add it to the end of the currentLine
						}

						if (currentLine.endsWith("GET /H"))
						{
							digitalWrite(ledPin, HIGH);
						}
						if (currentLine.endsWith("GET /L"))
						{
							digitalWrite(ledPin, LOW);
						}
					}
				}
				// close the connection:
				client.stop();
				Serial.println("client disconnected");
			}
		}
};











 
