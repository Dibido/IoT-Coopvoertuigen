from flask import Flask, jsonify, abort, make_response, request, url_for, g, render_template
from sqlite3 import dbapi2 as sqlite3
from datetime import datetime
from time import strptime, strftime, mktime, gmtime

app = Flask(__name__)
debugMode = True

#Database functions----------

#Opens a new database connection
def get_db():
	if not hasattr(g, 'sqlite_db'):
		g.sqlite_db = connect_db()
	return g.sqlite_db

#Connects to a specific database
def connect_db():
	conn = sqlite3.connect('vehicles.db')
	conn.row_factory = sqlite3.Row
	return conn

#Closes the database
@app.teardown_appcontext
def close_db(error):
	if hasattr(g, 'sqlite_db'):
		g.sqlite_db.close()

#Selects the last inserted row from Vehicles
def last_id():
    db = get_db()
    cur = db.execute('select last_insert_rowid() from Vehicles')
    vehicleData = cur.fetchall()
    return vehicleData[0][0]

#Shows data from a specific vehicle
def retrieve_vehicle(vehicleId):
    db = get_db()
    cur = db.execute("select * from Vehicles where vehicleId = ?", (vehicleId, ))
    vehicleData = cur.fetchall()
    vehicles = []
    for row in vehicleData:
        vehicles.append({'Timestamp' : row[0], 'vehicleId' : row[1], 'leftSpeed' : row[2], 'rightSpeed' : row[3], 'frontDist' : row[4], 'leftDist' : row[5], 'rightDist' : row[6]})
    return vehicles

def make_public_vehicle(vehicle):
    new_vehicle = {}
    for field in vehicle:
        if field == 'vehicleId':
            new_vehicle['uri'] = url_for('get_vehicle', vehicleId=vehicle['vehicleId'], _external=True)
        else:
            new_vehicle[field] = vehicle[field]
        return new_vehicle

def datetime_to_epoch(datetime_string):
    # Convert to datetime format
	target_timestamp = strptime(datetime_string, '%Y-%m-%d %H:%M:%S')
	# Convert to epoch
	epoch_in_millis = mktime(target_timestamp) * 1000
	return epoch_in_millis
    


#Request handlers----------

#GET request handler that returns every vehicle in the database
@app.route('/vehicles', methods=['GET'])
def get_vehicles():
	db = get_db()
	cur = db.execute('select distinct vehicleId from Vehicles order by vehicleId')
	vehicleData = cur.fetchall() # list of Row objects, cannot jsonify

	data = []
	for row in vehicleData:
		data.append({'vehicleId': row[0]})
	return render_template('index.html', vehicles = data)

#GET request handler that returns a specific vehicle in the database
@app.route('/vehicle/<int:vehicleId>', methods=['GET'])
def get_vehicle(vehicleId):
	vehicle = retrieve_vehicle(vehicleId)
	if len(vehicle) == 0:
		abort(404)
		
	leftdistance = ""
	rightdistance = ""
	frontdistance = ""
	leftspeed = ""
	rightspeed = ""
	
	for item in vehicle:
		epoch = str(datetime_to_epoch(item['Timestamp']))
		leftdistance += '[' + epoch + ',' + str(item['leftDist']) + ']' + ','
		
		rightdistance += '[' + epoch + ',' + str(item['rightDist']) + ']' + ','
		
		frontdistance += '[' + epoch + ',' + str(item['frontDist']) + ']' + ','
		
		leftspeed += '[' + epoch + ',' + str(item['leftSpeed']) + ']' + ','
		
		rightspeed += '[' + epoch + ',' + str(item['rightSpeed']) + ']' + ','
	
	leftDist = leftdistance[0:-1]
	rightDist = rightdistance[0:-1]
	frontDist = frontdistance[0:-1]
	leftSpeed = leftspeed[0:-1]
	rightSpeed = rightspeed[0:-1]
	
	return render_template('charts.html', leftdistancesdata = '[' + leftDist + ']', rightdistancesdata = '[' + rightDist + ']', frontdistdata = '[' + frontDist + ']', leftspeeddata = '[' + leftSpeed + ']', rightspeeddata = '[' + rightSpeed + ']' )

#POST request handler that inserts a new vehicle in the database
@app.route('/data', methods=['POST'])
def create_vehicle():
    if not request.json or 'vehicleId' not in request.json:
        abort(400)
    db = get_db()
    cur = db.execute("insert into Vehicles (Timestamp, vehicleId, leftSpeed, rightSpeed, frontDist, leftDist, rightDist) values (?,?,?,?,?,?,?)",
	( request.json['Timestamp'], request.json['vehicleId'], request.json['leftSpeed'], request.json['rightSpeed'], request.json['frontDist'], request.json['leftDist'], request.json['rightDist']))
    db.commit()
    vehicles = retrieve_vehicle(last_id())
    return jsonify({'vehicles': [make_public_vehicle(vehicle) for vehicle in vehicles]})

#Bad request handler
@app.errorhandler(400)
def bad_request(error):
	return make_response(jsonify({'error': 'Bad request'}), 400)

@app.errorhandler(404)
def not_found(error):
	return make_response(jsonify({'error': 'Not found'}), 404)


if __name__ == '__main__':
	app.run(debug = debugMode)
