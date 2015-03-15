#external
  module
  __dirname

var
  express = require('express')
  app = express()
  express-ws = require('express-ws')(app)
  inspect = require('util').inspect

var things = {}
var clients = {}

var send-message = (ws, msg) ->
  console.log ('Sending message: ' + inspect msg)
  ws.send
    JSON.stringify msg

var report-error = (ws, error) ->
  console.log ('Reporting error: ' + error)
  send-message
    ws
    {error: error}


var handle-client-message = (ws, msg) -> do!
  var client-id = msg['client-id']
  if (clients[client-id] == undefined)
    console.log ('Client connected: ' + client-id)
    clients[client-id] = ws
  else if (clients[client-id] != ws)
    console.log ('Client reconnected: ' + client-id)
    clients[client-id].close()
    clients[client-id] = ws
  var thing-id = msg['thing-id']
  if (thing-id != undefined)
    var thing = things[thing-id]
    if (thing == undefined)
      report-error (ws, 'Thing disconnected: ' + thing-id)
    else
      send-message (thing, msg)

var handle-thing-message = (ws, msg) -> do!
  var thing-id = msg['thing-id']
  if (thing-id == undefined)
    report-error (ws, 'thing-id undefned')
    return
  if (things[thing-id] == undefined)
    console.log ('Thing connected: ' + thing-id)
    things[thing-id] = ws
  Object.keys(clients).for-each #->
    send-message (clients[#it], msg)

var handle-message = (ws, msg-text) -> do!
  console.log ('Received message: ' + inspect msg-text)
  try do
    var
      msg = JSON.parse msg-text
      client-id = msg['client-id']
    if (client-id != undefined)
      handle-client-message (ws, msg)
    else
      handle-thing-message (ws, msg)
  catch (var e)
    report-error (ws, e.to-string())
    console.log ('Stack trace: ' + e.stack)
  

module.exports = #->
  app.get
    '/'
    (req, res, next) ->
      console.log ('Served front page', req.testing);
      res.send-file(__dirname + '/front-page.html')
   
  app.ws
    '/'
    (ws, req) ->
      ws.on
        'message'
        (msg) -> handle-message (ws, msg)
      console.log ('Web socket connected');
   
  var server = app.listen
    3000
    #->
      var
        host = server.address().address
        port = server.address().port
      console.log ('Server listening at http://%s:%s', host, port)
