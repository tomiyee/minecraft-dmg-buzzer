const http = require('http');
const express = require("express"); // Creates the Webserver
const path = require('path');
const socketIO = require('socket.io'); // Allows for server-client interaction
const bodyParser = require("body-parser");

// Generates the express server as an HTTP server, and enables socket.io
const app = express();
const server = http.Server(app);
const io = socketIO(server);

const PORT = 3000;

// Redirect all simple get requests to the client-side index.html
app.get('/', (req, res) => res.sendFile(__dirname + '/client/index.html'));
app.use('/css', express.static( __dirname + '/client/css'));
app.use('/scripts', express.static( __dirname + '/client/scripts'));

//Here we are configuring express to use body-parser as middle-ware.
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

server.listen(PORT, process.env.IP || "0.0.0.0", () => {
  let addr = server.address();
  console.log("Server listening at", addr.address + ":" + addr.port);
});

// ========================= HTTP Request Handlers ========================= //

let hurtCounter = 0;

// This get request will yield the parity of the number of times someone got hurt
app.get('/hurt', (req, res) => {
  res.send(hurtCounter + '');
});

app.post('/hurt', (req, res) => {
  hurtCounter = (hurtCounter + 1) % 2;
  io.emit('owie-increment');
  res.sendStatus(200);
});

// =========================== Server Variables =========================== //

io.on('connection', (socket) => {
  console.log('New Connection');
});
