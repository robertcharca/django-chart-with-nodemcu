# Sending data with NodeMCU-M (ESP8266)

## Table of contents



## Overview

NodeMCU is a totally different client from your PC. This means that, if you want to create a request, the url should be different than `127.0.0.1` or `localhost`. This section will give you recommendations for creating your C++ code for connecting to your local o remote network and creating HTTP requests.

## WiFi connection

Remote communications require an Ethernet or WiFi connection in your NodeMCU. For WiFi connection, it's important to add `ESP8266WiFi` library in the `setup()` function. The official documentation recommends this way:

```
    #include <ESP8266WiFi.h>

    void setup()
    {
    Serial.begin(115200);
    Serial.println();

    WiFi.begin("network-name", "pass-to-network");

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    }
```

You can change some parts if you want to, but I recommend to keep the code inside of the 'while' loop statement block because It will indicate if your code is connecting properly. Generally, changing the 'while' loop statement with a conditional statement doesn't work very well because `WiFi.status()` will just iterate one time. Remember that `setup()` function just executes once.

If you want a deeper explanation of `ESP8266WiFi` library, you can go to this [link](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html).

## HTTP requests

### HTTPClient and WiFiClient

For HTTP requests in NodeMCU, we need `<WiFiClient.h>` and `<ESP8266HTTPClient.h>` for **local** connections. These libraries comes in ESP8266 by default.

When you've included these libraries, it's important to declare them as an object, in this way:

```
    WiFiClient client;  
    HTTPClient http;
```

After that, you must especify this code inside of the `loop` function:

```
    http.begin(client, "http://url.com");
    http.addHeader("Content-Type", "type");
```

### "begin" method

The `begin` method is for starting your http client. Note that it requires your WiFiClient object and a url. 

In the case of 'url', it's important to apply a url that is not a HTTPS because `<WifiClient.h>` refers to http sites only. In addition, in order to save memory, you can declare your 'url' variable as `char*`.

In the case of 'client', it's important to consider that newer version o esp8266 board requires this object for HTTP requests. There's the possibility that you'd watched a YouTube tutorial that doesn't have this object, but for avoiding problems, add this in the 'begin' method.

### "addHeader" method

The `addHeader` method especifies what type of content your header will be. Even though there are four to seven [common types](https://stackoverflow.com/questions/23714383/what-are-all-the-possible-values-for-http-content-type-header), the most recommended are `application/json`, `text/html`, `text/plain` and `text/xml` for this device. If you want to test others, there's not problem (I think).

### HTTP methods

After writing these lines shown above, you can declare your HTTP methods. There are the `GET()`, `DELETE()`, `POST()`, `PUT()` and `PATCH()` methods to use, but you must especify the right url if you want to make a PUT, PATCH or DELETE request. 

In the case of getting an answer, you only get a HTTP code as an integer like 100, 200, 300, 404, 500 or `-1` due to a connection error. That's why you must write this line of code:

```
    int response = http.GET() //example
``` 

After declaring your http code variable, you can verify with your code if the request is succesfully done with this:

```
    if(response > 0){
        Serial.println("Status code: " + String(response));
        
        if(response == 200){
            String reponse = http.getString();
            Serial.println(response);
        }
    } else {
        Serial.println(response);
    }
```

### "end" method

Finally, it's important to close your http request, and this is done applying the `end` method. You must write it as:

```
    http.end();
```

The final result is this piece of code for HTTP requests:

```
    WiFiClient client;  
    HTTPClient http;

    http.begin(client, "http://url.com");
    http.addHeader("Content-Type", "text/plain");

    int response = http.GET()

    if(response > 0){
        Serial.println("Status code: " + String(response));
        
        if(response == 200){
            String reponse = http.getString();
            Serial.println(response);
        }
    } else {
        Serial.println(response);
    }

    http.end();

```

You can adapt your project code for sending a request depending on the circumstances. You can add a `delay function` or the `algorithm for concurrency` to specify your delay time. 

### Handling -1 code status

When you're testing your code, you could get a `-1` response code after sending a request. Here you can see some things to consider in case you got this response:

- *Check if your code is connected to your local network*. For this, you can apply this code to verify if your code is connect in each iteration:
  
  ```
    if(WiFi.status()== WL_CONNECTED) {
        WiFiClient client;  
        HTTPClient http;

        http.begin(client, "http://url.com");
        http.addHeader("Content-Type", "text/plain");

        int response = http.GET()

        if(response > 0){
            Serial.println("Status code: " + String(response));
            
            if(response == 200){
                String reponse = http.getString();
                Serial.println(response);
            }
        } else {
            Serial.println(response);
        }

        http.end();

        delay(1000);
    }
  ```

- *Check if you're making the request to the right url*. As we saw at the beginnning of this page, we must not create request directed to a `localhost` url, like `http://127.0.0.10` or `http://localhost` due to we're sending request to another device. As a recommendation, you can send a request to an url that has the same ip of your network. For example, if you write `ipconfig` in CMD (Windows) or `ifconfig` in Bash (Linux), you will notice that both have an IPv4 Address (in Bash you can see it as "inet"). This ip address could be used for testing your requests in a local enviroment.  
> **Launching Django with a different link**
> 
> If you want to configure your Django link with another different from your localhost link, you can write the following command:
> ```
>   python3 manage.py runserver 182.129.0.10:8000 //example
> ```

## Arduino JSON

Still in progress.