'use strict'

const serialPort = require('serialport');

const portSerial = new serialPort('COM2', {baudRate: 9600});

const parser = new serialPort.parsers.Readline();

portSerial.pipe(parser);

parser.on('data', (data) => {
    console.log(data);
});


const getBox = (req, res) => {
    portSerial.write(req.body.option);
    
    portSerial.write(req.body.password);
  
//console.log(req.body.option);
    res.status(200).send(req.body.option);
};

module.exports = {getBox};