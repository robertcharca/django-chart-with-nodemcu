# React chart with Django and NodeMCU-M 

## Overview

This project has  

## NodeMCU-M (ESP8266)

Still in progress.

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

### Chart js