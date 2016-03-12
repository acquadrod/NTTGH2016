var express = require('express');
var app = express();
var fs = require("fs");
var mqtt    = require('mqtt');
var client  = mqtt.connect('mqtt://127.0.0.1');

client.on('connect', function () {
  client.subscribe('presence');
  client.publish('presence', 'Hello mqtt');
});


app.get('/getCoffe', function (req, res) {
 console.log('long');
  client.publish('coffe', 'LONG');
res.sendStatus(200);
})

app.get('/getEspresso', function (req, res) {
 console.log('espresso');
  client.publish('coffe', 'SHORT');
res.sendStatus(200);
})
var server = app.listen(8081, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Example app listening at http://%s:%s", host, port)

})
