from random import random
import leaflet

latlon = []

with open("./chemin.txt", "r") as f:
    chemin = f.read().split(" ")

with open("./communes_parsed.csv", "r") as f:
    i = 0

    lines = f.readlines()

    for sommet in chemin:
        for line in lines:
            # print(line.split(",")[0])
            if (sommet == line.split(",")[0]):
                latitude = float(line.split(",")[5])
                longitude = float(line.split(",")[6])

                latlon.append([latitude, longitude])
                break;

    
    latitude = lines[1].split(",")[5]
    longitude = lines[1].split(",")[6]
    latlon.append([latitude, longitude])
 
    # print(lines)



    # latitude = lines[int(chemin[1])].split(",")[5]
    # longitude = lines[int(chemin[1])].split(",")[6]
    # print(latitude)
    # latlon.append([latitude, longitude])





l = leaflet.Leaflet(
    [latlon[0][0], latlon[0][1]], 
    4, 
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", 
    "OpenStreetMap contributors."
)

l.icon("depart", "https://emojipedia-us.s3.dualstack.us-west-1.amazonaws.com/thumbs/120/twitter/282/large-green-circle_1f7e2.png", [48, 48])
l.icon("arrivee", "https://emojipedia-us.s3.dualstack.us-west-1.amazonaws.com/thumbs/120/twitter/282/large-red-circle_1f534.png", [48, 48])

l.polyline(latlon, "red")

for i in range(0, len(latlon)):
    if i == 0:
        l.marker([latlon[i][0], latlon[i][1]], f"{latlon[i][0]}, {latlon[i][1]}", "icon: depart")
     
    elif i == len(latlon) - 2:
        l.marker([latlon[i][0], latlon[i][1]], f"{latlon[i][0]}, {latlon[i][1]}", "icon: arrivee")

    else :
        # l.marker([latlon[i][0], latlon[i][1]], f"{latlon[i][0]}, {latlon[i][1]}")
        pass

l.render()