var randomstring = require('randomstring')
var winston = require('winston')
var logger  = new winston.Logger()
var http = require('http')
var fs = require('fs')
var bodyParser = require('body-parser')

var sqlFormatter = require( "sql-formatter");

var app = require('express')();
var HOST="0.0.0.0"
var PORT=8080
server = http.createServer(app).listen(PORT,HOST);


app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
}));

app.set('view engine', 'ejs');

// index page 
app.get('/sqlconvertor', function(req, res) {
    res.render('sqlconvertor');
});

app.post('/output', function(req, res) {
    query=req.body.sql
    console.log(query)
    out=sqlFormatter.format(query,{
        params: ["'bar'"]
    });

    //out=sqlFormatter.format("SELECT * FROM tbl WHERE foo = ?", {
    //params: ["'bar'"]
    //})

    res.end(out);
});
