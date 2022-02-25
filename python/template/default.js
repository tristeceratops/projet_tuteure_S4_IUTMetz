let map = L.map('map')
    .setView([0, 0], 5);

L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", 
    {
        "attribution": "OpenStreetMap contributors"
    }
)
.addTo(map);

