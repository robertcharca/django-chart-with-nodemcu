# React chart with Django and NodeMCU-M 

## Overview

This project is made for documenting all the process applied for getting data from an Arduino to send it, through an HTTP request, to a Django API and show it with React and the library Chart js. 

Here you can see the necessary steps for installing all tools in this project. If you want to see a detailed explanation of every aspect, it's better to read the README file of each directory. 

## NodeMCU-M (ESP8266)

### Installing ESP8266 

In your Arduino IDE, go to `File`, in your upper menu, and select `Preferences`.

Inside of your "Preferences" window, go to `Additional Boards Manager URLs` and paste this link: 

    https://arduino.esp8266.com/stable/package_esp8266com_index.json

If you already have one board, type a comma to add the link given before.

When you've applied this link, go to `Tools` > `Board` > `Boards Manager...`. Search "esp8266" and install this board (from 2.7.4 to forward is recommended).

Following these steps would be enough for just executing the .ino file and testing it with the server. If you want to see a detailed explanation of the http requests in ESP8266, you can go to `data_sending` directory. 

## Django

### Virtual enviroment

Go to `data_processing` directory and create a virtual enviroment writing:

    python3 -m venv venv

For activating the virtual enviroment, write:

    source venv/bin/activate

If you're using CMD, write the following commands:

    python -m venv venv
    venv\Scripts\activate

### Installation

When you've activated the virtual enviroment, install all libraries from `requirements.txt` using `pip`:

    pip install -r requirements.txt

All must be done in the `data_processing` directory.

### Setting up

In order to apply the migration in your SQLite database, write these commands:

    python3 manage.py makemigrations
    python3 manage.py migrate

If there are not problems in the last step, you can run this project writing:

    python3 manage.py runserver

If you're using CMD, just change `python3` to `python` or `py` for not having problems.

## React js

### Installation

In order to install all the libraries needed for the project, write this command inside of `data_interface`:

    npm install

### Setting up

For running your project, you just need to write this command:

    npm start

If you want to know more about React and the implementation of Chart js in this project, you can go to `data_interface` directory.