#! /bin/bash
sqlite3 vehicles.db < create.sql
python ./main.py
