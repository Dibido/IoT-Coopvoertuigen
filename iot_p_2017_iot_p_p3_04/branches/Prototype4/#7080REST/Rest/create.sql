CREATE TABLE Vehicles (
	Timestamp datetime NOT NULL,
    vehicleId int NOT NULL,
	leftSpeed int NOT NULL,
	rightSpeed int NOT NULL,
	frontDist int NOT NULL,
    leftDist int NOT NULL,
    rightDist int NOT NULL,
    CONSTRAINT PK_Vehicle PRIMARY KEY (Timestamp, vehicleId)
);

INSERT INTO Vehicles (Timestamp, vehicleId, leftSpeed, rightSpeed, frontDist, leftDist, rightDist) VALUES (datetime('now'), 1, 100, 100, 35, 20, 30)
