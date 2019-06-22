#! /bin/bash
#If the database exists delete it
if [ -e "vehicles.db" ]
then
	rm ./vehicles.db
	echo "!--removed database--!"
fi
#Create database
sqlite3 vehicles.db < create.sql
#Run flask
python ./main.py
