from http.server import BaseHTTPRequestHandler, HTTPServer
import json #librerias a utilizar

class MyHTTPRequestHandler(BaseHTTPRequestHandler): #Clase que hereda la clase de la libreria
    def _set_response(self, content_type="text/plain"):
        self.send_response(200) #enviar ok
        self.send_header("Content-type", content_type) #Enviar cabecera del tipo de contenido
        self.end_headers() #enviar cabecera

    def do_GET(self):
        self._set_response()
        self.wfile.write("Hello from the server!".encode()) #.encode importa y manda bytes

    def do_POST(self):
        content_length = int(self.headers["Content-Length"])
        post_data = self.rfile.read(content_length) #lee caracteres

        # Print the complete HTTP request
        print("\n----- Incoming POST Request -----")
        print(f"Requestline: {self.requestline}")
        print(f"Headers:\n{self.headers}")
        print(f"Body:\n{post_data.decode()}")
        print("-------------------------------")

        # Respond to the client
        response_data = json.dumps({"message": "Received POST data", "data": post_data.decode()})
        self._set_response("application/json")
        self.wfile.write(response_data.encode())

def run_server(server_class=HTTPServer, handler_class=MyHTTPRequestHandler, port=7800): #funcion para correr el servidor
    server_address = ("", port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting server on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run_server()