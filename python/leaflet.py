class Leaflet:
    def __init__(self, coordinate, zoom, tile_server, attribution):
        self.js = f"""
            let map = L.map('map')
                .setView({coordinate}, {zoom});

            L.tileLayer(
                '{tile_server}', 
                {{
                    'attribution': '{attribution}'
                }}
            )
            .addTo(map);
        """

        # with open("./template/default.js", "r") as js_file:
        #     self.js = js_file.read()

        with open("./template/default.css", "r") as css_file:
            self.css = css_file.read()

    def marker(self, coordinate, tooltip = "", params = ""):
        self.js += f"""
            L.marker({coordinate}, {{{params}}})
                .addTo(map)
                .bindTooltip("{tooltip}"); 
        """

    def polyline(self, coordinate_list, color):
        self.js += f"""
            L.polyline({coordinate_list}, {{color: "{color}"}}).addTo(map);
        """

    def icon(self, name, url, size):
        self.js += f"""
            let {name} = L.icon({{
                iconUrl: '{url}',
                iconSize: {size},
            }});
        """

    def render(self):
        with open("./template/default.html", "r") as html_file:
            html = html_file.read()
            html = html.replace("{javascript}", self.js)
            html = html.replace("{css}", self.css)

            with open("./bin/build.html", "w") as html_build_file:
                html_build_file.write(html)

    