'use strict'

const serialPort = require('serialport');

const portSerial = new serialPort('COM2', {baudRate: 9600});

const parser = new serialPort.parsers.Readline();

portSerial.pipe(parser);



const writeSerial = (res, req) => {

    res.status(200).send('OK');
}

module.exports = writeSerial;